package main

import (
	"testing"

	"gotest.tools/v3/assert"
)

func TestHashTable_EmptyTable(t *testing.T) {
	var ht *HashTable[int]

	err := ht.Put("key1", 100)
	assert.ErrorIs(t, err, ErrHTEmpty, "Expected ErrHTEmpty when putting to a nil hash table")

	_, err = ht.Get("key1")
	assert.ErrorIs(t, err, ErrHTEmpty, "Expected ErrHTEmpty when getting from a nil hash table")

	err = ht.Delete("key1")
	assert.ErrorIs(t, err, ErrHTEmpty, "Expected ErrHTEmpty when deleting from a nil hash table")
}
