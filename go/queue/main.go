package main

import "fmt"

func main() {
	queue := NewQueue[int]()

	queue.Enqueue(10)
	queue.Enqueue(20)
	queue.Enqueue(30)

	data, err := queue.Dequeue()
	if err != nil {
		fmt.Println("Error: ", err)
	} else {
		fmt.Println("Dequeued data: ", data)
	}

}
