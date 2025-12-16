#include <myforest/node.h>
#include "myforest/dataset.h"
#include "myforest/decisiontree.h"

#include <iostream>
#include <vector>
#include <span>



void print_vector(std::vector<float>& x){

    for (int i =0;i<x.size(); i++){

        std::cout << x[i] << std::endl;
    }


}

void print_vector_2(std::vector<float>& x){

    for (auto& i : x){
        std::cout <<  i <<std::endl;
    }


}

template <typename T>
auto return_row(int row, const std::vector<T>& v, int num_row, int num_col){

    std::span<const T> cs(v);
    auto sub = cs.subspan(row*num_col, num_col);
    return sub;


}


int main()
{



    std::vector<float> v{1,2,3,
                         4,5,6,
                         7,8,9,
                         10,11,12};

    std::vector<float> y{0,0,1,1};

    myforest::DataSet data(v, y, 4, 3);

    myforest::DecisionTree tree(3);

    std::pair<int, int> results = tree.count(data.y());


    float gini_score = tree.gini_score(results.first, results.second);
    std::cout << gini_score << std::endl;

    tree.best_split(data);


}
