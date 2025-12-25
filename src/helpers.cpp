#include "myforest/helpers.h"
#include <algorithm>
#include <numeric>



namespace myforest{

std::vector<int> sample_features(int num_features, int m_try){

    std::mt19937 rng;
    std::vector<int> idx(num_features);
    std::iota(idx.begin(), idx.end(), 0); 
    std::shuffle(idx.begin(), idx.end(), rng);
    idx.resize(m_try);

    return idx;
}




}