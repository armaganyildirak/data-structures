#include "circular_buffer.h"

void circular_buffer_init(struct circular_buffer *cb) {
    cb->head = 0;
    cb->tail = 0;
}

bool circular_buffer_is_full(struct circular_buffer *cb) {
    return ((cb->head + 1) % BUFFER_SIZE) == cb->tail;
}

bool circular_buffer_is_empty(struct circular_buffer *cb) {
    return cb->head == cb->tail;
}

int circular_buffer_write(struct circular_buffer* cb, uint8_t data) {
    if (circular_buffer_is_full(cb)) {
        return  CIRCULAR_BUFFER_ERROR_FULL;
    
    }

    cb->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % BUFFER_SIZE;

    return CIRCULAR_BUFFER_SUCCESS;
}

int circular_buffer_read(struct circular_buffer* cb, uint8_t* data) {
    if (circular_buffer_is_empty(cb)) {
        return  CIRCULAR_BUFFER_ERROR_EMPTY;
    
    }

    *data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;

    return CIRCULAR_BUFFER_SUCCESS;
}