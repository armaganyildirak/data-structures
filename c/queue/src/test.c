#include "queue.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_int_queue() {
    struct queue *q = init_queue(INT);
    int data1 = 10, data2 = 20, result;

    assert(enqueue_node(q, &data1) == QUEUE_SUCCESS);
    assert(enqueue_node(q, &data2) == QUEUE_SUCCESS);

    assert(dequeue_node(q, &result) == QUEUE_SUCCESS);
    assert(result == 10);

    assert(dequeue_node(q, &result) == QUEUE_SUCCESS);
    assert(result == 20);

    assert(dequeue_node(q, &result) == QUEUE_ERROR_EMPTY);

    free_queue(q);
    printf("Integer queue test passed!\n");
}

void test_string_queue() {
    struct queue *q = init_queue(STRING);
    char *data1 = "Hello", *data2 = "World", *result;

    assert(enqueue_node(q, data1) == QUEUE_SUCCESS);
    assert(enqueue_node(q, data2) == QUEUE_SUCCESS);

    assert(dequeue_node(q, &result) == QUEUE_SUCCESS);
    assert(strcmp(result, "Hello") == 0);
    free(result);

    assert(dequeue_node(q, &result) == QUEUE_SUCCESS);
    assert(strcmp(result, "World") == 0);
    free(result);

    assert(dequeue_node(q, &result) == QUEUE_ERROR_EMPTY);

    free_queue(q);
    printf("String queue test passed!\n");
}

void test_float_queue() {
    struct queue *q = init_queue(FLOAT);
    float data1 = 1.5, data2 = 2.5, result;

    assert(enqueue_node(q, &data1) == QUEUE_SUCCESS);
    assert(enqueue_node(q, &data2) == QUEUE_SUCCESS);

    assert(dequeue_node(q, &result) == QUEUE_SUCCESS);
    assert(result == 1.5f);

    assert(dequeue_node(q, &result) == QUEUE_SUCCESS);
    assert(result == 2.5f);

    assert(dequeue_node(q, &result) == QUEUE_ERROR_EMPTY);

    free_queue(q);
    printf("Float queue test passed!\n");
}

void test_pointer_queue() {
    struct queue *q = init_queue(POINTER);
    int value1 = 10, value2 = 20;
    int *result;

    assert(enqueue_node(q, &value1) == QUEUE_SUCCESS);
    assert(enqueue_node(q, &value2) == QUEUE_SUCCESS);

    assert(dequeue_node(q, &result) == QUEUE_SUCCESS);
    assert(*result == 10);

    assert(dequeue_node(q, &result) == QUEUE_SUCCESS);
    assert(*result == 20);

    assert(dequeue_node(q, &result) == QUEUE_ERROR_EMPTY);

    free_queue(q);
    printf("Pointer queue test passed!\n");
}

int main() {
    test_int_queue();
    test_string_queue();
    test_float_queue();
    test_pointer_queue();
    printf("All tests passed!\n");
    return 0;
}
