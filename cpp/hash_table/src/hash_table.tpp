#include <cstring>
#include <stdexcept>

template <typename T>
HashTable<T>::HashTable(unsigned long size) : size(size) {
    buckets = new HashEntry*[size]();
}

template <typename T>
HashTable<T>::~HashTable() {
    hash_table_free();
    delete[] buckets;
}

template <typename T>
void HashTable<T>::hash_table_put(const char *key, const T &data) {
    unsigned long index = hash_function(key) % size;
    HashEntry *newEntry = new HashEntry{data, strdup(key), nullptr};

    if (buckets[index] != nullptr) {
        newEntry->prev = buckets[index];
    }
    buckets[index] = newEntry;
}

template <typename T>
T HashTable<T>::hash_table_get(const char *key) {
    unsigned long index = hash_function(key) % size;
    HashEntry *entry = buckets[index];

    while (entry != nullptr) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->prev;
    }

    throw std::runtime_error("Key not found");
}

template <typename T>
void HashTable<T>::hash_table_remove(const char *key) {
    unsigned long index = hash_function(key) % size;
    HashEntry *entry = buckets[index];
    HashEntry *prev = nullptr;

    while (entry != nullptr) {
        if (strcmp(entry->key, key) == 0) {
            if (prev == nullptr) {
                buckets[index] = entry->prev;
            } else {
                prev->prev = entry->prev;
            }
            free(entry->key);
            delete entry;
            return;
        }
        prev = entry;
        entry = entry->prev;
    }
}

template <typename T>
void HashTable<T>::hash_table_free() {
    for (unsigned long i = 0; i < size; ++i) {
        HashEntry *entry = buckets[i];
        while (entry != nullptr) {
            HashEntry *next = entry->prev;
            free(entry->key);
            delete entry;
            entry = next;
        }
        buckets[i] = nullptr;
    }
}

template <typename T>
unsigned long HashTable<T>::hash_function(const char *key) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}
