#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

enum data_type { 
    INT,
    FLOAT,
    STRING,
    DOUBLE,
    CHAR,
    LONG,
    SHORT,
    BOOL,
    POINTER,
};

struct queue_node {
    union {
        int int_val;
        float float_val;
        char *string_val;
        double double_val;
        char char_val;
        long long_val;
        short short_val;
        bool bool_val;
        void *pointer_val;
    };
    struct queue_node *next;
};

struct queue {
    struct queue_node *head;
    struct queue_node *tail;
    enum data_type type;
    int size;
};

enum queue_error_code {
    QUEUE_SUCCESS = 0,
    QUEUE_ERROR_NULL = -1,
    QUEUE_ERROR_EMPTY = -2,
    QUEUE_ERROR_MALLOC = -3,
    QUEUE_ERROR_TYPE_MISMATCH = -4, 
};

struct queue *init_queue(enum data_type type);
int enqueue_node(struct queue *queue, void *data);
int dequeue_node(struct queue *queue, void *data);
void free_queue(struct queue *queue);
#endif // QUEUE_H