#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <cstdint>
#include <stdexcept>

const std::size_t BUFFER_SIZE = 256;

class CircularBuffer {
public:
    uint8_t buffer[BUFFER_SIZE];
    std::size_t head;
    std::size_t tail;

public:
    CircularBuffer() : head(0), tail(0) {
        std::fill(std::begin(buffer), std::end(buffer), 0);
    }

    bool isFull() const {
        return (head + 1) % BUFFER_SIZE == tail;
    }

    bool isEmpty() const {
        return head == tail;
    }


    void write(uint8_t data) {
        if (isFull()) {
            throw std::runtime_error("Error - CircularBuffer is full");
        }

        buffer[head] = data;
        head = (head + 1) % BUFFER_SIZE;
    }

    uint8_t read() {
        if (isEmpty()) {
            throw std::runtime_error("Error - CircularBuffer is empty");
        }

        uint8_t data = buffer[tail];
        tail = (tail + 1) % BUFFER_SIZE;

        return data;
    }
};

#endif // CIRCULAR_BUFFER_H
