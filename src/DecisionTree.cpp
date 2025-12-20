#include "myforest/decisiontree.h"
#include "myforest/dataset.h"
#include "myforest/node.h"
#include <span>
#include <algorithm>


namespace myforest{
DecisionTree::DecisionTree(int max_depth_):
     max_depth(max_depth_)
{
    Node root_node;

}


float DecisionTree::gini_score(int pos_score, int neg_score) const{
    float total = pos_score+neg_score;
    float gini = 1-((pos_score/total)*(pos_score/total) + (neg_score/total)*(neg_score/total));
    return gini;
}

const std::pair<int, int> DecisionTree::count(const std::vector<float>& y) const{
    int count_positive = 0;
    int count_negative = 0;

    for (auto i : y){

        if (i == 1) {count_positive+=1;}
        if (i == 0) {count_negative+=1;}
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

SplitResult DecisionTree::best_split(const DataSet& data) const{

    //get data from the dataset object
    const std::vector<float>& x = data.X();
    const std::vector<float>& y = data.y();

    const int n_row = data.n_rows();
    const int n_col = data.n_cols();

    //definition of variables
    float best_w_gini = 1;
    float best_threshold;
    int split_feature;
    std::vector<int> top_left_index;
    std::vector<int> top_right_index;
    bool is_pure_gini = false;
    float left_gini = -1;
    float right_gini = -1;


    for (int col = 0; col < n_col; col++){ //for each column:

        std::vector<float> thresholds = get_thresholds(data, col); //fetch the thresholds of the col
        if (thresholds.empty()) continue;

    //for each of the threshold, iterate in the corresponding col
    // if the sample feature is superior or equal to the threshold -> counted in
    // the right node, left otherwise. Code computes the number of positive and negative
    // classes that end up in each node + the index of the left/right values

        for (auto v : thresholds){
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

    return {split_feature, best_threshold, top_left_index, top_right_index, is_pure_gini, left_gini,right_gini};
}

void DecisionTree::build_tree(myforest::Node& node, const DataSet& data) const {

    SplitResult split = best_split(data);
    std::pair<int, int> class_count = data.count_classes();

    if (class_count.first == 0 || class_count.second == 0){
        node.is_leaf = true;
        if (class_count.first >= class_count.second) node.predicted_class = 1;
        if (class_count.first < class_count.second) node.predicted_class = 0;
        node.feature_index = split.feature;
        node.threshold = split.threshold;
        return;
    }

    if (split.left_index.empty() || split.right_index.empty()) {
        node.is_leaf = true;
        if (class_count.first >= class_count.second) node.predicted_class = 1;
        if (class_count.first < class_count.second) node.predicted_class = 0;
        node.feature_index = split.feature;
        node.threshold = split.threshold;
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

    build_tree(*node.left_child, left_data);
    build_tree(*node.right_child, right_data);
}

void DecisionTree::print_tree(Node& node, int depth = 0){

    if (!node.is_leaf){

        if (node.left_child) print_tree(*node.left_child, depth+1);
        if (node.right_child) print_tree(*node.right_child, depth+1);

    }
}

int DecisionTree::iterate_tree(Node& node, const std::vector<float>& s) const {

    int feature = node.feature_index;
    float threshold = node.threshold;

    if (node.is_leaf) return node.predicted_class;

    if (s[feature] <= threshold){
        if (node.left_child){
            return iterate_tree(*node.left_child, s);
        }
        else return node.predicted_class;
    }

    if (s[feature]>threshold){

        if (node.right_child){
            return iterate_tree(*node.right_child, s);
        }
        else return node.predicted_class;

    }

    return -1;
}

void DecisionTree::fit(const DataSet& data){

    build_tree(root_node, data);

}

int DecisionTree::predict(const std::vector<float>& s){

    return iterate_tree(root_node, s);

}

}




