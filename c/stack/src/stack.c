#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct stack *new_stack(enum data_type type) {
    struct stack *stack = (struct stack *)malloc(sizeof(struct stack));
    if (stack == NULL) {
        perror("Error - malloc failed in new_stack");
        return NULL;
    }
    stack->type = type;
    stack->top = NULL;
    return stack;
}

bool is_empty(const struct stack *stack) {
    if (stack == NULL) {
        fprintf(stderr, "Error - stack is NULL in is_empty\n");
        return false;
    }
    return stack->top == NULL;
}

int validate_data(enum data_type type, union data_value data) {
    switch (type) {
    case INT:
        return STACK_SUCCESS;
    case FLOAT:
        return STACK_SUCCESS;
    case STRING:
        if (data.string_val == NULL) {
            fprintf(stderr, "Error - STRING value is NULL\n");
            return STACK_ERROR_TYPE_MISMATCH;
        }
        return STACK_SUCCESS;
    case DOUBLE:
        return STACK_SUCCESS;
    case CHAR:
        return STACK_SUCCESS;
    case LONG:
        return STACK_SUCCESS;
    case SHORT:
        return STACK_SUCCESS;
    case BOOL:
        return STACK_SUCCESS;
    case POINTER:
        if (data.pointer_val == NULL) {
            fprintf(stderr, "Error - POINTER value is NULL\n");
            return STACK_ERROR_TYPE_MISMATCH;
        }
        return STACK_SUCCESS;
    default:
        fprintf(stderr, "Error - Unsupported data type\n");
        return STACK_ERROR_TYPE_MISMATCH;
    }
}

int push(struct stack *stack, union data_value data) {
    if (stack == NULL) {
        fprintf(stderr, "Error - Stack is NULL in push\n");
        return STACK_ERROR_NULL;
    }

    int validation_result = validate_data(stack->type, data);
    if (validation_result != STACK_SUCCESS) {
        return validation_result;
    }

    struct stack_node *new_node =
        (struct stack_node *)malloc(sizeof(struct stack_node));
    if (new_node == NULL) {
        perror("Error - malloc failed in push");
        return STACK_ERROR_MALLOC;
    }

    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
    return STACK_SUCCESS;
}

int pop(struct stack *stack, union data_value *data) {
    if (is_empty(stack)) {
        fprintf(stderr, "Error - Stack is empty in pop\n");
        return STACK_ERROR_EMPTY;
    }

    struct stack_node *node_to_remove = stack->top;
    *data = node_to_remove->data;
    stack->top = node_to_remove->next;
    free(node_to_remove);
    stack->size--;
    return STACK_SUCCESS;
}

int peek(const struct stack *stack, union data_value *data) {
    if (is_empty(stack)) {
        fprintf(stderr, "Error - Stack is empty in peek\n");
        return STACK_ERROR_EMPTY;
    }
    *data = stack->top->data;
    return STACK_SUCCESS;
}

void free_stack(struct stack *stack) {
    while (!is_empty(stack)) {
        struct stack_node *node_to_remove = stack->top;
        stack->top = node_to_remove->next;
        free(node_to_remove);
    }
    free(stack);
}

void print_node(struct stack_node *node, enum data_type type) {
    switch (type) {
    case INT:
        printf("%d -> ", node->data.int_val);
        break;
    case FLOAT:
        printf("%f -> ", node->data.float_val);
        break;
    case STRING:
        printf("%s -> ", node->data.string_val);
        break;
    case DOUBLE:
        printf("%lf -> ", node->data.double_val);
        break;
    case CHAR:
        printf("%c -> ", node->data.char_val);
        break;
    case LONG:
        printf("%ld -> ", node->data.long_val);
        break;
    case SHORT:
        printf("%d -> ", node->data.short_val);
        break;
    case BOOL:
        printf("%s -> ", node->data.bool_val ? "true" : "false");
        break;
    case POINTER:
        printf("%p -> ", node->data.pointer_val);
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
