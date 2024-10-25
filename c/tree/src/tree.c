#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GREATER 1
#define SMALLER 2
#define EQUAL 3

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
        if (node->int_val < *(int *)data)
            return GREATER;
        if (node->int_val > *(int *)data)
            return SMALLER;
        return EQUAL;
    case FLOAT:
        if (node->float_val < *(float *)data)
            return GREATER;
        if (node->float_val > *(float *)data)
            return SMALLER;
        return EQUAL;
    case DOUBLE:
        if (node->double_val < *(double *)data)
            return GREATER;
        if (node->double_val > *(double *)data)
            return SMALLER;
        return EQUAL;
    case CHAR:
        if (node->char_val < *(char *)data)
            return GREATER;
        if (node->char_val > *(char *)data)
            return SMALLER;
        return EQUAL;
    case LONG:
        if (node->long_val < *(long *)data)
            return GREATER;
        if (node->long_val > *(long *)data)
            return SMALLER;
        return EQUAL;
    case SHORT:
        if (node->short_val < *(short *)data)
            return GREATER;
        if (node->short_val > *(short *)data)
            return SMALLER;
        return EQUAL;
    case STRING:
        if (node->string_val == NULL || data == NULL) {
            return TREE_ERROR_NULL;
        }
        int cmp = strcmp(node->string_val, (char *)data);
        if (cmp < 0)
            return GREATER;
        if (cmp > 0)
            return SMALLER;
        return EQUAL;
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
        int cmp_result = compare(tree->type, temp, data);
        if (cmp_result == SMALLER) {
            temp = temp->left;
        } else if (cmp_result == GREATER) {
            temp = temp->right;
        } else {
            fprintf(stderr, "Error - cannot insert existing node\n");
            free(new_node);
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

void copy_value(enum data_type type, struct tree_node *dst,
                struct tree_node *src) {
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
        if (dst->string_val == NULL || src->string_val == NULL)
            return;
        unsigned long size_of_str =
            strlen(dst->string_val) > strlen(src->string_val)
                ? strlen(dst->string_val)
                : strlen(src->string_val);
        strncpy(dst->string_val, src->string_val, size_of_str);
        break;
    default:
        break;
    }
}

int delete_node(struct tree *tree, void *data) {
    if (tree == NULL || tree->root == NULL) {
        fprintf(stderr, "Error - tree is empty.\n");
        return TREE_ERROR_EMPTY;
    }

    struct tree_node *parent = NULL;
    struct tree_node *current = tree->root;

    while (current != NULL && compare(tree->type, current, data) != EQUAL) {
        parent = current;
        if (compare(tree->type, current, data) == SMALLER) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        fprintf(stderr, "Error - data not found.\n");
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
        fprintf(stderr, "tree is empty!\n");
        return;
    }

    struct tree_node **stack =
        (struct tree_node **)malloc(sizeof(struct tree_node *) * tree->size);
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
        fprintf(stderr, "tree is empty!\n");
        return;
    }

    struct tree_node **stack =
        (struct tree_node **)malloc(sizeof(struct tree_node *) * tree->size);
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

int search(struct tree *tree, void *data) {
    if (tree == NULL || tree->root == NULL) {
        fprintf(stderr, "Error - tree is empty.\n");
        return TREE_ERROR_EMPTY;
    }

    struct tree_node *current = tree->root;

    while (current != NULL && compare(tree->type, current, data) != EQUAL) {
        if (compare(tree->type, current, data) == SMALLER) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        return TREE_ERROR_DATA_NOT_FOUND;
    } else {
        return TREE_DATA_FOUND;
    }
}
