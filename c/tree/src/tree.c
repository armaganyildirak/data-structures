#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GREATER 1
#define SMALLER 2
#define EQUAL 3
#define NOTEQUAL 4

struct tree *init_tree(enum data_type type) {
    struct tree *tree = (struct tree *)malloc(sizeof(struct tree));
    if (tree == NULL) {
        perror("Error - malloc failed");
        exit(EXIT_FAILURE);
    }
    tree->root = NULL;
    tree->type = type;
    tree->size = 0;
    return tree;
}
int set_data(enum data_type type, struct tree_node *node, void *data) {
    switch (type) {
    case INT:
        node->int_val = *(int *)data;
        break;
    case FLOAT:
        node->float_val = *(float *)data;
        break;
    case DOUBLE:
        node->double_val = *(double *)data;
        break;
    case CHAR:
        node->char_val = *(char *)data;
        break;
    case LONG:
        node->long_val = *(long *)data;
        break;
    case SHORT:
        node->short_val = *(short *)data;
        break;
    case STRING:
        node->string_val = (char *)malloc(strlen((char *)data) + 1);
        if (!node->string_val) {
            return TREE_ERROR_MALLOC;
        }
        strncpy(node->string_val, (char *)data, strlen((char *)data) + 1);
        break;
    default:
        return TREE_ERROR_TYPE_MISMATCH;
    }
    return TREE_SUCCESS;
}

int compare(enum data_type type, struct tree_node *node, void *data) {
    switch (type) {
    case INT:
        return node->int_val > *(int *)data ? SMALLER : GREATER;
        break;
    case FLOAT:
        return node->float_val > *(float *)data ? SMALLER : GREATER;
        break;
    case DOUBLE:
        return node->double_val > *(double *)data ? SMALLER : GREATER;
        break;
    case CHAR:
        return node->char_val > *(char *)data ? SMALLER : GREATER;
        break;
    case LONG:
        return node->long_val > *(long *)data ? SMALLER : GREATER;
        break;
    case SHORT:
        return node->short_val > *(short *)data ? SMALLER : GREATER;
        break;
    case STRING:
        return strcmp(node->string_val, (char *)data) > 0 ? SMALLER : GREATER;
        break;
    default:
        return TREE_ERROR_TYPE_MISMATCH;
    }
}

int insert_node(struct tree *tree, void *data) {
    struct tree_node *new_node =
        (struct tree_node *)malloc(sizeof(struct tree_node));
    if (new_node == NULL) {
        perror("Error - malloc failed");
        return TREE_ERROR_MALLOC;
    }
    new_node->right = NULL;
    new_node->left = NULL;

    int set_result = set_data(tree->type, new_node, data);
    if (set_result != TREE_SUCCESS) {
        free(new_node);
        return set_result;
    }

    if (tree->root == NULL) {
        tree->root = new_node;
        tree->size++;
        return TREE_SUCCESS;
    }

    struct tree_node *temp = tree->root;
    struct tree_node *parent = NULL;

    while (temp != NULL) {
        parent = temp;
        if (compare(tree->type, temp, data) == SMALLER) {
            temp = temp->left;
        } else if (compare(tree->type, temp, data) == GREATER) {
            temp = temp->right;
        } else {
            printf("Error - cannot insert existing node");
            return TREE_ERROR_EXISTING_DATA;
        }
    }

    if (compare(tree->type, parent, data) == SMALLER) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }

    tree->size++;
    return TREE_SUCCESS;
}

int is_equal(enum data_type type, struct tree_node *node, void *data) {
    switch (type) {
    case INT:
        return node->int_val == *(int *)data ? EQUAL : NOTEQUAL;
        break;
    case FLOAT:
        return node->float_val == *(float *)data ? EQUAL : NOTEQUAL;
        break;
    case DOUBLE:
        return node->double_val == *(double *)data ? EQUAL : NOTEQUAL;
        break;
    case CHAR:
        return node->char_val == *(char *)data ? EQUAL : NOTEQUAL;
        break;
    case LONG:
        return node->long_val == *(long *)data ? EQUAL : NOTEQUAL;
        break;
    case SHORT:
        return node->short_val == *(short *)data ? EQUAL : NOTEQUAL;
        break;
    case STRING:
        return strcmp(node->string_val, (char *)data) == 0 ? EQUAL : NOTEQUAL;
        break;
    default:
        return TREE_ERROR_TYPE_MISMATCH;
    }
}

