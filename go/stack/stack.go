package main

import "errors"

type StackNode[T any] struct {
	data T
	next *StackNode[T]
}

type Stack[T any] struct {
	top *StackNode[T]
}

func NewStack[T any]() *Stack[T] {
	return &Stack[T]{top: nil}
}

func (s *Stack[T]) IsEmpty() bool {
	return s.top == nil
}

func (s *Stack[T]) Push(data T) {
	newNode := &StackNode[T]{data: data, next: s.top}
	s.top = newNode
}

func (s *Stack[T]) Pop() (T, error) {
	var popped_value T
	if s.IsEmpty() {
		return popped_value, errors.New("Stack is empty")
	}
	temp := s
	popped_value = temp.top.data
	temp.top = s.top.next
	s = temp
	return popped_value, nil
}

func (s *Stack[T]) Peek() (T, error) {
	var peeked_value T
	if s.IsEmpty() {
		return peeked_value, errors.New("Stack is empty")
	}
	peeked_value = s.top.data
	return peeked_value, nil
}
