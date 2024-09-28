package main

import "fmt"

func main() {
	t := NewTree[int]()

	err := t.InsertNode(10)
	if err != nil {
		fmt.Println("Error:", err)
	}
	t.InsertNode(5)
	t.InsertNode(20)
	t.InsertNode(3)
	t.InsertNode(7)
	t.InsertNode(15)
	t.InsertNode(30)

	err = t.InsertNode(10)
	if err != nil {
		fmt.Println("Error:", err)
	}

	err = t.DeleteNode(7)
	if err != nil {
		fmt.Println("Error:", err)
	}
	err = t.DeleteNode(20)
	if err != nil {
		fmt.Println("Error:", err)
	}
	err = t.DeleteNode(10)
	if err != nil {
		fmt.Println("Error:", err)
	}

	err = t.DeleteNode(100)
	if err != nil {
		fmt.Println("Error:", err)
	}
}
