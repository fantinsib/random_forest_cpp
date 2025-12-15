#include <myforest/node.h>
#include "myforest/dataset.h"
#include <iostream>
#include <vector>



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

    std::vector<float> v{1,2,3,4};

    print_vector(v);
    print_vector_2(v);

}
