package main

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestInsertNode(t *testing.T) {
	list := NewList[int]()

	list.InsertNode(10)
	list.InsertNode(20)
	list.InsertNode(30)

	assert.Equal(t, list.head.data, 10, "head failed: expected 10")
	assert.Equal(t, list.head.next.data, 20, "second element failed: expected 20")
	assert.Equal(t, list.head.next.next.data, 30, "third element failed: expected 30")
	assert.Equal(t, list.head.next.next.prev.prev.data, 10, "first element failed: expected 10")

}

func TestDeleteNode(t *testing.T) {
	list := NewList[int]()
	list.InsertNode(10)
	list.InsertNode(20)
	list.InsertNode(30)

	list.DeleteNode(30)
	assert.Equal(t, list.head.data, 10, "last element removed: head is 10")

	list.DeleteNode(10)
	assert.Equal(t, list.head.data, 20, "first element removed: head is 20")

	list.DeleteNode(50)
	assert.Equal(t, list.head.data, 20, "tried to remove none existing element: head is 20")

}

func TestInsertMultipleNodes(t *testing.T) {
	list := NewList[int]()

	for i := 0; i < 500; i++ {
		list.InsertNode(i)
	}

	current := list.head
	for i := 0; i < 500; i++ {
		assert.Equal(t, current.data, i, "wrong insert")
		current = current.next
	}
}
