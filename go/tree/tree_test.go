package main

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestInsertIntoEmptyTree(t *testing.T) {
	tree := NewTree[int]()
	value := 10
	tree.InsertNode(value)

	assert.NotNil(t, tree.root)
	assert.Equal(t, 10, tree.root.data)
}

func TestInsertMultipleNodes(t *testing.T) {
	tree := NewTree[int]()
	values := []int{10, 5, 15, 3, 7, 12, 18}

	for _, value := range values {
		tree.InsertNode(value)
	}

	assert.Equal(t, 10, tree.root.data)
	assert.Equal(t, 5, tree.root.left.data)
	assert.Equal(t, 15, tree.root.right.data)
	assert.Equal(t, 3, tree.root.left.left.data)
	assert.Equal(t, 7, tree.root.left.right.data)
	assert.Equal(t, 12, tree.root.right.left.data)
	assert.Equal(t, 18, tree.root.right.right.data)
}

func TestPreventDuplicateInsert(t *testing.T) {
	tree := NewTree[int]()
	value1 := 10
	value2 := 10

	tree.InsertNode(value1)
	tree.InsertNode(value2)

	assert.Equal(t, 10, tree.root.data)
	assert.Nil(t, tree.root.left)
	assert.Nil(t, tree.root.right)
}

func TestDeleteLeafNode(t *testing.T) {
	tree := NewTree[int]()
	val1, val2, val3 := 10, 5, 15
	tree.InsertNode(val1)
	tree.InsertNode(val2)
	tree.InsertNode(val3)

	tree.DeleteNode(val3)

	assert.NotNil(t, tree.root)
	assert.Equal(t, 10, tree.root.data)
	assert.Nil(t, tree.root.right)
}

func TestDeleteNodeWithOneChild(t *testing.T) {
	tree := NewTree[int]()
	val1, val2, val3, val4 := 10, 5, 15, 12
	tree.InsertNode(val1)
	tree.InsertNode(val2)
	tree.InsertNode(val3)
	tree.InsertNode(val4)

	tree.DeleteNode(val3)

	assert.NotNil(t, tree.root)
	assert.Equal(t, 10, tree.root.data)
	assert.NotNil(t, tree.root.right)
	assert.Equal(t, 12, tree.root.right.data)
}

func TestDeleteNodeWithTwoChildren(t *testing.T) {
	tree := NewTree[int]()
	val1, val2, val3, val4, val5 := 10, 5, 15, 12, 20
	tree.InsertNode(val1)
	tree.InsertNode(val2)
	tree.InsertNode(val3)
	tree.InsertNode(val4)
	tree.InsertNode(val5)

	tree.DeleteNode(val3)

	assert.NotNil(t, tree.root)
	assert.Equal(t, 10, tree.root.data)
	assert.NotNil(t, tree.root.right)
	assert.Equal(t, 20, tree.root.right.data)
}

func TestDeleteRootNode(t *testing.T) {
	tree := NewTree[int]()
	val1, val2, val3 := 10, 5, 15
	tree.InsertNode(val1)
	tree.InsertNode(val2)
	tree.InsertNode(val3)

	tree.DeleteNode(val1)

	assert.NotNil(t, tree.root)
	assert.Equal(t, 15, tree.root.data)
	assert.NotNil(t, tree.root.left)
	assert.Equal(t, 5, tree.root.left.data)
}

func TestDeleteEmptyTree(t *testing.T) {
	tree := NewTree[int]()
	val := 10

	tree.DeleteNode(val)

	assert.Nil(t, tree.root)
}

func TestDeleteNonexistentNode(t *testing.T) {
	tree := NewTree[int]()
	val1, val2, val3, val4 := 10, 5, 15, 20
	tree.InsertNode(val1)
	tree.InsertNode(val2)
	tree.InsertNode(val3)

	tree.DeleteNode(val4)

	assert.NotNil(t, tree.root)
	assert.Equal(t, 10, tree.root.data)
	assert.Equal(t, 15, tree.root.right.data)
}
