#include <myforest/node.h>
#include "myforest/dataset.h"
#include "myforest/decisiontree.h"

#include <iostream>
#include <vector>
#include <span>


int main()
{


    std::vector<float> v{2,1,3,
                         1,1,6,
                         2,2,6,
                         1,2,12,
                         1,3,14,
                         1,12,11};

    std::vector<float> y{1,0,1,0,1,0};

    myforest::DataSet data(v, y, 6, 3);
    myforest::DecisionTree tree(3);    
    tree.fit(data);

    std::vector<float> new_sample{2,1,3};
    int pred = tree.predict(new_sample);
    std::cout << "PREDICTED : " << pred << std::endl;


}
