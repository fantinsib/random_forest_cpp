#include <myforest/node.h>
#include "myforest/dataset.h"

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



    std::vector<float> v{4,1,3,
                         2,3,5,
                         4,5,9,
                         8,6,2};

    std::vector<float> y{1,0,1,1};

    myforest::DataSet data(v, y, 4, 3);


    float e = data.iloc_x(2,0);


    std::cout<< e<< std::endl;


}
