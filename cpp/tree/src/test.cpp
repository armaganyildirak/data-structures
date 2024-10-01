#include "tree.h"
#include <cassert>
#include <iostream>

void test_insert_into_empty_tree() {
  Tree<int> tree;
  int value = 10;
  tree.insert_node(value);

  assert(tree.root != NULL);
  assert(tree.root->data == 10);

  std::cout << "test_insert_into_empty_tree passed!" << std::endl;
}

void test_insert_multiple_nodes() {
  Tree<int> tree;
  int values[] = {10, 5, 15, 3, 7, 12, 18};

  for (int i = 0; i < 7; i++) {
    tree.insert_node(values[i]);
  }

  assert(tree.root->data == 10);
  assert(tree.root->left->data == 5);
  assert(tree.root->right->data == 15);
  assert(tree.root->left->left->data == 3);
  assert(tree.root->left->right->data == 7);
  assert(tree.root->right->left->data == 12);
  assert(tree.root->right->right->data == 18);

  std::cout << "test_insert_multiple_nodes passed!" << std::endl;
}

void test_delete_leaf_node() {
  Tree<int> tree;

  int val1 = 10, val2 = 5, val3 = 15;
  tree.insert_node(val1);
  tree.insert_node(val2);
  tree.insert_node(val3);

  tree.delete_node(val3);

  assert(tree.root != NULL);
  assert(tree.root->data == 10);
  assert(tree.root->right == NULL);
  std::cout << "test_delete_leaf_node passed!" << std::endl;
}

void test_delete_node_with_one_child() {
  Tree<int> tree;

  int val1 = 10, val2 = 5, val3 = 15, val4 = 12;
  tree.insert_node(val1);
  tree.insert_node(val2);
  tree.insert_node(val3);
  tree.insert_node(val4);

  tree.delete_node(val3);

  assert(tree.root != NULL);
  assert(tree.root->data == 10);
  assert(tree.root->right != NULL);
  assert(tree.root->right->data == 12);
  std::cout << "test_delete_node_with_one_child passed!" << std::endl;
}

void test_delete_node_with_two_children() {
  Tree<int> tree;

  int val1 = 10, val2 = 5, val3 = 15, val4 = 12, val5 = 20;
  tree.insert_node(val1);
  tree.insert_node(val2);
  tree.insert_node(val3);
  tree.insert_node(val4);
  tree.insert_node(val5);

  tree.delete_node(val3);

  assert(tree.root != NULL);
  assert(tree.root->data == 10);
  assert(tree.root->right != NULL);
  assert(tree.root->right->data == 20);
  std::cout << "test_delete_node_with_two_children passed!" << std::endl;
}

void test_delete_root_node() {
  Tree<int> tree;

  int val1 = 10, val2 = 5, val3 = 15;
  tree.insert_node(val1);
  tree.insert_node(val2);
  tree.insert_node(val3);

  tree.delete_node(val1);

  assert(tree.root != NULL);
  assert(tree.root->data == 15);
  assert(tree.root->left != NULL);
  assert(tree.root->left->data == 5);
  std::cout << "test_delete_root_node passed!\n" << std::endl;
}

int main() {
  test_insert_into_empty_tree();
  test_insert_multiple_nodes();
  test_delete_leaf_node();
  test_delete_node_with_one_child();
  test_delete_node_with_two_children();
  test_delete_root_node();

  std::cout << "All tests passed!" << std::endl;
  return 0;
}