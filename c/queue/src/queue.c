#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct queue *init_queue(enum data_type type) {
    struct queue *queue = (struct queue *)malloc(sizeof(struct queue));
    if (queue == NULL) {
        perror("Error - malloc failed");
        exit(EXIT_FAILURE);
    }
    queue->head = NULL;
    queue->tail = NULL;
    queue->type = type;
    queue->size = 0;
    return queue;
}

int set_data(enum data_type type, struct queue_node *node, void *data) {
    switch (type) {
    case INT:
        node->int_val = *(int *)data;
        break;
    case FLOAT:
        node->float_val = *(float *)data;
        break;
    case DOUBLE:
        node->double_val = *(double *)data;
        break;
    case CHAR:
        node->char_val = *(char *)data;
        break;
    case LONG:
        node->long_val = *(long *)data;
        break;
    case SHORT:
        node->short_val = *(short *)data;
        break;
    case BOOL:
        node->bool_val = *(bool *)data;
        break;
    case STRING:
        node->string_val = (char *)malloc(strlen((char *)data) + 1);
        if (!node->string_val) {
            return QUEUE_ERROR_MALLOC;
        }
        strncpy(node->string_val, (char *)data, strlen((char *)data) + 1);
        break;
    case POINTER:
        node->pointer_val = data;
        break;
    default:
        return QUEUE_ERROR_TYPE_MISMATCH;
    }
    return QUEUE_SUCCESS;
}

int enqueue_node(struct queue *queue, void *data) {
    struct queue_node *new_node =
        (struct queue_node *)malloc(sizeof(struct queue_node));
    if (new_node == NULL) {
        perror("Error - malloc failed");
        return QUEUE_ERROR_MALLOC;
    }

    new_node->next = NULL;
    int set_result = set_data(queue->type, new_node, data);
    if (set_result != QUEUE_SUCCESS) {
        free(new_node);
        return set_result;
    }

    if (queue->tail == NULL) {
        queue->head = new_node;
        queue->tail = new_node;
    } else {
        queue->tail->next = new_node;
        queue->tail = new_node;
    }
    queue->size++;
    return QUEUE_SUCCESS;
}

int get_data(enum data_type type, struct queue_node *node, void *data) {
    switch (type) {
    case INT:
        *(int *)data = node->int_val;
        break;
    case FLOAT:
        *(float *)data = node->float_val;
        break;
    case DOUBLE:
        *(double *)data = node->double_val;
        break;
    case CHAR:
        *(char *)data = node->char_val;
        break;
    case LONG:
        *(long *)data = node->long_val;
        break;
    case SHORT:
        *(short *)data = node->short_val;
        break;
    case BOOL:
        *(bool *)data = node->bool_val;
        break;
    case STRING:
        if (node->string_val == NULL) {
            return QUEUE_ERROR_NULL;
        }
        char **string_data = (char **)data;
        *string_data = (char *)malloc(strlen(node->string_val) + 1);
        if (*string_data == NULL) {
            return QUEUE_ERROR_MALLOC;
        }
        strncpy(*string_data, node->string_val, strlen(node->string_val) + 1);
        break;
    case POINTER:
        *(void **)data = node->pointer_val;
        break;
    default:
        return QUEUE_ERROR_TYPE_MISMATCH;
    }
    return QUEUE_SUCCESS;
}

int dequeue_node(struct queue *queue, void *data) {
    if (queue->head == NULL) {
        fprintf(stderr, "Error - the queue is empty\n");
        return QUEUE_ERROR_EMPTY;
    }

    struct queue_node *temp = queue->head;
    int get_result = get_data(queue->type, temp, data);
    if (get_result != QUEUE_SUCCESS) {
        return get_result;
    }

    if (queue->type == STRING && temp->string_val != NULL) {
        free(temp->string_val);
    }

    queue->head = queue->head->next;
    if (queue->head == NULL) {
        queue->tail = NULL;
    }
    queue->size--;

    free(temp);
    return QUEUE_SUCCESS;
}

void free_queue(struct queue *queue) {
    if (queue == NULL) {
        return;
    }

    while (queue->head != NULL) {
        struct queue_node *node_to_remove = queue->head;
        queue->head = node_to_remove->next;

        if (queue->type == STRING && node_to_remove->string_val != NULL) {
            free(node_to_remove->string_val);
        }

        free(node_to_remove);
    }

    free(queue);
}
