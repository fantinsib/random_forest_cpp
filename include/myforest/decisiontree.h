#ifndef DECISIONTREE_H
#define DECISIONTREE_H
#include <iostream>
#include <iomanip>
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
    //Constructor
    DecisionTree(int max_depth);

    //attributes
    int max_depth;
    int num_features;
    Node root_node;

    //Functions
    void fit(const DataSet& data);
    void print_tree() const;
    int predict(const std::vector<float>& s);


private:

    int iterate_tree(Node& node, const std::vector<float>& s) const; //Recursion called by .predict()
    SplitResult best_split(const DataSet& data) const; //Returns best gini split of a DataSet
    const std::vector<float> get_thresholds(const DataSet& data, int t_col) const; //returns vector of thresholds
    void build_tree(Node& node, const DataSet& data, int depth) const; //recursion called by .fit()
    float gini_score(int pos_score, int neg_score) const; //computes Gini for a node given the number of pos classes and number of neg classes
    const std::pair<int,int> count(const std::vector<float>& y) const; //counts the number of positive & negative classes in a y vector
    void print_tree_rec(const Node& node, const std::string& prefix, bool is_left, bool is_last) const;
};
}
#endif // DECISIONTREE_H
