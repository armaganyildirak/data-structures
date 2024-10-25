package main

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestStackOperations(t *testing.T) {
	stack := NewStack[int]()

	stack.Push(10)
	stack.Push(20)
	stack.Push(30)

	peeked_value, err := stack.Peek()
	assert.NoError(t, err)
	assert.Equal(t, peeked_value, 30, "Peek failed: expected 30")

	popped_value, err := stack.Pop()
	assert.NoError(t, err)
	assert.Equal(t, popped_value, 30, "Pop failed: expected 30")

	peeked_value, err = stack.Peek()
	assert.NoError(t, err)
	assert.Equal(t, peeked_value, 20, "Peek failed: expected 20")

	popped_value, err = stack.Pop()
	assert.NoError(t, err)
	assert.Equal(t, popped_value, 20, "Pop failed: expected 30")

	popped_value, err = stack.Pop()
	assert.NoError(t, err)
	assert.Equal(t, popped_value, 10, "Pop failed: expected 30")

	assert.True(t, stack.IsEmpty(), "Stack should be empty but is not")

	_, err = stack.Pop()
	assert.Error(t, err, "Expected stack underflow error")
	assert.EqualError(t, err, "Stack is empty", "Unexpected error message")

}
