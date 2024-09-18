#include "queue.h"
#include <stdexcept>

template <typename T> 
Queue<T>::Queue() : head(nullptr), tail(nullptr) {}

template <typename T>
Queue<T>::~Queue() {
    while (head != nullptr) {
        dequeue();
    }
}

template <typename T>
void Queue<T>::enqueue(const T &data) {
    QueueNode *new_node = new QueueNode;
    if (new_node == nullptr) {
        throw std::runtime_error("Error - Memory allocation failed");
    }
    new_node->data = data;
    new_node->next = nullptr;
    if (tail == nullptr) {
        head = new_node;
        tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
}

template <typename T>
T Queue<T>::dequeue() {
    if (head == nullptr) {
        throw std::underflow_error("Error - Queue is empty");
    }

    QueueNode *temp = head;
    T data = temp->data;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    }
    delete temp;
    return data;
}