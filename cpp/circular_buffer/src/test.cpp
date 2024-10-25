#include <cassert>
#include <cstdint>
#include <iostream>
#include <ostream>
#include "circular_buffer.h"

void test_fill_buffer() {
    CircularBuffer cb;
    for (uint8_t i = 0; i < BUFFER_SIZE - 1; i++) {
        cb.write(i);
    }
    
    assert(cb.isFull() == true);
    std::cout << "Test Fill Buffer: Passed\n";
}

void test_read_all_elements() {
    CircularBuffer cb;
    for (uint8_t i = 0; i < BUFFER_SIZE - 1; i++) {
        cb.write(i);
    }
    for (uint8_t i = 0; i < BUFFER_SIZE - 1; i++) {
        assert(cb.read() == i);
    }
    assert(cb.isEmpty() == true);
    std::cout << "Test Read All Elements: Passed\n";
}

int main() {
    test_fill_buffer();
    test_read_all_elements();

    std::cout << "All tests passed!\n";
    return 0;
}
