#include "hash_table.h"
#include <iostream>
#include <cassert>

void test_basic_put_and_get() {
    HashTable<int> table(10);
    table.hash_table_put("key1", 100);
    table.hash_table_put("key2", 200);

    assert(table.hash_table_get("key1") == 100);
    assert(table.hash_table_get("key2") == 200);

    std::cout << "test_basic_put_and_get passed\n";
}

void test_update_existing_key() {
    HashTable<int> table(10);
    table.hash_table_put("key1", 100);
    table.hash_table_put("key1", 300);

    assert(table.hash_table_get("key1") == 300);

    std::cout << "test_update_existing_key passed\n";
}

void test_remove_key() {
    HashTable<int> table(10);
    table.hash_table_put("key1", 100);
    table.hash_table_remove("key1");

    try {
        table.hash_table_get("key1");
        assert(false);
    } catch (const std::runtime_error&) {
        std::cout << "Expected exception for key not found!" << std::endl;
    }

    std::cout << "test_remove_key passed\n";
}


int main() {
    test_basic_put_and_get();
    test_update_existing_key();
    test_remove_key();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
