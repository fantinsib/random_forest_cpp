#include "myforest/randomforest.h"
#include "myforest/decisiontree.h"
#include <random>
#include <cmath>
#include <numeric>


namespace myforest{

RandomForest::RandomForest(int n_trees_, int m_try_) :
    m_try(m_try_),
    n_trees(n_trees_)
    
{}

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

void RandomForest::fit(DataSet& v){

    trees_.clear();

    for (int i = 0; i < n_trees; i++){

        DecisionTree t = DecisionTree(3);
        DataSet subset = random_samples(v);
        t.fit(subset, true, m_try);
        trees_.push_back(std::move(t));
        
    }

    is_fitted = true;
    num_features = v.n_cols();

}

float RandomForest::single_predict(std::vector<float>& x){

    if (is_fitted != true) throw std::runtime_error(".single_predict() called but RandomForest was never fitted!");
    if (x.size()%num_features != 0) throw std::runtime_error("Number of features in sample does not match number of features from training.");
    
    int pos_count=0;
    int neg_count=0;

    for (auto& t : trees_){
        
        std::vector<int> t_pred = t.predict(x);
        (t_pred[0] == 1) ? pos_count++ : neg_count++;

    }

    float pct_predicted = (pos_count/static_cast<float>(pos_count+neg_count));

    return pct_predicted;

}

std::vector<int> RandomForest::predict(std::vector<float>& x){

    if (is_fitted != true) throw std::runtime_error(".predict() called but RandomForest was never fitted!");
    if (x.size()%num_features != 0) throw std::runtime_error("Number of features in sample does not match number of features from training.");

    int num_samples = x.size()/num_features;

    std::vector<int> pred(num_samples);
    std::vector<float> sample(num_features);

    //Iterating to separate each sample :
    for (int i = 0; i<num_samples; i++){
        for (int j = 0; j < num_features; j++ ){
            sample[j]= (x[i*num_features + j]);
        }

        // We now have a complete sample in sample; 

        int pos_count=0;
        int neg_count=0;

        for (auto& t : trees_){
    
            std::vector<int> t_pred = t.predict(sample);
            if (t_pred[0] ==0) neg_count++;
            if (t_pred[0] ==1) pos_count++;

        }
        (pos_count >= neg_count) ? pred[i]=1 : pred[i] = 0;

    }
    return pred;

}
}

