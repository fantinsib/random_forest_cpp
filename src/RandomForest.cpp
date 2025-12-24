#include "myforest/randomforest.h"
#include <random>


namespace myforest{

RandomForest::RandomForest() {}

DataSet RandomForest::random_samples(DataSet& v, float size = 0.6){
    /*
    Takes as input a dataset and returns a sub dataset consisting of 
    random samples from the original dataset
    */

}

void RandomForest::set_seed(int seed){
    this->seed_ = seed;
}



}

