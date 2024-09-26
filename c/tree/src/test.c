#include "tree.h"
#include <assert.h>
#include <stdio.h>

void test_insert_into_empty_tree() {
    struct tree *tree = init_tree();
    int value = 10;
    insert_node(tree, &value);

    assert(tree->root != NULL);
    assert(*(int *)tree->root->data == 10);

    printf("test_insert_into_empty_tree passed!\n");
    free_tree(tree);
}

void test_insert_multiple_nodes() {
    struct tree *tree = init_tree();
    int values[] = {10, 5, 15, 3, 7, 12, 18};

    for (int i = 0; i < 7; i++) {
        insert_node(tree, &values[i]);
    }

    assert(*(int *)tree->root->data == 10);
    assert(*(int *)tree->root->left->data == 5);
    assert(*(int *)tree->root->right->data == 15);
    assert(*(int *)tree->root->left->left->data == 3);
    assert(*(int *)tree->root->left->right->data == 7);
    assert(*(int *)tree->root->right->left->data == 12);
    assert(*(int *)tree->root->right->right->data == 18);

    print_tree(tree->root);
    printf("test_insert_multiple_nodes passed!\n");
    free_tree(tree);
}

void test_prevent_duplicate_insert() {
    struct tree *tree = init_tree();
    int value1 = 10;
    int value2 = 10;

    insert_node(tree, &value1);
    insert_node(tree, &value2);

    assert(*(int *)tree->root->data == 10);
    assert(tree->root->left == NULL);
    assert(tree->root->right == NULL);

    printf("test_prevent_duplicate_insert passed!\n");
    free_tree(tree);
}

void test_delete_leaf_node() {
    struct tree *tree = init_tree();

    int val1 = 10, val2 = 5, val3 = 15;
    insert_node(tree, &val1);
    insert_node(tree, &val2);
    insert_node(tree, &val3);

    delete_node(tree, &val3);

    assert(tree->root != NULL);
    assert(*(int *)tree->root->data == 10);
    assert(tree->root->right == NULL);
    printf("test_delete_leaf_node passed!\n");
    free_tree(tree);
}

void test_delete_node_with_one_child() {
    struct tree *tree = init_tree();

    int val1 = 10, val2 = 5, val3 = 15, val4 = 12;
    insert_node(tree, &val1);
    insert_node(tree, &val2);
    insert_node(tree, &val3);
    insert_node(tree, &val4);

    delete_node(tree, &val3);

    assert(tree->root != NULL);
    assert(*(int *)tree->root->data == 10);
    assert(tree->root->right != NULL);
    assert(*(int *)tree->root->right->data == 12);
    printf("test_delete_node_with_one_child passed!\n");
    free_tree(tree);
}

void test_delete_node_with_two_children() {
    struct tree *tree = init_tree();

    int val1 = 10, val2 = 5, val3 = 15, val4 = 12, val5 = 20;
    insert_node(tree, &val1);
    insert_node(tree, &val2);
    insert_node(tree, &val3);
    insert_node(tree, &val4);
    insert_node(tree, &val5);

    delete_node(tree, &val3);

    assert(tree->root != NULL);
    assert(*(int *)tree->root->data == 10);
    assert(tree->root->right != NULL);
    assert(*(int *)tree->root->right->data == 20);
    printf("test_delete_node_with_two_children passed!\n");
    free_tree(tree);
}

void test_delete_root_node() {
    struct tree *tree = init_tree();

    int val1 = 10, val2 = 5, val3 = 15;
    insert_node(tree, &val1);
    insert_node(tree, &val2);
    insert_node(tree, &val3);

    delete_node(tree, &val1);

    assert(tree->root != NULL);
    assert(*(int *)tree->root->data == 15);
    assert(tree->root->left != NULL);
    assert(*(int *)tree->root->left->data == 5);
    printf("test_delete_root_node passed!\n");
    free_tree(tree);
}

void test_delete_empty_tree() {
    struct tree *tree = init_tree();
    int val = 10;

    delete_node(tree, &val);
    assert(tree->root == NULL);
    printf("test_delete_empty_tree passed!\n");
    free_tree(tree);
}

void test_delete_nonexistent_node() {
    struct tree *tree = init_tree();

    int val1 = 10, val2 = 5, val3 = 15, val4 = 20;
    insert_node(tree, &val1);
    insert_node(tree, &val2);
    insert_node(tree, &val3);

    delete_node(tree, &val4);

    assert(tree->root != NULL);
    assert(*(int *)tree->root->data == 10);
    assert(*(int *)tree->root->right->data == 15);
    printf("test_delete_nonexistent_node passed!\n");
    free_tree(tree);
}

int main() {
    test_insert_into_empty_tree();
    test_insert_multiple_nodes();
    test_prevent_duplicate_insert();
    test_delete_leaf_node();
    test_delete_node_with_one_child();
    test_delete_node_with_two_children();
    test_delete_root_node();
    test_delete_empty_tree();
    test_delete_nonexistent_node();

    printf("All tests passed!\n");
    return 0;
}