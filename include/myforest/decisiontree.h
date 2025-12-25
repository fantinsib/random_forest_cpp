#ifndef DECISIONTREE_H
#define DECISIONTREE_H
#include <iostream>
#include <iomanip>
#include <stdexcept>

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
    bool found_a_split;

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
    bool fitted = false; 

    //Functions
    void fit(const DataSet& data, bool in_rf=false, int m_try = -1);
    void print_tree() const;
    std::vector<int> predict(const std::vector<float>& s);


private:

    int iterate_tree(Node& node, const std::vector<float>& s) const; //Recursion called by .predict()
    SplitResult best_split(const DataSet& data, bool in_rf=false, int m_try=-1) const; //Returns best gini split of a DataSet
    const std::vector<float> get_thresholds(const DataSet& data, int t_col) const; //returns vector of thresholds
    void build_tree(Node& node, const DataSet& data, int depth, bool in_rf, int m_try) const; //recursion called by .fit()
    float gini_score(int pos_score, int neg_score) const; //computes Gini for a node given the number of pos classes and number of neg classes
    const std::pair<int,int> count(const std::vector<float>& y) const; //counts the number of positive & negative classes in a y vector
    void print_tree_rec(const Node& node, const std::string& prefix, bool is_left, bool is_last) const;
};
}
#endif // DECISIONTREE_H
