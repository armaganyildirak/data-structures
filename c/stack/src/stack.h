#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

struct stack_record {
    void *data;
};

struct stack {
    struct stack_record stack_record;
    struct stack *next;
};

struct stack_record create_stack_record(void *data);
struct stack *create_stack(struct stack_record stack_record);
struct stack *push(struct stack *stack, struct stack_record stack_record);
struct stack_record pop(struct stack **stack);
bool is_empty(struct stack *stack);

#endif // STACK_H