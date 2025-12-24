#ifndef RANDOMFOREST_H
#define RANDOMFOREST_H
#include "dataset.h"

namespace myforest{

class RandomForest
{
public:
    RandomForest();
    int seed_;
    DataSet random_samples(DataSet& v, float size = 0.6);
    void set_seed(int seed);
};

}
#endif // RANDOMFOREST_H
