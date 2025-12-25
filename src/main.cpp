#include <myforest/node.h>
#include "myforest/dataset.h"
#include "myforest/decisiontree.h"
#include "myforest/randomforest.h"

#include <iostream>
#include <vector>
#include <span>
#include <random>


/*
 *
 * This project aims at implementing
 * a random forest engine in C++ with
 * a Python binding for easier use.
 *
 * Limited to binary classification
 * for now (targets -> {0,1})
 *
 */


void print_vector(const std::vector<int> v){

    for (auto i : v){

        std::cout << i << ", ";
    }
        std::cout << std::endl;
}

int main()
{

    std::vector<float> f{1,1,3,5,
                         1,1,6,3,
                         2,2,6,4,
                         1,2,2,9,
                         3,3,1,13,
                         5,3,2,20};

    std::vector<float> v{6, 1, 2, 4,
                        6, 9, 2, 6,
                        7, 2, 0, 7,
                        7, 2, 3, 4,
                        1, 7, 1, 1,
                        4, 0, 9, 5,
                        8, 0, 9, 2,
                        6, 3, 2, 2,
                        4, 9, 6, 4,
                        8, 6, 10, 3};


    std::vector<float> y{0,1,0,0,1,1,1,0,1,1};

    std::vector<float> x2{8,11,11,3};
    
    myforest::DataSet data(v, y, 10, 4);
    
    myforest::RandomForest rf(100, 2);
    
    rf.fit(data);

    float pred = rf.single_predict(x2);

    std::cout << pred << std::endl;

    // statement vide

}
