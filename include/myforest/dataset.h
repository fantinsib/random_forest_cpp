#ifndef DATASET_H
#define DATASET_H
#include <vector>


namespace myforest{
class DataSet
{
public:
    DataSet(std::vector<float> X, std::vector<float> Y, int n_rows, int n_cols);
    int n_rows() const {return n_rows_;}
    int n_cols() const {return n_cols_;}

    const std::vector<float>& X() const {return X_;}
    const std::vector<float>& y() const {return y_;}

    float iloc_x(int row, int col) const {return X_[col +row*n_cols_];}
    float iloc_y(int row) const {return y_[row];}





private:
    std::vector<float> X_;
    std::vector<float> y_;
    int n_rows_;
    int n_cols_;


};
}
#endif // DATASET_H
