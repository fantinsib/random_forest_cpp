#include <myforest/node.h>
#include "myforest/dataset.h"
#include "myforest/decisiontree.h"

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
 * v.1 will be limited to binary
 * classification for now (targets -> {0,1})
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

    /*
    std::vector<float> f{1,1,3,5,
                         1,1,6,3,
                         2,2,6,4,
                         1,2,2,9,
                         3,3,1,13,
                         5,3,2,20};

    std::vector<float> v{6, 3, 7, 4,
                        6, 9, 2, 6,
                        7, 4, 3, 7,
                        7, 2, 5, 4,
                        1, 7, 5, 1,
                        4, 0, 9, 5,
                        8, 0, 9, 2,
                        6, 3, 8, 2,
                        4, 2, 6, 4,
                        8, 6, 1, 3};

    std::vector<float> y{1,0,0,0,1,1,1,0,0,1};

    myforest::DataSet data(v, y, 10, 4);
    myforest::DecisionTree tree(100);
    tree.fit(data);

    std::vector<float> new_sample{1,1,6,3.1,
                                  1.1,2,2,8.9,
                                  4.5, 4, 2.1, 30};

    std::vector<int> pred = tree.predict(new_sample);
    std::cout << "PREDICTED : " << std::endl;
    print_vector(pred);
    tree.print_tree();

    */


    std::mt19937 rng(43);
    std::uniform_int_distribution<int> dist(0,9);
    int x = dist(rng);
    std::cout << x<< std::endl;

}
