package main

import "fmt"

func main() {
	ht := NewHashTable[string](5)
	ht.Put("fruit", "banana")
	ht.Put("protein", "meat")

	val, err := ht.Get("fruit")
	if err == nil {
		fmt.Println("Value for 'fruit':", val)
	}

	val, err = ht.Get("protein")
	if err == nil {
		fmt.Println("Value for 'protein':", val)
	}

	ht.Delete("protein")

	_, err = ht.Get("protein")
	if err != nil {
		fmt.Println(err)
	}
}
