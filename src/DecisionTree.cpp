#include "myforest/decisiontree.h"
#include "myforest/dataset.h"
#include "myforest/node.h"
#include "myforest/helpers.h"
#include <span>
#include <algorithm>
#include <random>
#include <numeric>
#include <stdexcept>



namespace myforest{
DecisionTree::DecisionTree(int max_depth_):
     max_depth(max_depth_)
{
    Node root_node;}

float DecisionTree::gini_score(int pos_score, int neg_score) const{
    if (pos_score==0 && neg_score ==0) throw std::invalid_argument("No values specified for positive and negative scores.");

    float total = pos_score+neg_score;
    float gini = 1-((pos_score/total)*(pos_score/total) + (neg_score/total)*(neg_score/total));
    return gini;
}

std::pair<int, int> DecisionTree::count(const std::vector<float>& y) const{
    int count_positive = 0;
    int count_negative = 0;

    for (auto i : y){

        if (i == 1) {count_positive+=1;}
        else if (i == 0) {count_negative+=1;}
        else {throw std::invalid_argument("DecisionTree.count() : non-binary label");}
    }
    return {count_positive, count_negative};
}

const std::vector<float> DecisionTree::get_thresholds(const DataSet& data, int t_col) const{

    //Takes a reference to the dataset and returns the threshold vector
    // for the specified col

    int n_row = data.n_rows();
    std::vector<float> sorted_col(n_row);
    for (int i =0; i<n_row; i++)
    {
        sorted_col[i] = data.iloc_x(i, t_col);
    }
    // sorting:
    std::sort(sorted_col.begin(), sorted_col.end());
    //computing & storing the thresholds in a vector:
    std::vector<float> thresholds;
    for (int row = 1; row < n_row; row++){

        float a = sorted_col[row-1];
        float b = sorted_col[row];

        if (a!=b) {
            float t = (a+b)*0.5;
            thresholds.push_back(t);
        }
    }
    return thresholds;
}

SplitResult DecisionTree::best_split(const DataSet& data, bool in_rf, int m_try) const{
    /*
    Takes as input a dataset and returns a SplitResult struct containing
    the best split based on Gini
    */

    //get data from the dataset object
    const std::vector<float>& x = data.X();
    const std::vector<float>& y = data.y();

    const int n_row = data.n_rows();
    const int n_col = data.n_cols();

    //definition of variables
    float best_w_gini = 1;
    float best_threshold = -1;
    int split_feature = -1;
    std::vector<int> top_left_index;
    std::vector<int> top_right_index;
    bool is_pure_gini = false;
    float left_gini = -1;
    float right_gini = -1;
    bool found_a_split = false;

    // If best_split is called in the context of a RandomForest,
    // the features are selected based on m_try :

    std::vector<int> col_number;
    
    if (in_rf){

        col_number = sample_features(num_features, m_try);
    }

    else{
        col_number.resize(num_features);
        std::iota(col_number.begin(), col_number.end(), 0);
    }

    for (int col : col_number){ //for each column:

        std::vector<float> thresholds = get_thresholds(data, col); //fetch the thresholds of the col
        if (thresholds.empty()) continue;

    //for each of the threshold, iterate in the corresponding col
    // if the sample feature is superior or equal to the threshold -> counted in
    // the right node, left otherwise. Code computes the number of positive and negative
    // classes that end up in each node + the index of the left/right values

        for (auto v : thresholds){
            found_a_split = true;
            int count_pos_left= 0;
            int count_pos_right=0;
            int count_neg_left=0;
            int count_neg_right=0;

            std::vector<int> left_index;
            std::vector<int> right_index;

            for (int i = 0; i < n_row; i++){
                if (data.iloc_x(i, col) >= v)
                {
                    if (data.iloc_y(i) == 1) {count_pos_right++;}
                    if (data.iloc_y(i) == 0) {count_neg_right++;}
                    right_index.push_back(i);
                }
                if (data.iloc_x(i, col) < v)
                {
                    if (data.iloc_y(i) == 1) {count_pos_left++;}
                    if (data.iloc_y(i) == 0) {count_neg_left++;}
                    left_index.push_back(i);
                }
            }
            //Computing the resulting gini of the two nodes:
            float gini_left = gini_score(count_pos_left, count_neg_left);
            float gini_right = gini_score(count_pos_right, count_neg_right);
            float left_weight  = static_cast<float>(count_pos_left + count_neg_left) / static_cast<float>(n_row);
            float right_weight = static_cast<float>(count_pos_right + count_neg_right) / static_cast<float>(n_row);

            float w_gini = left_weight * gini_left + right_weight * gini_right;
            bool is_pure_gini = false;

            //Is best split so far ?
            if (w_gini < best_w_gini){
                best_w_gini = w_gini;
                best_threshold = v;
                split_feature = col;
                top_right_index = right_index;
                top_left_index = left_index;
                left_gini = gini_left;
                right_gini= gini_right;

                }
        }
    }

    if (best_w_gini <= 1e-7f){
        is_pure_gini = true;
    }

    else is_pure_gini = false;

    return {split_feature, best_threshold, top_left_index, top_right_index, is_pure_gini, left_gini,right_gini, found_a_split};
}

void DecisionTree::fit(const DataSet& data, bool in_rf, int m_try){

    num_features = data.n_cols();
    if (num_features <= 0)  throw std::runtime_error("Error : num_features is null or non valid");
    if (m_try < 0) m_try = num_features;
    int depth = 0;
    build_tree(root_node, data, depth, in_rf, m_try);
    fitted = true;

}

void DecisionTree::build_tree(myforest::Node& node, const DataSet& data, int depth, bool in_rf, int m_try) const {

    SplitResult split = best_split(data, in_rf, m_try);
    std::pair<int, int> class_count = data.count_classes();

    //lambda function to stop iteration :
    auto end_branch= [&](){
        node.is_leaf = true;
        if (class_count.first >= class_count.second) node.predicted_class = 1;
        if (class_count.first < class_count.second) node.predicted_class = 0;
        node.feature_index = -1;
        node.threshold = 0.f;
        return;
    };

    if (split.found_a_split == false) {
        end_branch();
        return;
    }

    if (class_count.first == 0 || class_count.second == 0) {
        end_branch();
        return;
    }

    if (split.left_index.empty() || split.right_index.empty()) {
        end_branch();
        return;
    }

    if (depth >= max_depth){
        end_branch();
        return;
    }

    node.is_leaf = false;
    node.feature_index = split.feature;
    node.threshold = split.threshold;

    if (class_count.first >= class_count.second) node.predicted_class = 1;
    if (class_count.first < class_count.second) node.predicted_class = 0;


    DataSet left_data  = data.index_split(split.left_index);
    DataSet right_data = data.index_split(split.right_index);

    node.left_child  = std::make_unique<myforest::Node>();
    node.right_child = std::make_unique<myforest::Node>();

    node.left_child->rows  = split.left_index;
    node.right_child->rows = split.right_index;


    build_tree(*node.left_child, left_data, depth+1, in_rf, m_try);
    build_tree(*node.right_child, right_data, depth+1, in_rf, m_try);

}

void DecisionTree::print_tree_rec(const Node& node,const std::string& prefix,bool is_left,bool is_last) const {

    std::cout << prefix
              << (is_last ? "└── " : "├── ")
              << (is_left ? "yes: " : "no:  ");

    if (node.is_leaf) {
        std::cout << "Leaf(id=" << node.node_id
                  << ") → class=" << node.predicted_class << '\n';
        return;
    }

    std::cout << "Node(id=" << node.node_id
              << ") x[" << node.feature_index << "] <= "
              << std::fixed << std::setprecision(4) << node.threshold
              << '\n';

    
    const std::string child_prefix = prefix + (is_last ? "    " : "│   ");

    const bool has_left  = (node.left_child  != nullptr);
    const bool has_right = (node.right_child != nullptr);

    if (has_left) {
        const bool left_is_last = !has_right;                 
        print_tree_rec(*node.left_child, child_prefix, true, left_is_last);
    }
    if (has_right) {
        print_tree_rec(*node.right_child, child_prefix, false, true); 
    }
}

void DecisionTree::print_tree() const {
    if (fitted != true) {throw std::runtime_error(".print_tree() called, but tree was never fitted");}
    if (root_node.is_leaf) {
        std::cout << "Leaf(id=" << root_node.node_id
                  << ") → class=" << root_node.predicted_class << '\n';
        return;
    }

    std::cout << "Node(id=" << root_node.node_id
              << ") x[" << root_node.feature_index << "] <= "
              << std::fixed << std::setprecision(4) << root_node.threshold
              << '\n';

    if (root_node.left_child)
        print_tree_rec(*root_node.left_child, "", true,  true);   // is_left, is_last
    if (root_node.right_child)
        print_tree_rec(*root_node.right_child, "", false, true);
}

int DecisionTree::iterate_tree(const Node& node, const std::vector<float>& s) const {


    int feature = node.feature_index;
    float threshold = node.threshold;

    if (node.is_leaf) return node.predicted_class;

    if (s[feature] < threshold){
        if (node.left_child){
            return iterate_tree(*node.left_child, s);
        }
        else return node.predicted_class;
    }

    if (s[feature]>=threshold){

        if (node.right_child){
            return iterate_tree(*node.right_child, s);
        }
        else return node.predicted_class;

    }

    throw std::logic_error("Unreachable state in iterate_tree");
}

std::vector<int> DecisionTree::predict(const std::vector<float>& s){

    if (fitted != true) throw std::runtime_error(".predict() called but tree has not been fitted");
    if (s.size() % num_features != 0) throw std::runtime_error("Sample does not have the correct size");

    int num_samples = s.size()/num_features;

    std::vector<int> pred;
    std::vector<float> sample;
    for (int i = 0; i<num_samples; i++){


        for (int j = 0; j < num_features; j++ ){
            sample.push_back(s[i*num_features + j]);
        }

        pred.push_back((iterate_tree(root_node, sample)));
        sample.clear();
    }

    return pred;

}

}




