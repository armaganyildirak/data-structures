package main

import "fmt"

func main() {
	stack := NewStack[int]()

	stack.Push(10)
	stack.Push(20)
	stack.Push(30)

	peeked_value, err := stack.Peek()
	if err != nil {
		fmt.Println("Error: ", err)
	} else {
		fmt.Println("peeked: ", peeked_value)
	}

	popped_value, err := stack.Pop()
	if err != nil {
		fmt.Println("Error: ", err)
	} else {
		fmt.Println("popped: ", popped_value)
	}

}
