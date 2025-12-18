#include "myforest/decisiontree.h"
#include "myforest/dataset.h"
#include "myforest/node.h"
#include <span>
#include <algorithm>


namespace myforest{
DecisionTree::DecisionTree(int max_depth_):
     max_depth(max_depth_),
     num_features(4)
{}


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

const std::vector<float> DecisionTree::thresholds(const std::vector<float>& X) const{






}

SplitResult DecisionTree::best_split(const DataSet& data) const{

    const std::vector<float>& x = data.X();
    const std::vector<float>& y = data.y();

    const int n_row = data.n_rows();
    const int n_col = data.n_cols();



    float best_w_gini = 1;
    float best_threshold;
    int split_feature;
    std::vector<int> top_left_index;
    std::vector<int> top_right_index;

    //iterating columns:
    for (int col = 0; col < n_col; col++){

        //Preparing the thresholds :
        //Getting the col values
        std::vector<float> sorted_col(n_row);
        for (int i =0; i<n_row; i++)
        {
            sorted_col[i] = data.iloc_x(i, col);
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

    //Splitting the col for each of the thresholds:
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
            float w_gini = gini_left*(count_pos_left+count_neg_left)/n_row
                           + gini_right*(count_pos_right+count_neg_right)/n_row;

            //Is best split so far ?
            if (w_gini < best_w_gini){
                best_w_gini = w_gini;
                best_threshold = v;
                split_feature = col;
                top_right_index = right_index;
                top_left_index = left_index;

                }
        }
    }

    std::cout << "RESULTS" << std::endl << "Gini :" << best_w_gini << " | Best t : " << best_threshold << " | Split on col "<<split_feature << std::endl;

    SplitResult split = SplitResult(split_feature, best_threshold, top_left_index, top_right_index);

    return split;
}

void DecisionTree::build_tree(Node root_node, const DataSet& data) const{


    SplitResult split = best_split(data);

    int depth = 1;

    if (depth >= max_depth){
        return;
    }













}


}






