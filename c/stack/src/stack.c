#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct stack *new_stack() {
    struct stack *stack = (struct stack *)malloc(sizeof(struct stack));
    if (stack == NULL) {
        perror("Error - malloc failed");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;
    return stack;
}

bool is_empty(const struct stack *stack) { return stack->top == NULL; }

void push(struct stack *stack, void *data) {
    if (stack == NULL) {
        fprintf(stderr, "Error - Stack is NULL!\n");
        exit(EXIT_FAILURE);
    }

    struct stack_node *new_node =
        (struct stack_node *)malloc(sizeof(struct stack_node));
    if (new_node == NULL) {
        perror("Error - malloc failed");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;
}

void *pop(struct stack *stack) {
    if (is_empty(stack)) {
        fprintf(stderr, "Error - Stack is empty!\n");
        exit(EXIT_FAILURE);
    }

    struct stack_node *node_to_remove = stack->top;
    void *data = node_to_remove->data;
    stack->top = node_to_remove->next;
    free(node_to_remove);

    return data;
}

void *peek(const struct stack *stack) {
    if (is_empty(stack)) {
        fprintf(stderr, "Error - Stack is empty!\n");
        exit(EXIT_FAILURE);
    }

    return stack->top->data;
}

void free_stack(struct stack *stack) {
    while (!is_empty(stack)) {
        pop(stack);
    }
    free(stack);
}