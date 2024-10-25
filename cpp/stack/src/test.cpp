#include "stack.h"
#include <cassert>
#include <iostream>

void test_stack_push() {
  Stack<int> stack;
  stack.push(10);
  stack.push(20);

  assert(stack.peek() == 20);
}

void test_stack_pop() {
  Stack<int> stack;
  stack.push(10);
  stack.push(20);

  int popped = stack.pop();
  assert(popped == 20);
  assert(stack.peek() == 10);
}

void test_stack_peek() {
  Stack<int> stack;
  stack.push(30);
  assert(stack.peek() == 30);
}

void test_stack_is_empty() {
  Stack<int> stack;

  assert(stack.is_empty());

  stack.push(10);

  assert(stack.peek() == 10);
}

int main() {
  test_stack_push();
  test_stack_pop();
  test_stack_peek();
  test_stack_is_empty();

  std::cout << "All tests passed!" << std::endl;
  return 0;
  return 0;
}