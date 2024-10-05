#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

enum data_type { 
    INT,
    FLOAT,
    STRING,
    DOUBLE,
    CHAR,
    LONG,
    SHORT,
};

struct tree_node {
    union {
        int int_val;
        float float_val;
        char *string_val;
        double double_val;
        char char_val;
        long long_val;
        short short_val;
        bool bool_val;
        void *pointer_val;
    };
    struct tree_node *left;
    struct tree_node *right;
};

struct tree {
    struct tree_node *root;
    enum data_type type;
    int size;
};

enum tree_error_code {
    TREE_SUCCESS = 0,
    TREE_ERROR_NULL = -1,
    TREE_ERROR_EMPTY = -2,
    TREE_ERROR_MALLOC = -3,
    TREE_ERROR_TYPE_MISMATCH = -4,
    TREE_ERROR_EXISTING_DATA = -5,
    TREE_ERROR_DATA_NOT_FOUND = -6
};

struct tree *init_tree(enum data_type type);
int insert_node(struct tree *tree, void *data);
int delete_node(struct tree *tree, void *data);
void free_tree(struct tree *tree);
void print_tree(struct tree *tree);
#endif // TREE_H