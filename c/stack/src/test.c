#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


void test_new_stack() {
    struct stack *stack = new_stack();
    if (stack == NULL) {
        printf("test_new_stack failed\n");
        return;
    }
    if (stack->top != NULL) {
        printf("test_new_stack failed: stack top is not NULL\n");
    } else {
        printf("test_new_stack passed\n");
    }
    free(stack);
}

void test_push_pop() {
    struct stack *stack = new_stack();
    int data1 = 10, data2 = 20;

    push(stack, &data1);
    push(stack, &data2);

    if (peek(stack) != &data2) {
        printf("test_push_pop failed: top element is incorrect\n");
    } else {
        int *popped_data = (int *)pop(stack);
        if (*popped_data != 20) {
            printf("test_push_pop failed: popped data is incorrect\n");
        } else {
            popped_data = (int *)pop(stack);
            if (*popped_data != 10) {
                printf("test_push_pop failed: popped data is incorrect\n");
            } else if (!is_empty(stack)) {
                printf("test_push_pop failed: stack is not empty after popping all elements\n");
            } else {
                printf("test_push_pop passed\n");
            }
        }
    }
    free(stack);
}

void test_peek() {
    struct stack *stack = new_stack();
    int data = 30;

    push(stack, &data);

    if (*(int *)peek(stack) != 30) {
        printf("test_peek failed: top element is incorrect\n");
    } else {
        printf("test_peek passed\n");
    }
    free(stack);
}

void test_is_empty() {
    struct stack *stack = new_stack();

    if (!is_empty(stack)) {
        printf("test_is_empty failed: stack should be empty initially\n");
    } else {
        int data = 40;
        push(stack, &data);
        if (is_empty(stack)) {
            printf("test_is_empty failed: stack should not be empty after push\n");
        } else {
            pop(stack);
            if (!is_empty(stack)) {
                printf("test_is_empty failed: stack should be empty after popping all elements\n");
            } else {
                printf("test_is_empty passed\n");
            }
        }
    }
    free(stack);
}

int main() {
    test_new_stack();
    test_push_pop();
    test_peek();
    test_is_empty();
    return 0;
}