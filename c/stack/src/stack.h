#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

struct stack_node {
    void *data;
    struct stack_node *next;
};

struct stack {
    struct stack_node *top;
};

struct stack *new_stack();
void push(struct stack *stack, void *data);
void *pop(struct stack *stack);
bool is_empty(const struct stack *stack);
void *peek(const struct stack *stack);

#endif // STACK_H