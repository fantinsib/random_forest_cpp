#ifndef DECISIONTREE_H
#define DECISIONTREE_H
#include <iostream>


namespace myforest{
class DecisionTree
{
public:
    DecisionTree(int max_depth);
    int max_depth;
    int num_features;

    float gini_score(int pos_score, int neg_score);
    const std::pair<int,int> count(const std::vector<float>& y) const;

private:

    std::pair<int, int> best_split(const DataSet& data) const;
    const std::vector<float> thresholds(const std::vector<float>& X) const;


};
}
#endif // DECISIONTREE_H
