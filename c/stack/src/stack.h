#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

enum data_type { 
    INT,
    FLOAT,
    STRING,
    DOUBLE,
    CHAR,
    LONG,
    SHORT,
    BOOL,
    POINTER,
};

struct stack_node {
    union {
        int int_val;
        float float_val;
        char *string_val;
        double double_val;
        char char_val;
        long long_val;
        short short_val;
        bool bool_val;
        void *pointer_val;
    };
    struct stack_node *next;
};

struct stack {
    enum data_type type;
    struct stack_node *top;
    int size;
};

enum stack_error_code {
    STACK_SUCCESS = 0,
    STACK_ERROR_NULL = -1,
    STACK_ERROR_EMPTY = -2,
    STACK_ERROR_MALLOC = -3,
    STACK_ERROR_TYPE_MISMATCH = -4
};

struct stack *new_stack(enum data_type type);
int push(struct stack *stack, void *data);
int pop(struct stack *stack, void *data);
bool is_empty(const struct stack *stack);
int peek(const struct stack *stack, void *data);
void free_stack(struct stack *stack);
void print_stack(struct stack *stack);

#endif // STACK_H
