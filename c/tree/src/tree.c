#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

struct tree *init_tree() {
    struct tree *tree = (struct tree *)malloc(sizeof(struct tree));
    if (tree == NULL) {
        perror("Error - malloc failed");
        exit(EXIT_FAILURE);
    }
    tree->root = NULL;
    return tree;
}

struct tree_node *create_node(void *data) {
    struct tree_node *new_node =
        (struct tree_node *)malloc(sizeof(struct tree_node));
    if (new_node == NULL) {
        perror("Error - malloc failed");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->right = NULL;
    new_node->left = NULL;

    return new_node;
}

void insert_node(struct tree *tree, void *data) {
    struct tree_node *new_node = create_node(data);
    if (tree->root == NULL) {
        tree->root = new_node;
        return;
    }

    struct tree_node *temp = tree->root;
    struct tree_node *parent = NULL;

    while (temp != NULL) {
        parent = temp;
        if (*(int *)data < *(int *)temp->data) {
            temp = temp->left;
        } else if (*(int *)data > *(int *)temp->data) {
            temp = temp->right;
        } else {
            printf("Error - cannot insert existing node");
            return;
        }
    }

    if (*(int *)data < *(int *)parent->data) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
}

void delete_node(struct tree *tree, void *data) {
    if (tree == NULL || tree->root == NULL) {
        printf("Error - tree is empty.\n");
        return;
    }

    struct tree_node *parent = NULL;
    struct tree_node *current = tree->root;

    while (current != NULL && *(int *)data != *(int *)current->data) {
        parent = current;
        if (*(int *)data < *(int *)current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        printf("Error - data not found.\n");
        return;
    }

    if (current->left == NULL && current->right == NULL) {
        if (current == tree->root) {
            tree->root = NULL;
        } else if (parent->left == current) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(current);
    } else if (current->left == NULL || current->right == NULL) {
        struct tree_node *child = NULL;
        if (current->left != NULL) {
            child = current->left;
        } else {
            child = current->right;
        }
        if (current == tree->root) {
            tree->root = child;
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        free(current);
    } else {
        struct tree_node *temp_parent = current;
        struct tree_node *temp = current->right;

        while (temp->left != NULL) {
            temp_parent = temp;
            temp = temp->left;
        }

        current->data = temp->data;

        if (temp_parent->left == temp) {
            temp_parent->left = temp->right;
        } else {
            temp_parent->right = temp->right;
        }

        free(temp);
    }
}

void free_tree(struct tree *tree) {
    if (tree == NULL) {
        printf("tree is empty!\n");
        return;
    }

    struct tree_node **stack = (struct tree_node **)malloc(
        sizeof(struct tree_node *) * NUMBER_OF_INPUTS);
    int top = -1;

    struct tree_node *current = tree->root;

    while (current != NULL || top >= 0) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        struct tree_node *right = current->right;
        free(current);
        current = right;
    }

    free(stack);

    free(tree);
}

void print_tree(struct tree_node *node) {
    if (node == NULL) {
        printf("tree is empty!\n");
        return;
    }

    struct tree_node *stack[NUMBER_OF_INPUTS];
    int top = -1;

    struct tree_node *current = node;

    while (current != NULL || top >= 0) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];
        printf("%d ", *(int *)current->data);
        current = current->right;
    }
    printf("\n");
}
