#include "stack.h"
#include <stdio.h>

void test_stack_push_pop() {
    struct stack_record record_1 = create_stack_record("record 1");
    struct stack_record record_2 = create_stack_record("record 2");
    struct stack_record record_3 = create_stack_record("record 3");
    struct stack_record record_4 = create_stack_record("record 4");
    struct stack_record record_5 = create_stack_record("record 5");
    struct stack *stack = create_stack(record_1);

    stack = push(stack, record_2);
    stack = push(stack, record_3);
    stack = push(stack, record_4);
    stack = push(stack, record_5);
    
    struct stack_record popped_record = pop(&stack);
    printf("popped: %s\n", (char *)popped_record.data);
    popped_record = pop(&stack);
    printf("popped: %s\n", (char *)popped_record.data);
    popped_record = pop(&stack);
    printf("popped: %s\n", (char *)popped_record.data);
    popped_record = pop(&stack);
    printf("popped: %s\n", (char *)popped_record.data);
    popped_record = pop(&stack);
    printf("popped: %s\n", (char *)popped_record.data);
    popped_record = pop(&stack);
    printf("popped: %s\n", (char *)popped_record.data);

}

int main() {
    test_stack_push_pop();

    return 0;
}