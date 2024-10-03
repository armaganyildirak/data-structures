#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_init_list() {
    struct list *int_list = init_list(INT);
    assert(int_list != NULL);
    assert(int_list->size == 0);
    assert(int_list->head == NULL);
    assert(int_list->type == INT);
    free_list(int_list);

    struct list *str_list = init_list(STRING);
    assert(str_list != NULL);
    assert(str_list->size == 0);
    assert(str_list->head == NULL);
    assert(str_list->type == STRING);
    free_list(str_list);

    printf("test_init_list passed!\n");
}

void test_is_empty() {
    struct list *int_list = init_list(INT);
    assert(int_list->head == NULL);

    int val = 10;
    insert_node(int_list, &val, 0);
    assert(int_list->head != NULL);

    free_list(int_list);

    printf("test_is_empty passed!\n");
}

void test_insert_node() {
    struct list *int_list = init_list(INT);

    int val1 = 10, val2 = 20, val3 = 30;
    insert_node(int_list, &val1, 0);
    insert_node(int_list, &val2, 1);
    insert_node(int_list, &val3, 1);

    assert(int_list->size == 3);
    assert(int_list->head->int_val == 10);
    assert(int_list->head->next->int_val == 30);
    assert(int_list->head->next->next->int_val == 20);

    free_list(int_list);
    printf("test_insert_node passed!\n");
}

void test_delete_node() {
    struct list *int_list = init_list(INT);

    int val1 = 10, val2 = 20, val3 = 30;
    insert_node(int_list, &val1, 0);
    insert_node(int_list, &val2, 1);
    insert_node(int_list, &val3, 1);

    assert(delete_node(int_list, 1) == LIST_SUCCESS);
    assert(int_list->size == 2);
    assert(int_list->head->int_val == 10);
    assert(int_list->head->next->int_val == 20);

    assert(delete_node(int_list, 0) == LIST_SUCCESS);
    assert(int_list->size == 1);
    assert(int_list->head->int_val == 20);

    free_list(int_list);
    printf("test_delete_node passed!\n");
}

void test_string_handling() {
    struct list *str_list = init_list(STRING);

    insert_node(str_list, "hello", 0);
    insert_node(str_list, "world", 1);
    insert_node(str_list, "!", 1);

    assert(str_list->size == 3);
    assert(strcmp(str_list->head->string_val, "hello") == 0);
    assert(strcmp(str_list->head->next->string_val, "!") == 0);
    assert(strcmp(str_list->head->next->next->string_val, "world") == 0);

    assert(delete_node(str_list, 1) == LIST_SUCCESS);
    assert(str_list->size == 2);
    assert(strcmp(str_list->head->string_val, "hello") == 0);
    assert(strcmp(str_list->head->next->string_val, "world") == 0);

    free_list(str_list);
    printf("test_string_handling passed!\n");
}

void test_error_handling() {
    struct list *int_list = init_list(INT);

    int val = 10;
    assert(insert_node(NULL, &val, 0) == LIST_ERROR_NULL);
    assert(insert_node(int_list, &val, 2) == LIST_ERROR_INDEX_OUT_OF_BOUNDS);

    assert(delete_node(NULL, 0) == LIST_ERROR_NULL);
    assert(delete_node(int_list, 0) == LIST_ERROR_EMPTY);

    free_list(int_list);
    printf("test_error_handling passed!\n");
}

int main() {
    test_init_list();
    test_is_empty();
    test_insert_node();
    test_delete_node();
    test_string_handling();
    test_error_handling();

    printf("All tests passed!\n");
    return 0;
}
