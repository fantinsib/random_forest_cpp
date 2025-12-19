#ifndef NODE_H
#define NODE_H
#include <memory>
#include <vector>

namespace myforest{
class Node
{
public:
    Node();
    int feature_index;
    float threshold;
    int predicted_class;

    bool is_leaf = true;

    int return_feature_index() const;
    float return_threshold() const;
    int node_id = rand() % 1000 + 1;

    std::vector<int> rows;

    std::unique_ptr<Node> left_child;
    std::unique_ptr<Node> right_child;
};
}
#endif // NODE_H
