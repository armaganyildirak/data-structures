#ifndef TREE_H
#define TREE_H

struct tree_node {
    void *data;
    struct tree_node *left;
    struct tree_node *right;
};

struct tree {
    struct tree_node *root;
};

#define NUMBER_OF_INPUTS 100

struct tree *init_tree();
struct tree_node *create_node(void *data);
void insert_node(struct tree *tree, void *data);
void delete_node(struct tree *tree, void *data);
void free_tree(struct tree *tree);
void print_tree(struct tree_node* node);
#endif // TREE_H