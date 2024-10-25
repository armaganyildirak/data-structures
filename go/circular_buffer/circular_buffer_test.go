package main

import (
	"testing"
)

func TestCircularBuffer(t *testing.T) {
	cb := NewCircularBuffer()

	if !cb.IsEmpty() {
		t.Error("Buffer should be empty initially")
	}
	if cb.IsFull() {
		t.Error("Buffer should not be full initially")
	}

	if err := cb.Write(42); err != nil {
		t.Errorf("Unexpected error on write: %v", err)
	}
	if cb.IsEmpty() {
		t.Error("Buffer should not be empty after write")
	}

	data, err := cb.Read()
	if err != nil {
		t.Errorf("Unexpected error on read: %v", err)
	}
	if data != 42 {
		t.Errorf("Expected 42, got %v", data)
	}
	if !cb.IsEmpty() {
		t.Error("Buffer should be empty after read")
	}

	for i := 0; i < BUFFER_SIZE-1; i++ {
		if err := cb.Write(byte(i)); err != nil {
			t.Errorf("Unexpected error on write: %v", err)
		}
	}
	if !cb.IsFull() {
		t.Error("Buffer should be full")
	}

	if err := cb.Write(255); err != ErrBufferFull {
		t.Errorf("Expected ErrBufferFull, got %v", err)
	}

	for i := 0; i < BUFFER_SIZE-1; i++ {
		data, err := cb.Read()
		if err != nil {
			t.Errorf("Unexpected error on read: %v", err)
		}
		if data != byte(i) {
			t.Errorf("Expected %v, got %v", i, data)
		}
	}
	if !cb.IsEmpty() {
		t.Error("Buffer should be empty after reading all elements")
	}
}
