#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 256

struct circular_buffer {
    uint8_t buffer[BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
};

enum circular_buffer_error_code {
    CIRCULAR_BUFFER_SUCCESS = 0,
    CIRCULAR_BUFFER_ERROR_EMPTY = -1,
    CIRCULAR_BUFFER_ERROR_FULL = -2,

};

void circular_buffer_init(struct circular_buffer *cb);
int circular_buffer_write(struct circular_buffer* cb, uint8_t data);
int circular_buffer_read(struct circular_buffer *cb, uint8_t* data);
bool circular_buffer_is_full(struct circular_buffer *cb);
bool circular_buffer_is_empty(struct circular_buffer *cb);

#endif // CIRCULAR_BUFFER_H
