package main

import "fmt"

type ListNode[T any] struct {
	data T
	next *ListNode[T]
	prev *ListNode[T]
}

type List[T any] struct {
	head *ListNode[T]
}

func NewList[T any]() *List[T] {
	return &List[T]{head: nil}
}

func (l *List[T]) IsEmpty() bool {
	return l.head == nil
}

func Equal(a, b interface{}) bool {
	return fmt.Sprint(a) == fmt.Sprint(b)
}

func (l *List[T]) InsertNode(data T) {
	newNode := &ListNode[T]{data: data, next: nil, prev: nil}
	if l.IsEmpty() {
		l.head = newNode
	} else {
		temp := l.head
		for temp.next != nil {
			temp = temp.next
		}
		temp.next = newNode
		newNode.prev = temp
	}
}

func (l *List[T]) DeleteNode(data T) {
	if l.IsEmpty() {
		return
	}
	temp := l.head
	for temp != nil {
		if Equal(temp.data, data) {
			if temp.prev == nil {
				l.head = temp.next
				if temp.next != nil {
					temp.next.prev = nil
				}
			} else if temp.next == nil {
				temp.prev.next = nil
			} else {
				temp.prev.next = temp.next
				temp.next.prev = temp.prev
			}
			break
		}
		temp = temp.next
	}
}

func (l *List[T]) PrintList() {
	temp := l.head
	for temp != nil {
		fmt.Print(temp.data, " -> ")
		temp = temp.next
	}
	fmt.Println("NULL")
}
