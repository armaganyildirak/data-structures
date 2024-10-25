#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>

enum data_type { 
    INT,
    FLOAT,
    STRING,
    DOUBLE,
    CHAR,
    LONG,
    SHORT,
    BOOL,
    POINTER,
};

struct hash_entry {
    char *key;
    union {
        int int_val;
        float float_val;
        char *string_val;
        double double_val;
        char char_val;
        long long_val;
        short short_val;
        bool bool_val;
        void *pointer_val;
    };
    struct hash_entry *next;
};

struct hash_table {
    struct hash_entry **buckets;
    enum data_type type;
    unsigned long size;
};

enum hash_table_error_code {
    HASH_TABLE_SUCCESS = 0,
    HASH_TABLE_ERROR_NULL = -1,
    HASH_TABLE_ERROR_EMPTY = -2,
    HASH_TABLE_ERROR_MALLOC = -3,
    HASH_TABLE_ERROR_TYPE_MISMATCH = -4, 
    HASH_TABLE_ERROR_KEY_NOT_FOUND = -5,
};

struct hash_table *hash_table_init(enum data_type type, int size);
int hash_table_put(struct hash_table *table, const char *key, void *value);
int hash_table_get(struct hash_table *table, const char *key, void *value);
int hash_table_remove(struct hash_table *table, const char *key);
void hash_table_free(struct hash_table *table);
#endif // HASH_TABLE_H