#include "myforest/decisiontree.h"
#include "myforest/dataset.h"
#include <span>
#include <algorithm>


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



    std::pair<int, float> best_col_and_t;

    for (int col = 0; col < n_col; col++){
        // Identifying thresholds:

        //Fetching the col and sorting:

        std::vector<float> sorted_col(n_row);

        for (int i =0; i<n_row; i++)
        {
            sorted_col[i] = data.iloc_x(i, col);

        }
        // sorting:
        std::sort(sorted_col.begin(), sorted_col.end());

        std::vector<float> thresholds;

        for (int row = 1; row < n_row; row++){

            float a = sorted_col[row-1];
            float b = sorted_col[row];

            if (a!=b) {float t = (a+b)*0.5;}


            thresholds.push_back(t);

    }
        std::cout << "Thresholds"<< std::endl;
        for (auto v : thresholds){
            int count_pos_left= 0;
            int count_pos_right=0;
            int count_neg_left=0;
            int count_neg_right=0;
            for (int i = 0; i < n_row; i++){


                std::cout << data.iloc_x(i, col) << std::endl;

                if (data.iloc_x(i, col) >= v)
                {
                    if (data.iloc_y(i) == 1) {count_pos_right++;}
                    if (data.iloc_y(i) == 0) {count_neg_right++;}

                }
                if (data.iloc_x(i, col) < v)
                {
                    if (data.iloc_y(i) == 1) {count_pos_left++;}
                    if (data.iloc_y(i) == 0) {count_neg_left++;}

                }

            }

            std::cout<< "Distribution count for col " << col << " and v "<< v << std::endl;
            std::cout << "Left" << std::endl;
            std::cout << count_pos_left << " " << count_neg_left << std::endl;
            std::cout << "Right" << std::endl;
            std::cout << count_pos_right << " " << count_neg_right << std::endl;








        }





    }



}

}






