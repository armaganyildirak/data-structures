#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

void test_new_stack() {
    struct stack *stack = new_stack();
    assert(stack != NULL);
    assert(stack->top == NULL);
    printf("test_new_stack passed\n");
    free_stack(stack);
}

void test_push_pop() {
    struct stack *stack = new_stack();
    int data1 = 10, data2 = 20;

    push(stack, &data1);
    push(stack, &data2);

    assert(peek(stack) == &data2);
    
    int *popped_data = (int *)pop(stack);
    assert(*popped_data == 20);

    popped_data = (int *)pop(stack);
    assert(*popped_data == 10);

    assert(is_empty(stack));
    
    printf("test_push_pop passed\n");
    free_stack(stack);
}

void test_peek() {
    struct stack *stack = new_stack();
    int data = 30;

    push(stack, &data);
    assert(*(int *)peek(stack) == 30);
    
    printf("test_peek passed\n");

    free_stack(stack);
}

void test_is_empty() {
    struct stack *stack = new_stack();

    assert(is_empty(stack));
    
    int data = 40;
    push(stack, &data);
    assert(!is_empty(stack));

    pop(stack);
    assert(is_empty(stack));
    
    printf("test_is_empty passed\n");
    free_stack(stack);
}

int main() {
    test_new_stack();
    test_push_pop();
    test_peek();
    test_is_empty();
    return 0;
}