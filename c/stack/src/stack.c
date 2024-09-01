#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct stack *new_stack() {
    struct stack *stack = (struct stack *)malloc(sizeof(struct stack));
    if (stack == NULL) {
        printf("Error - malloc failed\n");
        exit(1);
    }
    stack->top = NULL;
    return stack;
}

bool is_empty(struct stack* stack) {
    if(stack->top == NULL) {
        return false;
    }

    return true;
}

void push(struct stack **stack, void *data) {
    if (stack == NULL) {
        printf("Error - Stack is NULL!\n");
        exit(1);
    }

    struct stack_node *new_node = (struct stack_node *)malloc(sizeof(struct stack_node));
    if (new_node == NULL) {
        printf("Error - malloc failed\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = (*stack)->top;
    (*stack)->top = new_node;
}

void *pop(struct stack **stack) {
    if(!is_empty(*stack)) {
        printf("Error - Stack is empty!\n");
        exit(1);
    }

    struct stack_node *new_node = (*stack)->top;
    (*stack)->top = (*stack)->top->next;

    return new_node->data;
}

void *peek(struct stack *stack) {
    if(!is_empty(stack)) {
        printf("Error - Stack is empty!\n");
        exit(1);
    }

    return stack->top->data;
}