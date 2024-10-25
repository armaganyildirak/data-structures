#include "hash_table.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_int_hash_table() {
    struct hash_table *table = hash_table_init(INT, 1024);
    char *key1 = "key1";
    char *key2 = "key2";
    int data1 = 10, data2 = 20, result;

    assert(hash_table_put(table, key1, &data1) == HASH_TABLE_SUCCESS);
    assert(hash_table_put(table, key2, &data2) == HASH_TABLE_SUCCESS);

    assert(hash_table_get(table, key1, &result) == HASH_TABLE_SUCCESS);
    assert(result == data1);

    assert(hash_table_get(table, key2, &result) == HASH_TABLE_SUCCESS);
    assert(result == data2);

    printf("Integer hash table test passed!\n");

    hash_table_free(table);
}

void test_string_hash_table() {
    struct hash_table *table = hash_table_init(STRING, 1024);
    char *key1 = "greeting";
    char *key2 = "farewell";
    char *data1 = "hello";
    char *data2 = "goodbye";
    char *result;

    assert(hash_table_put(table, key1, data1) == HASH_TABLE_SUCCESS);
    assert(hash_table_put(table, key2, data2) == HASH_TABLE_SUCCESS);

    assert(hash_table_get(table, key1, (void **)&result) == HASH_TABLE_SUCCESS);
    assert(strcmp(result, data1) == 0);
    free(result);

    assert(hash_table_get(table, key2, (void **)&result) == HASH_TABLE_SUCCESS);
    assert(strcmp(result, data2) == 0);
    free(result);
    printf("String hash table test passed!\n");

    hash_table_free(table);
}

void test_update_hash_table() {
    struct hash_table *table = hash_table_init(INT, 1024);
    char *key = "key";
    int data1 = 10, data2 = 30, result;

    assert(hash_table_put(table, key, &data1) == HASH_TABLE_SUCCESS);
    assert(hash_table_get(table, key, &result) == HASH_TABLE_SUCCESS);
    assert(result == data1);

    assert(hash_table_put(table, key, &data2) == HASH_TABLE_SUCCESS);
    assert(hash_table_get(table, key, &result) == HASH_TABLE_SUCCESS);
    assert(result == data2);

    printf("Update hash table test passed!\n");

    hash_table_free(table);
}

void test_remove_hash_table() {
    struct hash_table *table = hash_table_init(INT, 1024);
    char *key = "key";
    int data = 10, result;

    assert(hash_table_put(table, key, &data) == HASH_TABLE_SUCCESS);
    assert(hash_table_remove(table, key) == HASH_TABLE_SUCCESS);
    assert(hash_table_get(table, key, &result) ==
           HASH_TABLE_ERROR_KEY_NOT_FOUND);

    printf("Remove hash table test passed!\n");

    hash_table_free(table);
}

int main() {
    test_int_hash_table();
    test_string_hash_table();
    test_update_hash_table();
    test_remove_hash_table();

    printf("All tests passed!\n");
    return 0;
}
