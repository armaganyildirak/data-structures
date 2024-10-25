#include <iostream>
#include <stdexcept>
#include <stack>
#include "tree.h"

template <typename T>
Tree<T>::Tree() : root(nullptr) {}

template <typename T>
Tree<T>::~Tree() {
    if (root == nullptr) {
        return;
    }
    std::stack<TreeNode*> node_stack;
    node_stack.push(root);
    while (!node_stack.empty()) {
        TreeNode *current = node_stack.top();
        node_stack.pop();

        if (current->left != nullptr) {
            node_stack.push(current->left);
        }
        if (current->right != nullptr) {
            node_stack.push(current->right);
        }

        delete current;
    }
    root = nullptr;
}

template <typename T>
void Tree<T>::insert_node(const T &data) {
    TreeNode *new_node = new TreeNode;
    if (new_node == nullptr) {
        throw std::runtime_error("Error - Memory allocation failed");
    }

    new_node->data = data;
    new_node->left = nullptr;
    new_node->right = nullptr;

    if (root == nullptr) {
        root = new_node;
        return;
    }

    TreeNode *temp = root;
    TreeNode *parent = nullptr;

    while (temp != nullptr) {
        parent = temp;
        if (data < temp->data) {
            temp = temp->left;
        } else if (data > temp->data) {
            temp = temp->right;
        } else {
            throw std::runtime_error("Error - cannot insert existing node");
        }
    }

    if (data < parent->data) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
}

template <typename T>
void Tree<T>::delete_node(const T &data) {
    if (root == nullptr) {
        throw std::runtime_error("Error - tree is empty");
    }

    TreeNode *parent = nullptr;
    TreeNode *current = root;

    while (current != nullptr && data != current->data) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == nullptr) {
        throw std::runtime_error("Error - data not found");
    }

    if (current->left == nullptr && current->right == nullptr) {
        if (current == root) {
            root = nullptr;
        } else if (parent->left == current) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete current;
    } else if (current->left == nullptr || current->right == nullptr) {
        TreeNode *child = (current->left != nullptr) ? current->left : current->right;

        if (current == root) {
            root = child;
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        delete current;
    } else {
        TreeNode *temp_parent = current;
        TreeNode *temp = current->right;

        while (temp->left != nullptr) {
            temp_parent = temp;
            temp = temp->left;
        }

        current->data = temp->data;

        if (temp_parent->left == temp) {
            temp_parent->left = temp->right;
        } else {
            temp_parent->right = temp->right;
        }

        delete temp;
    }
}
