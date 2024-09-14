#include <iostream>
#include "stack.h"


void test_stack_push() {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);

    if (stack.peek() == 20) {
        std::cout << "test_stack_push: Passed\n";
    } else {
        std::cout << "test_stack_push: Failed\n";
    }
}

void test_stack_pop() {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);

    int popped = stack.pop();
    if (popped == 20 && stack.peek() == 10) {
        std::cout << "test_stack_pop: Passed\n";
    } else {
        std::cout << "test_stack_pop: Failed\n";
    }
}

void test_stack_peek() {
    Stack<int> stack;
    stack.push(30);

    if (stack.peek() == 30) {
        std::cout << "test_stack_peek: Passed\n";
    } else {
        std::cout << "test_stack_peek: Failed\n";
    }
}

void test_stack_is_empty() {
    Stack<int> stack;

    if (stack.is_empty()) {
        std::cout << "test_stack_is_empty: Passed\n";
    } else {
        std::cout << "test_stack_is_empty: Failed\n";
    }

    stack.push(10);

    if (!stack.is_empty()) {
        std::cout << "test_stack_is_empty (non-empty): Passed\n";
    } else {
        std::cout << "test_stack_is_empty (non-empty): Failed\n";
    }
}

int main() {
    test_stack_push();
    test_stack_pop();
    test_stack_peek();
    test_stack_is_empty();

    return 0;
}