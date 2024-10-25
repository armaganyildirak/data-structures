package main

import "errors"

type QueueNode[T any] struct {
	data T
	next *QueueNode[T]
}

type Queue[T any] struct {
	head *QueueNode[T]
	tail *QueueNode[T]
}

func NewQueue[T any]() *Queue[T] {
	return &Queue[T]{head: nil, tail: nil}
}

func (q *Queue[T]) Enqueue(data T) {
	newNode := &QueueNode[T]{data: data, next: nil}
	if q.tail == nil {
		q.head = newNode
		q.tail = newNode
	} else {
		q.tail.next = newNode
		q.tail = newNode
	}

}

func (q *Queue[T]) Dequeue() (T, error) {
	var data T
	if q.head == nil {
		return data, errors.New("Queue is empty")
	}
	temp := q.head
	data = temp.data
	q.head = q.head.next
	if q.head == nil {
		q.tail = nil
	}
	return data, nil
}
