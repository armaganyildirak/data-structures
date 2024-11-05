package main

import "errors"

type HashEntry[T any] struct {
	key   string
	value T
	next  *HashEntry[T]
}

type HashTable[T any] struct {
	buckets []*HashEntry[T]
	size    uint64
}

var (
	ErrHTEmpty      = errors.New("hash table is empty")
	ErrDataNotFound = errors.New("data not found")
	ErrKeyEmpty     = errors.New("key is empty")
)

func NewHashTable[T any](size uint64) *HashTable[T] {
	return &HashTable[T]{
		buckets: make([]*HashEntry[T], size),
		size:    size,
	}
}

func (ht *HashTable[T]) hash(key string) uint64 {
	var hash uint64
	hash = 5381

	for _, c := range key {
		hash = ((hash << 5) + hash) + uint64(c)
	}

	return hash
}

func (ht *HashTable[T]) Put(key string, value T) error {
	if ht == nil {
		return ErrHTEmpty
	}

	index := ht.hash(key) % ht.size
	entry := ht.buckets[index]

	if entry == nil {
		ht.buckets[index] = &HashEntry[T]{key, value, nil}
		return nil
	}

	var prev *HashEntry[T]
	for entry != nil {
		if entry.key == key {
			entry.value = value
			return nil
		}

		prev = entry
		entry = entry.next
	}

	prev.next = &HashEntry[T]{key, value, nil}
	return nil
}

func (ht *HashTable[T]) Get(key string) (T, error) {
	var value T
	if ht == nil {
		return value, ErrHTEmpty
	}

	index := ht.hash(key) % ht.size
	entry := ht.buckets[index]

	for entry != nil {
		if entry.key == key {
			return entry.value, nil
		}
		entry = entry.next
	}

	return value, ErrDataNotFound
}

func (ht *HashTable[T]) Delete(key string) error {
	if ht == nil {
		return ErrHTEmpty
	}

	index := ht.hash(key) % ht.size
	entry := ht.buckets[index]

	if entry == nil {
		return ErrDataNotFound
	}

	if entry.key == key {
		ht.buckets[index] = entry.next
		return nil
	}

	var prev *HashEntry[T]
	for entry != nil {
		if entry.key == key {
			prev.next = entry.next
			return nil
		}
		prev = entry
		entry = entry.next
	}

	return ErrDataNotFound
}
