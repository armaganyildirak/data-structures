#include "queue.h"
#include <cassert>
#include <iostream>

void test_init_queue() {
    Queue<int> queue;

    assert(queue.head == nullptr);
    assert(queue.tail == nullptr);
}

void test_enqueue_node() {
    Queue<int> queue;
    int data1 = 1, data2 = 2;

    queue.enqueue(data1);
    assert(queue.head != nullptr);
    assert(queue.head->data == data1);
    assert(queue.tail->data == data1);

    queue.enqueue(data2);
    assert(queue.head != nullptr);
    assert(queue.head->next->data == data2);
    assert(queue.tail->data == data2);
}

void test_dequeue_node() {
    Queue<int> queue;
    int data1 = 1, data2 = 2;

    queue.enqueue(data1);
    queue.enqueue(data2);
    int dequeued_data = queue.dequeue();
    assert(dequeued_data == data1);
    assert(queue.head->data == data2);
    assert(queue.tail->data == data2);

    dequeued_data = queue.dequeue();
    assert(dequeued_data == data2);
    assert(queue.head == nullptr);
    assert(queue.tail == nullptr);
}


int main() {
    test_init_queue();
    test_enqueue_node();
    test_dequeue_node();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}