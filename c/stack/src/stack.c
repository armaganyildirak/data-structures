#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack *new_stack(enum data_type type) {
    struct stack *stack = (struct stack *)malloc(sizeof(struct stack));
    if (stack == NULL) {
        perror("Error - malloc failed in new_stack");
        return NULL;
    }
    stack->type = type;
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

bool is_empty(const struct stack *stack) {
    if (stack == NULL) {
        fprintf(stderr, "Error - stack is NULL in is_empty\n");
        return false;
    }
    return stack->top == NULL;
}

int set_data(enum data_type type, struct stack_node *node, void *data) {
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
            return STACK_ERROR_MALLOC;
        }
        strncpy(node->string_val, (char *)data, strlen((char *)data) + 1);
        break;
    case POINTER:
        node->pointer_val = data;
        break;
    default:
        return STACK_ERROR_TYPE_MISMATCH;
    }
    return STACK_SUCCESS;
}

int get_data(enum data_type type, struct stack_node *node, void *data) {
    switch (type) {
    case INT:
        *(int *)data = node->int_val;
        break;
    case FLOAT:
        *(float *)data = node->float_val;
        break;
    case DOUBLE:
        *(double *)data = node->double_val;
        break;
    case CHAR:
        *(char *)data = node->char_val;
        break;
    case LONG:
        *(long *)data = node->long_val;
        break;
    case SHORT:
        *(short *)data = node->short_val;
        break;
    case BOOL:
        *(bool *)data = node->bool_val;
        break;
    case STRING:
        if (node->string_val == NULL) {
            return STACK_ERROR_NULL;
        }
        char **string_data = (char **)data;
        *string_data = (char *)malloc(strlen(node->string_val) + 1);
        if (*string_data == NULL) {
            return STACK_ERROR_MALLOC;
        }
        strncpy(*string_data, node->string_val, strlen(node->string_val) + 1);
        break;
    case POINTER:
        *(void **)data = node->pointer_val;
        break;
    default:
        return STACK_ERROR_TYPE_MISMATCH;
    }
    return STACK_SUCCESS;
}

int push(struct stack *stack, void *data) {
    if (stack == NULL) {
        fprintf(stderr, "Error - Stack is NULL in push\n");
        return STACK_ERROR_NULL;
    }

    struct stack_node *new_node =
        (struct stack_node *)malloc(sizeof(struct stack_node));
    if (new_node == NULL) {
        perror("Error - malloc failed in push");
        return STACK_ERROR_MALLOC;
    }

    int set_result = set_data(stack->type, new_node, data);
    if (set_result != STACK_SUCCESS) {
        free(new_node);
        return set_result;
    }

    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
    return STACK_SUCCESS;
}

int pop(struct stack *stack, void *data) {
    if (is_empty(stack)) {
        fprintf(stderr, "Error - Stack is empty in pop\n");
        return STACK_ERROR_EMPTY;
    }

    struct stack_node *node_to_remove = stack->top;
    int get_result = get_data(stack->type, node_to_remove, data);
    if (get_result != STACK_SUCCESS) {
        return get_result;
    }

    stack->top = node_to_remove->next;

    if (stack->type == STRING && node_to_remove->string_val != NULL) {
        free(node_to_remove->string_val);
    }

    free(node_to_remove);
    stack->size--;
    return STACK_SUCCESS;
}

int peek(const struct stack *stack, void *data) {
    if (is_empty(stack)) {
        fprintf(stderr, "Error - Stack is empty in peek\n");
        return STACK_ERROR_EMPTY;
    }
    return get_data(stack->type, stack->top, data);
}

void free_stack(struct stack *stack) {
    if (stack == NULL) {
        return;
    }

    while (!is_empty(stack)) {
        struct stack_node *node_to_remove = stack->top;
        stack->top = node_to_remove->next;

        if (stack->type == STRING && node_to_remove->string_val != NULL) {
            free(node_to_remove->string_val);
        }

        free(node_to_remove);
    }
    free(stack);
}

void print_node(struct stack_node *node, enum data_type type) {
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

void print_stack(struct stack *stack) {
    if (stack == NULL) {
        fprintf(stderr, "Error - stack is NULL in print_stack\n");
        return;
    }

    struct stack_node *current = stack->top;
    while (current != NULL) {
        print_node(current, stack->type);
        current = current->next;
    }
    printf("NULL\n");
}
