package main

func main() {
	list := NewList[int]()

	list.InsertNode(10)
	list.InsertNode(20)
	list.InsertNode(30)

	list.PrintList()

	list.DeleteNode(10)
	list.PrintList()

	list.DeleteNode(30)
	list.PrintList()

	list.DeleteNode(20)
	list.PrintList()
}
