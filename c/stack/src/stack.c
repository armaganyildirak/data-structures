#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct stack_record create_stack_record(void *data) {
    struct stack_record stack_record = {.data = data};
    return stack_record;
}

struct stack *create_stack(struct stack_record stack_record) {
    struct stack *stack = (struct stack *)malloc(sizeof(struct stack));
    if (stack == NULL) {
        printf("Error - malloc failed\n");
        exit(1);
    }
    stack->stack_record = stack_record;
    stack->next = NULL;
    return stack;
}

bool is_empty(struct stack* stack) {
    if(stack == NULL) {
        return false;
    }

    return true;
}

void push(struct stack **stack, struct stack_record stack_record) {
    if (stack == NULL || stack_record.data == NULL) {
        printf("Error - Stack or Record is NULL!\n");
        exit(1);
    }

    struct stack *new = create_stack(stack_record);
    new->next = *stack;
    *stack = new;
}

struct stack_record pop(struct stack **stack) {
    if(!is_empty(*stack)) {
        printf("Error - Stack is empty!\n");
        exit(1);
    }

    struct stack *temp = *stack;
    struct stack_record popped_record = temp->stack_record;
    *stack = (*stack)->next;

    free(temp);

    return popped_record;
}

struct stack_record peek(struct stack *stack) {
    if(!is_empty(stack)) {
        printf("Error - Stack is empty!\n");
        exit(1);
    }

    struct stack_record peeked_record = stack->stack_record;

    return peeked_record;
}