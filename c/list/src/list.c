#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list *init_list(enum data_type type) {
    struct list *list = (struct list *)malloc(sizeof(struct list));
    if (list == NULL) {
        perror("Error - malloc failed");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->type = type;
    list->size = 0;
    return list;
}

int set_data(enum data_type type, struct list_node *node, void *data) {
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
    case BOOL:
        node->bool_val = *(bool *)data;
        break;
    case STRING:
        node->string_val = (char *)malloc(strlen((char *)data) + 1);
        if (!node->string_val) {
            return LIST_ERROR_MALLOC;
        }
        strncpy(node->string_val, (char *)data, strlen((char *)data) + 1);
        break;
    case POINTER:
        node->pointer_val = data;
        break;
    default:
        return LIST_ERROR_TYPE_MISMATCH;
    }
    return LIST_SUCCESS;
}

int insert_node(struct list *list, void *data, int idx) {
    if (list == NULL) {
        fprintf(stderr, "Error - list is NULL in insert_node\n");
        return LIST_ERROR_NULL;
    }

    struct list_node *new_node =
        (struct list_node *)malloc(sizeof(struct list_node));
    if (new_node == NULL) {
        perror("Error - malloc failed in insert_node");
        return LIST_ERROR_MALLOC;
    }

    new_node->next = NULL;
    new_node->prev = NULL;

    int set_result = set_data(list->type, new_node, data);
    if (set_result != LIST_SUCCESS) {
        free(new_node);
        return set_result;
    }

    if (idx < 0 || idx > list->size) {
        fprintf(stderr, "Error - index out of bounds in insert_node\n");
        free(new_node);
        return LIST_ERROR_INDEX_OUT_OF_BOUNDS;
    }

    if (idx == 0) {
        if (list->head != NULL) {
            new_node->next = list->head;
            list->head->prev = new_node;
        }
        list->head = new_node;
    } else {
        struct list_node *current = list->head;
        for (int i = 0; i < idx - 1; i++) {
            current = current->next;
        }
        new_node->next = current->next;
        new_node->prev = current;

        if (current->next != NULL) {
            current->next->prev = new_node;
        }
        current->next = new_node;
    }

    list->size++;
    return LIST_SUCCESS;
}

int append(struct list *list, void *data) {
    if (list == NULL) {
        fprintf(stderr, "Error - list is NULL in insert_node\n");
        return LIST_ERROR_NULL;
    }

    struct list_node *new_node =
        (struct list_node *)malloc(sizeof(struct list_node));
    if (new_node == NULL) {
        perror("Error - malloc failed in insert_node");
        return LIST_ERROR_MALLOC;
    }

    new_node->next = NULL;
    new_node->prev = NULL;

    int set_result = set_data(list->type, new_node, data);
    if (set_result != LIST_SUCCESS) {
        free(new_node);
        return set_result;
    }

    struct list_node *current = list->head;
    while (current->next != NULL ) {
        current = current->next;
    }

    current->next = new_node;
    new_node->prev = current;

    list->size++;
    return LIST_SUCCESS;
}

int prepend(struct list *list, void *data) {
    if (list == NULL) {
        fprintf(stderr, "Error - list is NULL in insert_node\n");
        return LIST_ERROR_NULL;
    }

    struct list_node *new_node =
        (struct list_node *)malloc(sizeof(struct list_node));
    if (new_node == NULL) {
        perror("Error - malloc failed in insert_node");
        return LIST_ERROR_MALLOC;
    }

    new_node->next = NULL;
    new_node->prev = NULL;

    int set_result = set_data(list->type, new_node, data);
    if (set_result != LIST_SUCCESS) {
        free(new_node);
        return set_result;
    }

    new_node->next = list->head;

    if (list->head != NULL) {
        list->head->prev = new_node;
    }

    list->head = new_node;

    list->size++;
    return LIST_SUCCESS;
}

int delete_node(struct list *list, int idx) {
    if (list == NULL) {
        fprintf(stderr, "Error - list is NULL in delete_node\n");
        return LIST_ERROR_NULL;
    }
    if (list->head == NULL) {
        fprintf(stderr, "Error - list is empty in delete_node\n");
        return LIST_ERROR_EMPTY;
    }
    if (idx < 0 || idx >= list->size) {
        fprintf(stderr, "Error - index out of bounds in delete_node\n");
        return LIST_ERROR_INDEX_OUT_OF_BOUNDS;
    }

    struct list_node *current = list->head;

    for (int i = 0; i < idx; i++) {
        current = current->next;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        list->head = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    if (list->type == STRING) {
        free(current->string_val);
    }

    free(current);
    list->size--;
    return LIST_SUCCESS;
}

void free_list(struct list *list) {
    struct list_node *temp = list->head;
    while (temp != NULL) {
        struct list_node *next_node = temp->next;

        if (list->type == STRING && temp->string_val != NULL) {
            free(temp->string_val);
        }

        free(temp);
        temp = next_node;
    }
    free(list);
}

void print_node(struct list_node *node, enum data_type type) {
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
    case BOOL:
        printf("%s -> ", node->bool_val ? "true" : "false");
        break;
    case POINTER:
        printf("%p -> ", node->pointer_val);
        break;
    default:
        break;
    }
}

void print_list(const struct list *list) {
    if (list == NULL) {
        fprintf(stderr, "Error - stack is NULL in print_list\n");
        return;
    }

    struct list_node *current = list->head;
    while (current != NULL) {
        print_node(current, list->type);
        current = current->next;
    }
    printf("NULL\n");
}

int search(struct list *list, void *data) {
    if (list == NULL || data == NULL) {
        return LIST_ERROR_DATA_NOT_FOUND; // Return error if list or data is
                                          // NULL
    }

    struct list_node *temp = list->head;
    int idx = 0;
    while (temp != NULL) {
        switch (list->type) {
        case INT:
            if (temp->int_val == *(int *)data) {
                return idx;
            }
            break;
        case FLOAT:
            if (temp->float_val == *(float *)data) {
                return idx;
            }
            break;
        case STRING:
            if (strcmp(temp->string_val, (char *)data) == 0) {
                return idx;
            }
            break;
        case DOUBLE:
            if (temp->double_val == *(double *)data) {
                return idx;
            }
            break;
        case CHAR:
            if (temp->char_val == *(char *)data) {
                return idx;
            }
            break;
        case LONG:
            if (temp->long_val == *(long *)data) {
                return idx;
            }
            break;
        case SHORT:
            if (temp->short_val == *(short *)data) {
                return idx;
            }
            break;
        case BOOL:
            if (temp->bool_val == *(bool *)data) {
                return idx;
            }
            break;
        case POINTER:
            if (temp->pointer_val == data) {
                return idx;
            }
            break;
        default:
            break;
        }
        idx++;
        temp = temp->next;
    }
    return LIST_ERROR_DATA_NOT_FOUND;
}