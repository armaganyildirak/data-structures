package main

import (
	"fmt"
	"log"
)

func main() {
	cb := NewCircularBuffer()

	fmt.Println("Writing to the buffer:")
	for i := 0; i < 5; i++ {
		err := cb.Write(byte(i + 1))
		if err != nil {
			log.Fatalf("Error writing to buffer: %v", err)
		}
		fmt.Printf("Wrote: %d\n", i+1)
	}

	fmt.Println("Reading from the buffer:")
	for i := 0; i < 5; i++ {
		data, err := cb.Read()
		if err != nil {
			log.Fatalf("Error reading from buffer: %v", err)
		}
		fmt.Printf("Read: %d\n", data)
	}

	_, err := cb.Read()
	if err != nil {
		fmt.Printf("Expected error: %v\n", err)
	}
}
