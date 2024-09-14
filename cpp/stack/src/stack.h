#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack {
private:
    struct StackNode {
        T data;
        StackNode *next;
    };

    StackNode *top;

public:
    // Constructor
    Stack();

    // Destructor
    ~Stack();

    void push(const T &data);

    T pop();

    bool is_empty() const;

    T peek() const;
};

#include "stack.tpp"

#endif // STACK_H