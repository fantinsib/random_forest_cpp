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
    float left_gini;
    float right_gini;

};


class DecisionTree
{
public:
    DecisionTree(int max_depth);
    int max_depth;
    int num_features;
    Node root_node;

    void fit(const DataSet& data);
    float gini_score(int pos_score, int neg_score) const;
    const std::pair<int,int> count(const std::vector<float>& y) const;
    void print_tree(Node& node, int depth);
    int predict(const std::vector<float>& s);


private:

    int iterate_tree(Node& node, const std::vector<float>& s) const;
    SplitResult best_split(const DataSet& data) const;
    const std::vector<float> get_thresholds(const DataSet& data, int t_col) const;
    void build_tree(Node& node, const DataSet& data) const;

};
}
#endif // DECISIONTREE_H
