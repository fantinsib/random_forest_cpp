#include "myforest/randomforest.h"
#include "myforest/decisiontree.h"
#include <random>
#include <cmath>


namespace myforest{

RandomForest::RandomForest() {}

DataSet RandomForest::random_samples(DataSet& v, float size){
    /*
    Takes as input a dataset and returns a sub dataset consisting of 
    random samples from the original dataset
    */
    int num_samples = v.n_rows();
    int sample_size = std::round(num_samples*size);

    std::vector <int> index_num;

    std::mt19937 rng;
    if (seed_) rng.seed(*seed_);
    else rng.seed(std::random_device{}());

    std::uniform_int_distribution<int> dist(0, num_samples-1);
    for (int i = 0; i < sample_size; i++){
    
        int loc = dist(rng);
        index_num.push_back(loc);
    }

    return v.index_split(index_num);
}





void RandomForest::set_seed(int seed){

    if (seed < 0) throw std::runtime_error ("Seed value can't be negative.");
    this->seed_ = seed;
}

}

