#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_int_stack() {
    struct stack *stack = new_stack(INT);
    assert(stack != NULL);

    union data_value data;
    data.int_val = 10;
    assert(push(stack, data) == STACK_SUCCESS);

    data.int_val = 20;
    assert(push(stack, data) == STACK_SUCCESS);

    assert(!is_empty(stack));

    union data_value popped_data;
    assert(pop(stack, &popped_data) == STACK_SUCCESS);
    assert(popped_data.int_val == 20);

    assert(pop(stack, &popped_data) == STACK_SUCCESS);
    assert(popped_data.int_val == 10);

    assert(is_empty(stack));

    assert(pop(stack, &popped_data) == STACK_ERROR_EMPTY);

    free_stack(stack);
    printf("test_int_stack passed!\n");
}

void test_string_stack() {
    struct stack *stack = new_stack(STRING);
    assert(stack != NULL);

    union data_value hello;
    hello.string_val = (char *)malloc(6);
    strncpy(hello.string_val, "Hello", 6);
    assert(push(stack, hello) == STACK_SUCCESS);

    union data_value world;
    world.string_val = (char *)malloc(6);
    strncpy(world.string_val, "World", 6);
    assert(push(stack, world) == STACK_SUCCESS);

    assert(!is_empty(stack));

    union data_value popped_data;
    assert(pop(stack, &popped_data) == STACK_SUCCESS);
    assert(strcmp(popped_data.string_val, "World") == 0);

    assert(pop(stack, &popped_data) == STACK_SUCCESS);
    assert(strcmp(popped_data.string_val, "Hello") == 0);

    assert(is_empty(stack));

    assert(pop(stack, &popped_data) == STACK_ERROR_EMPTY);

    free(hello.string_val);
    free(world.string_val);
    free_stack(stack);
    printf("test_string_stack passed!\n");
}

void test_float_stack() {
    struct stack *stack = new_stack(FLOAT);
    assert(stack != NULL);

    union data_value data;
    data.float_val = 1.23f;
    assert(push(stack, data) == STACK_SUCCESS);

    data.float_val = 4.56f;
    assert(push(stack, data) == STACK_SUCCESS);

    assert(stack->size == 2);
    assert(!is_empty(stack));

    union data_value popped_data;
    assert(pop(stack, &popped_data) == STACK_SUCCESS);
    assert(popped_data.float_val == 4.56f);

    assert(pop(stack, &popped_data) == STACK_SUCCESS);
    assert(popped_data.float_val == 1.23f);

    assert(stack->size == 0);
    assert(is_empty(stack));

    assert(pop(stack, &popped_data) == STACK_ERROR_EMPTY);

    free_stack(stack);
    printf("test_float_stack passed!\n");
}

void test_bool_stack() {
    struct stack *stack = new_stack(BOOL);
    assert(stack != NULL);

    union data_value data;
    data.bool_val = true;
    assert(push(stack, data) == STACK_SUCCESS);

    data.bool_val = false;
    assert(push(stack, data) == STACK_SUCCESS);

    assert(!is_empty(stack));

    union data_value popped_data;
    assert(pop(stack, &popped_data) == STACK_SUCCESS);
    assert(popped_data.bool_val == false);

    assert(pop(stack, &popped_data) == STACK_SUCCESS);
    assert(popped_data.bool_val == true);

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

    union data_value data;
    data.pointer_val = &x;
    assert(push(stack, data) == STACK_SUCCESS);

    data.pointer_val = &y;
    assert(push(stack, data) == STACK_SUCCESS);

    assert(!is_empty(stack));

    union data_value popped_data;
    assert(pop(stack, &popped_data) == STACK_SUCCESS);
    assert(popped_data.pointer_val == &y);

    assert(pop(stack, &popped_data) == STACK_SUCCESS);
    assert(popped_data.pointer_val == &x);

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
