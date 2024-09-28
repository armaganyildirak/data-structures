package main

import (
	"errors"

	"golang.org/x/exp/constraints"
)

var (
	ErrExistingNode = errors.New("cannot insert existing node")
	ErrTreeEmpty    = errors.New("tree is empty")
	ErrDataNotFound = errors.New("data not found")
)

type TreeNode[T constraints.Ordered] struct {
	data  T
	left  *TreeNode[T]
	right *TreeNode[T]
}

type Tree[T constraints.Ordered] struct {
	root *TreeNode[T]
}

func NewTree[T constraints.Ordered]() *Tree[T] {
	return &Tree[T]{root: nil}
}

func (t *Tree[T]) InsertNode(data T) error {
	newNode := &TreeNode[T]{data: data, left: nil, right: nil}
	if t.root == nil {
		t.root = newNode
	} else {
		temp := t.root
		var parent *TreeNode[T]

		for temp != nil {
			parent = temp
			if data > temp.data {
				temp = temp.right
			} else if data < temp.data {
				temp = temp.left
			} else {
				return ErrExistingNode
			}
		}

		if data > parent.data {
			parent.right = newNode
		} else {
			parent.left = newNode
		}
	}
	return nil
}

func (t *Tree[T]) DeleteNode(data T) error {
	if t.root == nil {
		return ErrTreeEmpty
	}

	var parent *TreeNode[T]
	current := t.root

	for current != nil && data != current.data {
		parent = current
		if data < current.data {
			current = current.left
		} else {
			current = current.right
		}
	}

	if current == nil {
		return ErrDataNotFound
	}

	if current.left == nil && current.right == nil {
		if current == t.root {
			t.root = nil
		} else if parent != nil {
			if parent.left == current {
				parent.left = nil
			} else {
				parent.right = nil
			}
		}
	} else if current.left == nil || current.right == nil {
		var child *TreeNode[T]
		if current.left != nil {
			child = current.left
		} else {
			child = current.right
		}

		if current == t.root {
			t.root = child
		} else if parent != nil {
			if parent.left == current {
				parent.left = child
			} else {
				parent.right = child
			}
		}
	} else {
		tempParent := current
		temp := current.right

		for temp.left != nil {
			tempParent = temp
			temp = temp.left
		}

		current.data = temp.data

		if tempParent.left == temp {
			tempParent.left = temp.right
		} else {
			tempParent.right = temp.right
		}
	}

	return nil
}
