#ifndef TREE_H
#define TREE_H

template <typename T>
class Tree {
public:
    struct TreeNode {
        T data;
        TreeNode *left;
        TreeNode *right;
    };

    TreeNode *root;

public:
    Tree();
    ~Tree();

    void insert_node(const T &data);

    void delete_node(const T &data);
};

#include "tree.tpp"

#endif // TREE_H