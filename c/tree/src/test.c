#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"

void test_tree_int() {
    struct tree *int_tree = init_tree(INT);

    int val1 = 10, val2 = 5, val3 = 15, val4 = 20, val5 = 25; 

    assert(insert_node(int_tree, &val1) == TREE_SUCCESS);
    assert(insert_node(int_tree, &val2) == TREE_SUCCESS);
    assert(insert_node(int_tree, &val3) == TREE_SUCCESS);
    assert(insert_node(int_tree, &val4) == TREE_SUCCESS);
    assert(insert_node(int_tree, &val5) == TREE_SUCCESS);

    assert(int_tree->size == 5);

    assert(int_tree->root->int_val == val1);

    assert(int_tree->root->left->int_val == val2);
    assert(int_tree->root->right->int_val == val3);

    assert(delete_node(int_tree, &val2) == TREE_SUCCESS);
    assert(int_tree->size == 4);

    free_tree(int_tree);
    printf("test_tree_int passed.\n");
}

void test_tree_string() {
    struct tree *str_tree = init_tree(STRING);

    char *val1 = "banana";
    char *val2 = "apple";
    char *val3 = "cherry";

    assert(insert_node(str_tree, val1) == TREE_SUCCESS);
    assert(insert_node(str_tree, val2) == TREE_SUCCESS);
    assert(insert_node(str_tree, val3) == TREE_SUCCESS);

    assert(str_tree->size == 3);

    assert(strcmp(str_tree->root->string_val, val1) == 0);
    assert(strcmp(str_tree->root->left->string_val, val2) == 0);
    assert(strcmp(str_tree->root->right->string_val, val3) == 0);

    assert(delete_node(str_tree, val2) == TREE_SUCCESS);
    assert(str_tree->size == 2);

    free_tree(str_tree);
    printf("test_tree_string passed.\n");
}

void test_tree_double() {
    struct tree *dbl_tree = init_tree(DOUBLE);

    double val1 = 10.5, val2 = 5.5, val3 = 15.5;

    assert(insert_node(dbl_tree, &val1) == TREE_SUCCESS);
    assert(insert_node(dbl_tree, &val2) == TREE_SUCCESS);
    assert(insert_node(dbl_tree, &val3) == TREE_SUCCESS);

    assert(dbl_tree->size == 3);

    assert(dbl_tree->root->double_val == val1);

    assert(dbl_tree->root->left->double_val == val2);
    assert(dbl_tree->root->right->double_val == val3);

    assert(delete_node(dbl_tree, &val2) == TREE_SUCCESS);
    assert(dbl_tree->size == 2);

    free_tree(dbl_tree);
    printf("test_tree_double passed.\n");
}

int main() {
    test_tree_int();
    test_tree_string();
    test_tree_double();
    
    printf("All tests passed!\n");
    return 0;
}
