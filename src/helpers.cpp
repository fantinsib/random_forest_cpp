#include "myforest/helpers.h"
#include <algorithm>
#include <numeric>



namespace myforest{

std::vector<int> sample_features(int num_features, int m_try){

    if (num_features <= 0 || m_try <= 0) throw std::invalid_argument("Featuring sampling error : num_features or m_try values are invalid");
    if (num_features < m_try) throw std::invalid_argument("More features to sample than existing features");

    static thread_local std::mt19937 rng{std::random_device{}()};
    std::vector<int> idx(num_features);
    std::iota(idx.begin(), idx.end(), 0); 
    std::shuffle(idx.begin(), idx.end(), rng);
    idx.resize(m_try);

    return idx;
}




}