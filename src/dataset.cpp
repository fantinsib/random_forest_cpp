#include "myforest/dataset.h"


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

Table::Table(std::vector<float> x, int n_row, int n_col):

    X_(x),
    n_rows_(n_row),
    n_cols_(n_col)

{}








}
