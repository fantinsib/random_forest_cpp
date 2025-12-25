#ifndef RANDOMFOREST_H
#define RANDOMFOREST_H
#include "dataset.h"
#include "decisiontree.h"
#include <optional> 

namespace myforest{

class RandomForest
{
public:
    RandomForest(int n_trees_, int m_try_);

    std::optional<int> seed_;
    int m_try;
    int n_trees;
    DataSet random_samples(DataSet& v, float size = 0.6);
    void set_seed(int seed);
    void fit(DataSet& v);

    float single_predict(std::vector<float>& x);

private:

    std::vector<DecisionTree> trees_;

};

}
#endif // RANDOMFOREST_H
