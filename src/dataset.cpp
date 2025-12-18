#include "myforest/dataset.h"
#include <iostream>


namespace myforest{
DataSet::DataSet(std::vector<float> X, std::vector<float> Y, int n_rows, int n_cols):

    X_(X),
    y_(Y),
    n_rows_(n_rows),
    n_cols_(n_cols)

{}

std::span<const float> DataSet::row_X(int row) const {

    std::span<const float> cs(X_);
    auto sub = cs.subspan(row*n_cols_, n_cols_);
    return sub;
}


std::span<const float> DataSet::row_y(int row) const {

    std::span<const float> cs(y_);
    auto sub = cs.subspan(row,1);
    return sub;
}


DataSet DataSet::index_split(std::vector<int>& index) const {
    // Returns a subsplit of the dataset object of the rows from the specified index

    //vector index references nth row of the dataset
    std::vector<float> X_results;
    std::vector<float> y_results;

    for (auto i : index){
        for (int col = 0; col < n_cols_; col++){
            X_results.push_back(iloc_x(i, col));


    }
        y_results.push_back(iloc_y(i));
    }

    DataSet output(X_results, y_results, index.size(), n_cols_);
    return output;
}

void DataSet::print() const {

    for (int r = 0; r < n_rows_; r++){
        std::cout << "Sample " << r << " | Target : " << iloc_y(r) << std::endl;
        for (int col = 0; col < n_cols_; col++){

            std::cout << iloc_x(r, col) << ", ";

        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}}
