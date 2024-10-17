#include <assert.h>
#include <stdio.h>
#include "circular_buffer.h"

void test_circular_buffer_init() {
    struct circular_buffer cb;
    circular_buffer_init(&cb);
    
    assert(circular_buffer_is_empty(&cb));
    assert(!circular_buffer_is_full(&cb));
}

void test_circular_buffer_write_and_read() {
    struct circular_buffer cb;
    circular_buffer_init(&cb);
    
    uint8_t data;
    
    assert(circular_buffer_write(&cb, 42) == CIRCULAR_BUFFER_SUCCESS);
    assert(!circular_buffer_is_empty(&cb));
    
    assert(circular_buffer_read(&cb, &data) == CIRCULAR_BUFFER_SUCCESS);
    assert(data == 42);
    assert(circular_buffer_is_empty(&cb));
}

void test_circular_buffer_full() {
    struct circular_buffer cb;
    circular_buffer_init(&cb);
    
    for (int i = 0; i < BUFFER_SIZE - 1; i++) {
        assert(circular_buffer_write(&cb, i) == CIRCULAR_BUFFER_SUCCESS);
    }
    
    assert(circular_buffer_is_full(&cb));
    assert(circular_buffer_write(&cb, 42) == CIRCULAR_BUFFER_ERROR_FULL);
}

void test_circular_buffer_empty() {
    struct circular_buffer cb;
    circular_buffer_init(&cb);
    
    uint8_t data;
    
    assert(circular_buffer_read(&cb, &data) == CIRCULAR_BUFFER_ERROR_EMPTY);
}

void test_circular_buffer_wraparound() {
    struct circular_buffer cb;
    circular_buffer_init(&cb);
    
    uint8_t data;

    for (int i = 0; i < BUFFER_SIZE - 1; i++) {
        assert(circular_buffer_write(&cb, i) == CIRCULAR_BUFFER_SUCCESS);
    }

    for (int i = 0; i < (BUFFER_SIZE - 1) / 2; i++) {
        assert(circular_buffer_read(&cb, &data) == CIRCULAR_BUFFER_SUCCESS);
        assert(data == i);
    }
    
    for (int i = 100; i < 100 + (BUFFER_SIZE - 1) / 2; i++) {
        assert(circular_buffer_write(&cb, i) == CIRCULAR_BUFFER_SUCCESS);
    }

    for (int i = (BUFFER_SIZE - 1) / 2; i < BUFFER_SIZE - 1; i++) {
        assert(circular_buffer_read(&cb, &data) == CIRCULAR_BUFFER_SUCCESS);
        assert(data == i);
    }
    for (int i = 100; i < 100 + (BUFFER_SIZE - 1) / 2; i++) {
        assert(circular_buffer_read(&cb, &data) == CIRCULAR_BUFFER_SUCCESS);
        assert(data == i);
    }
}


int main() {
    test_circular_buffer_init();
    test_circular_buffer_write_and_read();
    test_circular_buffer_full();
    test_circular_buffer_empty();
    test_circular_buffer_wraparound();

    printf("All tests passed!\n");
    
    return 0;
}