void copy_value(enum data_type type, struct tree_node *dst, struct tree_node *src) {
    switch (type) {
    case INT:
        dst->int_val = src->int_val;
        break;
    case FLOAT:
        dst->int_val = src->int_val;
        break;
    case DOUBLE:
        dst->int_val = src->int_val;
        break;
    case CHAR:
        dst->int_val = src->int_val;
        break;
    case LONG:
        dst->int_val = src->int_val;
        break;
    case SHORT:
        dst->int_val = src->int_val;
        break;
    case STRING:
        if (dst->string_val == NULL || src->string_val == NULL) return;
        unsigned long size_of_str = strlen(dst->string_val) > strlen(src->string_val) ? strlen(dst->string_val) : strlen(src->string_val);
        strncpy(dst->string_val, src->string_val, size_of_str);
        break;
    default:
        break;
    }
}

int delete_node(struct tree *tree, void *data) {
    if (tree == NULL || tree->root == NULL) {
        printf("Error - tree is empty.\n");
        return TREE_ERROR_EMPTY;
    }

    struct tree_node *parent = NULL;
    struct tree_node *current = tree->root;

    while (current != NULL && is_equal(tree->type, current, data) == NOTEQUAL) {
        parent = current;
        if (compare(tree->type, current, data) == SMALLER) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        printf("Error - data not found.\n");
        return TREE_ERROR_DATA_NOT_FOUND;
    }

    if (current->left == NULL && current->right == NULL) {
        if (current == tree->root) {
            tree->root = NULL;
        } else if (parent->left == current) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        if (tree->type == STRING && current->string_val != NULL) {
            free(current->string_val);
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
        if (tree->type == STRING && current->string_val != NULL) {
            free(current->string_val);
        }
        free(current);
    } else {
        struct tree_node *temp_parent = current;
        struct tree_node *temp = current->right;

        while (temp->left != NULL) {
            temp_parent = temp;
            temp = temp->left;
        }

        copy_value(tree->type, current, temp);

        if (temp_parent->left == temp) {
            temp_parent->left = temp->right;
        } else {
            temp_parent->right = temp->right;
        }

        free(temp);
    }

    tree->size--;
    return TREE_SUCCESS;
}

void free_tree(struct tree *tree) {
    if (tree == NULL) {
        printf("tree is empty!\n");
        return;
    }

    struct tree_node **stack = (struct tree_node **)malloc(
        sizeof(struct tree_node *) * tree->size);
    int top = -1;

    struct tree_node *current = tree->root;

    while (current != NULL || top >= 0) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        struct tree_node *right = current->right;
        if (tree->type == STRING && current->string_val != NULL) {
            free(current->string_val);
        }
        free(current);
        current = right;
    }

    free(stack);

    free(tree);
}

void print_node(struct tree_node *node, enum data_type type) {
    switch (type) {
    case INT:
        printf("%d -> ", node->int_val);
        break;
    case FLOAT:
        printf("%f -> ", node->float_val);
        break;
    case STRING:
        printf("%s -> ", node->string_val);
        break;
    case DOUBLE:
        printf("%lf -> ", node->double_val);
        break;
    case CHAR:
        printf("%c -> ", node->char_val);
        break;
    case LONG:
        printf("%ld -> ", node->long_val);
        break;
    case SHORT:
        printf("%d -> ", node->short_val);
        break;
    default:
        break;
    }
}

void print_tree(struct tree *tree) {
    if (tree->root == NULL) {
        printf("tree is empty!\n");
        return;
    }

    struct tree_node **stack = (struct tree_node **)malloc(
        sizeof(struct tree_node *) * tree->size);
    int top = -1;

    struct tree_node *current = tree->root;

    while (current != NULL || top >= 0) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];
        print_node(current, tree->type);
        current = current->right;
    }
    printf("\n");
}
