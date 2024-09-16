#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct queue *init_queue() {
    struct queue *queue = (struct queue *)malloc(sizeof(struct queue));
    if (queue == NULL) {
        perror("Error - malloc failed");
        exit(EXIT_FAILURE);
    }
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

struct queue_node *create_node(void *data) {
    struct queue_node *new_node = (struct queue_node *)malloc(sizeof(struct queue_node));
    if (new_node == NULL) {
        perror("Error - malloc failed");
        exit(EXIT_FAILURE);
    }
    new_node->next = NULL;
    new_node->data = data;
    return new_node;
}

void enqueue_node(struct queue *queue, void *data) {
    struct queue_node *new_node = create_node(data);
    if (queue->tail == NULL) {
        queue->head = new_node;
        queue->tail = new_node;
    } else {
        queue->tail->next = new_node;
        queue->tail = new_node;
    }
}

void *dequeue_node(struct queue *queue) {
    if (queue->head == NULL) {
        fprintf(stderr, "Error - the queue is empty\n");
        return NULL;
    }
    struct queue_node *temp = queue->head;
    void *data = temp->data;
    queue->head = queue->head->next;
    if (queue->head == NULL) {
        queue->tail = NULL;
    }
    free(temp);
    return data;
}

void free_queue(struct queue *queue) {
    while (queue->head != NULL) {
        dequeue_node(queue);
    }
    free(queue);
}