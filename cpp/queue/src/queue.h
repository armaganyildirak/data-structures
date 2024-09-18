#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
class Queue {
public:
    struct QueueNode {
        T data;
        QueueNode *next;
    };

    QueueNode* head;
    QueueNode* tail;

public:
    Queue();
    ~Queue();

    void enqueue(const T &data);

    T dequeue();

};

#include "queue.tpp"

#endif // QUEUE_H