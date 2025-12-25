#ifndef RANDOMFOREST_H
#define RANDOMFOREST_H
#include "dataset.h"
#include <optional> 

namespace myforest{

class RandomForest
{
public:
    RandomForest();
    std::optional<int> seed_;
    DataSet random_samples(DataSet& v, float size = 0.6);
    DataSet random_features(DataSet& v);
    void set_seed(int seed);
};

}
#endif // RANDOMFOREST_H
