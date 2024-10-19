package main

import (
	"errors"
)

const BUFFER_SIZE = 256

type CircularBuffer struct {
	buffer [BUFFER_SIZE]byte
	head   int
	tail   int
}

var (
	ErrBufferEmpty = errors.New("buffer is empty")
	ErrBufferFull  = errors.New("buffer is full")
)

func NewCircularBuffer() *CircularBuffer {
	return &CircularBuffer{
		head: 0,
		tail: 0,
	}
}

func (cb *CircularBuffer) IsFull() bool {
	return ((cb.head + 1) % BUFFER_SIZE) == cb.tail
}

func (cb *CircularBuffer) IsEmpty() bool {
	return cb.head == cb.tail
}

func (cb *CircularBuffer) Write(data byte) error {
	if cb.IsFull() {
		return ErrBufferFull
	}

	cb.buffer[cb.head] = data
	cb.head = (cb.head + 1) % BUFFER_SIZE

	return nil
}

func (cb *CircularBuffer) Read() (byte, error) {
	if cb.IsEmpty() {
		return 0, ErrBufferEmpty
	}

	data := cb.buffer[cb.tail]
	cb.tail = (cb.tail + 1) % BUFFER_SIZE

	return data, nil
}
