#ifndef DECISIONTREE_H
#define DECISIONTREE_H

class DecisionTree
{
public:
    DecisionTree(int max_depth);
    int max_depth;
    int num_features;

    float gini_score(int k, float p);
};

#endif // DECISIONTREE_H
