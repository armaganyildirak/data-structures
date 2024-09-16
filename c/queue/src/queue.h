#ifndef QUEUE_H
#define QUEUE_H

struct queue_node {
    void *data;
    struct queue_node *next;
};

struct queue {
    struct queue_node *head;
    struct queue_node *tail;
};

struct queue *init_queue();
struct queue_node *create_node(void *data);
void enqueue_node(struct queue *queue, void *data);
void *dequeue_node(struct queue *queue);
void free_queue(struct queue *queue);
#endif // QUEUE_H