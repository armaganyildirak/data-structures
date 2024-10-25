package main

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestInitQueue(t *testing.T) {
	queue := NewQueue[int]()
	assert.NotNil(t, queue)
	assert.Nil(t, queue.head)
	assert.Nil(t, queue.tail)
}

func TestEnqueueNode(t *testing.T) {
	queue := NewQueue[int]()
	data1, data2 := 1, 2

	queue.Enqueue(data1)
	assert.NotNil(t, queue.head)
	assert.Equal(t, data1, queue.head.data)
	assert.Equal(t, data1, queue.tail.data)

	queue.Enqueue(data2)
	assert.NotNil(t, queue.head.next)
	assert.Equal(t, data2, queue.head.next.data)
	assert.Equal(t, data2, queue.tail.data)
}

func TestDequeueNode(t *testing.T) {
	queue := NewQueue[int]()
	data1, data2 := 1, 2

	queue.Enqueue(data1)
	queue.Enqueue(data2)

	dequeuedData, err := queue.Dequeue()
	assert.NoError(t, err)
	assert.Equal(t, data1, dequeuedData)
	assert.Equal(t, data2, queue.head.data)
	assert.Equal(t, data2, queue.tail.data)

	dequeuedData, err = queue.Dequeue()
	assert.NoError(t, err)
	assert.Equal(t, data2, dequeuedData)
	assert.Nil(t, queue.head)
	assert.Nil(t, queue.tail)
}

func TestDequeueEmptyQueue(t *testing.T) {
	queue := NewQueue[int]()
	data, err := queue.Dequeue()
	assert.Error(t, err)
	assert.Equal(t, 0, data)
}
