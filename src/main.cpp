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
                         2,2,6,
                         1,2,12,
                         1,3,14,
                         1,12,11};

    std::vector<float> y{0,0,1,0,1,0};

    myforest::DataSet data(v, y, 6, 3);

    myforest::DecisionTree tree(3);

    myforest::Node root_node;

    tree.build_tree(root_node, data);
    tree.print_tree(root_node, 0);
}
