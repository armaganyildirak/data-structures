#ifndef HASHTABLE_H
#define HASHTABLE_H

template <typename T>
class HashTable {
public:
    struct HashEntry {
        T value;
        char *key;
        HashEntry *prev;
    };

    HashEntry **buckets;
    unsigned long size;

public:
    HashTable(unsigned long size);
    ~HashTable();

    void hash_table_put(const char *key, const T &data);

    T hash_table_get(const char *key);

    void hash_table_remove(const char *key);

    void hash_table_free();

    unsigned long hash_function(const char *key);
};

#include "hash_table.tpp"

#endif // HASHTABLE_H