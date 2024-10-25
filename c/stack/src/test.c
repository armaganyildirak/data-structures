#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_int_stack() {
    struct stack *stack = new_stack(INT);
    assert(stack != NULL);

    int data = 10;
    assert(push(stack, &data) == STACK_SUCCESS);

    data = 20;
    assert(push(stack, &data) == STACK_SUCCESS);

    assert(!is_empty(stack));

    int popped_data;
    assert(pop(stack, &popped_data) == STACK_SUCCESS);
    assert(popped_data == 20);

    assert(pop(stack, &popped_data) == STACK_SUCCESS);
    assert(popped_data == 10);

    assert(is_empty(stack));

    assert(pop(stack, &popped_data) == STACK_ERROR_EMPTY);

    free_stack(stack);
    printf("test_int_stack passed!\n");
}

void test_string_stack() {
    struct stack *stack = new_stack(STRING);
    assert(stack != NULL);

    char *hello = (char *)malloc(6);
    strncpy(hello, "Hello", 6);
    int res = push(stack, hello);
    assert(res == STACK_SUCCESS);

    char *world = (char *)malloc(6);
    strncpy(world, "World", 6);
    res = push(stack, world);
    assert(res == STACK_SUCCESS);

    assert(!is_empty(stack));

    char *popped_data;

    assert(pop(stack, &popped_data) == STACK_SUCCESS);
    assert(strcmp(popped_data, "World") == 0);
    free(popped_data);

    assert(pop(stack, &popped_data) == STACK_SUCCESS);
    assert(strcmp(popped_data, "Hello") == 0);
    free(popped_data);

    assert(is_empty(stack));

    assert(pop(stack, &popped_data) == STACK_ERROR_EMPTY);

    free_stack(stack);
    free(hello);
    free(world);
    printf("test_string_stack passed!\n");
}

void test_float_stack() {
    struct stack *stack = new_stack(FLOAT);
    assert(stack != NULL);

    float data = 1.23f;
    assert(push(stack, &data) == STACK_SUCCESS);

    data = 4.56f;
    assert(push(stack, &data) == STACK_SUCCESS);

    assert(stack->size == 2);
    assert(!is_empty(stack));

    float popped_data;
    assert(pop(stack, &popped_data) == STACK_SUCCESS);
    assert(popped_data == 4.56f);

    assert(pop(stack, &popped_data) == STACK_SUCCESS);
    assert(popped_data == 1.23f);

    assert(stack->size == 0);
    assert(is_empty(stack));

    assert(pop(stack, &popped_data) == STACK_ERROR_EMPTY);

    free_stack(stack);
    printf("test_float_stack passed!\n");
}

void test_bool_stack() {
    struct stack *stack = new_stack(BOOL);
    assert(stack != NULL);

    bool data;
    data = true;
    assert(push(stack, &data) == STACK_SUCCESS);

    data = false;
    assert(push(stack, &data) == STACK_SUCCESS);

    assert(!is_empty(stack));

    bool popped_data;
    assert(pop(stack, &popped_data) == STACK_SUCCESS);
    assert(popped_data == false);

    assert(pop(stack, &popped_data) == STACK_SUCCESS);
    assert(popped_data == true);

    assert(is_empty(stack));

    assert(pop(stack, &popped_data) == STACK_ERROR_EMPTY);

    free_stack(stack);
    printf("test_bool_stack passed!\n");
}

void test_pointer_stack() {
    struct stack *stack = new_stack(POINTER);
    assert(stack != NULL);

    int x = 42;
    int y = 84;

    void *data;
    data = &x;
    assert(push(stack, data) == STACK_SUCCESS);

    data = &y;
    assert(push(stack, data) == STACK_SUCCESS);

    assert(!is_empty(stack));

    void *popped_data;
    assert(pop(stack, &popped_data) == STACK_SUCCESS);
    assert(popped_data == &y);

    assert(pop(stack, &popped_data) == STACK_SUCCESS);
    assert(popped_data == &x);

    assert(is_empty(stack));

    assert(pop(stack, &popped_data) == STACK_ERROR_EMPTY);

    free_stack(stack);
    printf("test_pointer_stack passed!\n");
}

int main() {
    test_int_stack();
    test_string_stack();
    test_float_stack();
    test_bool_stack();
    test_pointer_stack();

    printf("All tests passed!\n");
    return 0;
}
