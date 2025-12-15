#include "myforest/dataset.h"


namespace myforest{
DataSet::DataSet(std::vector<float> X, std::vector<float> Y, int n_rows, int n_cols):

    X_(X),
    y_(Y),
    n_rows_(n_rows),
    n_cols_(n_cols)

{}

 }
