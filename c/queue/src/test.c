#include "queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_init_queue() {
    struct queue *queue = init_queue();
    assert(queue != NULL);
    assert(queue->head == NULL);
    assert(queue->tail == NULL);
    free_queue(queue);
    printf("test_init_queue passed\n");
}

void test_enqueue_node() {
    struct queue *queue = init_queue();
    int data1 = 1, data2 = 2;

    enqueue_node(queue, &data1);
    assert(queue->head != NULL);
    assert(queue->head->data == &data1);
    assert(queue->tail->data == &data1);

    enqueue_node(queue, &data2);
    assert(queue->head->next != NULL);
    assert(queue->head->next->data == &data2);
    assert(queue->tail->data == &data2);

    free_queue(queue);
    printf("test_enqueue_node passed\n");
}

void test_dequeue_node() {
    struct queue *queue = init_queue();
    int data1 = 1, data2 = 2;

    enqueue_node(queue, &data1);
    enqueue_node(queue, &data2);

    int *dequeued_data = (int *)dequeue_node(queue);
    assert(dequeued_data == &data1);
    assert(queue->head->data == &data2);
    assert(queue->tail->data == &data2);

    dequeued_data = (int *)dequeue_node(queue);
    assert(dequeued_data == &data2);
    assert(queue->head == NULL);
    assert(queue->tail == NULL);

    free_queue(queue);
    printf("test_dequeue_node passed\n");
}

void test_dequeue_empty_queue() {
    struct queue *queue = init_queue();
    void *data = dequeue_node(queue);
    assert(data == NULL);
    free_queue(queue);
    printf("test_dequeue_empty_queue passed\n");
}

void test_free_queue() {
    struct queue *queue = init_queue();
    int data1 = 1, data2 = 2;

    enqueue_node(queue, &data1);
    enqueue_node(queue, &data2);

    free_queue(queue);
    printf("test_free_queue passed\n");
}

int main() {
    test_init_queue();
    test_enqueue_node();
    test_dequeue_node();
    test_dequeue_empty_queue();
    test_free_queue();

    printf("All tests passed!\n");
    return 0;
}