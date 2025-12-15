#ifndef NODE_H
#define NODE_H
#include <memory>

namespace myforest{
class Node
{
public:
    Node();
    int feature_index;
    float threshold;

    int return_feature_index() const;
    float return_threshold() const;

    std::unique_ptr<Node> left_child;
    std::unique_ptr<Node> right_child;
};
}
#endif // NODE_H
