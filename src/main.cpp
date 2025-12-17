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


int main()
{



    std::vector<float> v{1,1,3,
                         1,1,6,
                         1,2,6,
                         1,2,12};

    std::vector<float> y{0,0,1,1};

    myforest::DataSet data(v, y, 4, 3);

    myforest::DecisionTree tree(3);

    std::pair<int, int> results = tree.count(data.y());


    float gini_score = tree.gini_score(results.first, results.second);
    std::cout << gini_score << std::endl;

    tree.best_split(data);


}
