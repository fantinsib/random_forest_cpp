#ifndef DECISIONTREE_H
#define DECISIONTREE_H
#include <iostream>
#include <iomanip>
#include <stdexcept>

#include <myforest/dataset.h>
#include <myforest/node.h>


namespace myforest{

/**
 * @brief Result of a split evaluation 
 * 
 * Stores :
 * - the splitting feature and the threshold
 * - the index vector of the samples to the left & right node
 * - is_pure_gini : True if the weighted gini of the split is 0
 * - left_gini and right_gini : the gini of the left and right nodes after the split 
 * - found_a_split : true if at least one split has been found
 */

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
    /**
     * @brief Construct a new Decision Tree object
     * 
     * @param max_depth Maximum allowed depth of the Decision Tree (root depth = 0)
     */
    DecisionTree(int max_depth);

    //attributes
    int max_depth;
    int num_features; // Undefined while tree has not been fitted
    Node root_node;
    bool fitted = false; 

    /**
    * @brief Trains the decision tree on the provided dataset
    *
    * Builds the tree recursively using CART-style splits
    * After calling this method, the tree is fully constructed
    * and ready for prediction
    *
    * @param data Training dataset containing features and labels
    * @param in_rf If true, only a subset of features are considered in each split (random forest mode).
    * A number of `m_try` features are selected randomly among all the features.
    * @param m_try Number of features to consider at each split. If m_try < 0, all features are considered (true by default)
    *
    * @throws std::runtime_error if the dataset has no features
    *
    * @post The tree is fitted and `fitted == true` ; ready for prediction
    */
    void fit(const DataSet& data, bool in_rf=false, int m_try = -1);
    
    /**
     * @brief Outputs a structured representation of the tree once fitted 
     * 
     * @throws std::runtime_error if the function is called before the tree was fitted
     */
    void print_tree() const;

    /**
    * @brief Predicts binary class labels for multiple samples
     * 
     * @param s A flattened 1D vector of the samples to predict (N samples * n features)
     * @return std::vector<int> A vector of 0 and 1 for the prediction in the corresponding order 
     * @throws std::runtime_error if the method is called while fitted is not true or if the size of 
     * the s vector is incoherent with the number of features from the training.
     */
    std::vector<int> predict(const std::vector<float>& s);


private:

    
    /**
     * @brief Returns the predicted class of a single sample
     * 
     * Passes the sample through the tree until a leaf is reached.
     *
     * @param node Current node
     * @param s A flattened vector of a single sample
     * @return int Predicted class label
     * @throws std::logic_error If an unreachable state is encountered (should not happen)
     */
    int iterate_tree(const Node& node, const std::vector<float>& s) const;
    
    /**
     * @brief Computes the minimum Gini split 
     * 
     * @param data DataSet on which to compute the split
     * @param in_rf If true, the optimal split is based only on a random subset of features (random forest mode).
     * A number of `m_try` features are selected randomly among all the features.
     * @param m_try Number of features to consider at each split. If m_try < 0, all features are considered 
     * @return SplitResult The split with the lowest weighted Gini found
     */
    SplitResult best_split(const DataSet& data, bool in_rf=false, int m_try=-1) const; //Returns best gini split of a DataSet

    /**
     * @brief Computes the thresholds to be tested for a given feature
     * 
     * @param data DataSet on which to compute the split
     * @param t_col the column index of the dataset corresponding to the feature
     * @return vector of candidates thresholds computed as the midpoints between two consecutive sorted feature values 
     */
    const std::vector<float> get_thresholds(const DataSet& data, int t_col) const; //returns vector of thresholds
    
    /**
     * @brief Creates a tree structure of nodes
     *
     * From a node, computes the best split given the DataSet.
     * Passes the result of the split to two children nodes or stops if 
     * a stopping condition is met (no split found, max depth reached, pure node)
     * 
     * @param node The node in which the split is calculated
     * @param data The current DataSet 
     * @param depth The current depth of the recursion
     * @param in_rf true if the method is called in a RandomForest. Serves for best_split()
     * @param m_try if in_rf is true, number of features to be picked randomly
     */
    void build_tree(Node& node, const DataSet& data, int depth, bool in_rf, int m_try) const; 
    
    /**
     * @brief Computes Gini given the number of positive and negative labels
     * 
     * @param pos_score the number of samples labeled as positive 
     * @param neg_score the number of samples labeled as negative
     * @return float 
     */
    float gini_score(int pos_score, int neg_score) const; //computes Gini for a node given the number of pos classes and number of neg classes
    
    /**
     * @brief Returns the number of positive and negative labels in target vector
     * 
     * @param y the 1D vector containing the labels
     * @return Pair {count_positive, count_negative} with 
     *         - count_positive the number of labels equal to 1
     *         - count_negative the number of labels equal to 0
     * @throws std::invalid_argument if a non-binary label is in y (not in {0,1})
     */
    std::pair<int,int> count(const std::vector<float>& y) const; 
    
    /**
     * @brief Helper function for printing the tree
     * 
     * @param node Current node
     * @param prefix inherited prefix from parent
     * @param is_left 
     * @param is_last 
     */
    void print_tree_rec(const Node& node, const std::string& prefix, bool is_left, bool is_last) const;
};
}
#endif // DECISIONTREE_H
