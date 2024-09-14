#include "stack.h"

// Constructor
template <typename T> 
Stack<T>::Stack() : top(nullptr) {}

// Destructor
template <typename T>
Stack<T>::~Stack() {
    while (!is_empty()) {
        pop();
    }
}

template <typename T>
bool Stack<T>::is_empty() const {
    return top == nullptr;
}

template <typename T>
T Stack<T>::peek() const {
    if (is_empty()) {
        throw std::underflow_error("Error - Stack is empty");
    }

    return top->data;
}

template <typename T>
void Stack<T>::push(const T& data) {
    StackNode *new_node = new StackNode;
    if (new_node == nullptr) {
        throw std::runtime_error("Error - Memory allocation failed");
    }
    new_node->data = data;
    new_node->next = top;
    top = new_node;
}

template <typename T>
T Stack<T>::pop() {
    if (is_empty()) {
        throw std::underflow_error("Error - Stack is empty");
    }
    
    StackNode *temp = top;
    T data = temp->data;
    top = top->next;
    delete temp;

    return data;
}
