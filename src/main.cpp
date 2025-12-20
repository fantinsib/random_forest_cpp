#include <myforest/node.h>
#include "myforest/dataset.h"
#include "myforest/decisiontree.h"

#include <iostream>
#include <vector>
#include <span>

void print_vector(const std::vector<int> v){

    for (auto i : v){

        std::cout << i << ", ";
    }
        std::cout << std::endl;


}


int main()
{
    std::vector<float> v{1,1,3,
                         1,1,6,
                         2,2,6,
                         1,2,2,
                         3,3,1,
                         5,3,2};

    std::vector<float> y{1,0,0,0,1,1};

    myforest::DataSet data(v, y, 6, 3);
    myforest::DecisionTree tree(2);
    tree.fit(data);

    std::vector<float> new_sample{1,1,3,
                                  1,1,6,
                                  3,3,1};

    std::vector<int> pred = tree.predict(new_sample);
    std::cout << "PREDICTED : " << std::endl;
    print_vector(pred);
    tree.print_tree();

}
