#include "stack.h"
#include <stdio.h>

void test_stack_push_pop() {

    struct stack *stack = new_stack();
    
    push(&stack, (int *)10);
    push(&stack, (int *)20);
    push(&stack, (int *)30);
    push(&stack, (int *)40);
    push(&stack, (int *)50);
    push(&stack, (int *)60);

    void *peeked_value = peek(stack); 
    printf("peeked: %d\n", *(int *)&peeked_value);
    
    void *popped_value = pop(&stack);
    printf("popped: %d\n", *(int *)&popped_value);
    popped_value = pop(&stack);
    printf("popped: %d\n", *(int *)&popped_value);
    popped_value = pop(&stack);
    printf("popped: %d\n", *(int *)&popped_value);
    popped_value = pop(&stack);
    printf("popped: %d\n", *(int *)&popped_value);
    popped_value = pop(&stack);
    printf("popped: %d\n", *(int *)&popped_value);
    popped_value = pop(&stack);
    printf("popped: %d\n", *(int *)&popped_value);
    popped_value = pop(&stack);
    printf("popped: %d\n", *(int *)&popped_value);


}

int main() {
    test_stack_push_pop();

    return 0;
}