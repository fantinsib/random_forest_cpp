#include "myforest/decisiontree.h"
#include "myforest/dataset.h"
#include <span>


namespace myforest{
DecisionTree::DecisionTree(int max_depth_):
     max_depth(max_depth_),
     num_features(4)
{}


float DecisionTree::gini_score(int pos_score, int neg_score){

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

std::pair<int, int> DecisionTree::best_split(const DataSet& data) const{

    const std::vector<float>& x = data.X();
    const std::vector<float>& y = data.y();

    const int n_row = data.n_rows();
    const int n_col = data.n_cols();


    for (int col = 0; col < n_col; col++){
        for (int row = 0; row < n_row; n_row++){





        }





    }



}

}






