#ifndef DECISIONTREE_H
#define DECISIONTREE_H
#include <iostream>
#include <myforest/dataset.h>
#include <myforest/node.h>


namespace myforest{

struct SplitResult{

    int feature;
    float threshold;
    std::vector<int> left_index;
    std::vector<int> right_index;
    bool is_pure_gini = false;

};


class DecisionTree
{
public:
    DecisionTree(int max_depth);
    int max_depth;
    int num_features;

    float gini_score(int pos_score, int neg_score) const;
    const std::pair<int,int> count(const std::vector<float>& y) const;
    void build_tree(Node& node, const DataSet& data) const;
    void print_tree(Node& node, int depth);

//private:

    SplitResult best_split(const DataSet& data) const;
    const std::vector<float> thresholds(const std::vector<float>& X) const;





};
}
#endif // DECISIONTREE_H
