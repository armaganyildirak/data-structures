#include <stdio.h>
#include <stdlib.h>
#include "list.h"


void test_init_list() {
    struct list *list = init_list();
    if (list->head != NULL) {
        printf("test_init_list failed\n");
    } else {
        printf("test_init_list passed\n");
    }
    free(list);
}

void test_insert_node() {
    struct list *list = init_list();
    int data1 = 1, data2 = 2;

    insert_node(list, &data1);
    insert_node(list, &data2);

    print_list(list);

    struct list_node *temp = list->head;
    if (temp == NULL || *(int *)temp->data != 1) {
        printf("test_insert_node failed\n");
        free(list);
        return;
    }
    temp = temp->next;
    if (temp == NULL || *(int *)temp->data != 2) {
        printf("test_insert_node failed\n");
        free(list);
        return;
    }
    if (temp->next != NULL) {
        printf("test_insert_node failed\n");
    } else {
        printf("test_insert_node passed\n");
    }
    free(list);
}

void test_print_list() {
    struct list *list = init_list();
    int data1 = 1, data2 = 2, data3 = 3;

    insert_node(list, &data1);
    insert_node(list, &data2);
    insert_node(list, &data3);

    printf("Testing print_list:\n");
    print_list(list);

    free(list);
}

void test_delete_node() {
    struct list *list = init_list();
    int data1 = 1, data2 = 2, data3 = 3;

    insert_node(list, &data1);
    insert_node(list, &data2);
    insert_node(list, &data3);

    delete_node(list, &data2);

    print_list(list);

    struct list_node *temp = list->head;
    if (temp == NULL || *(int *)temp->data != 1) {
        printf("test_delete_node failed\n");
        free(list);
        return;
    }
    temp = temp->next;
    if (temp == NULL || *(int *)temp->data != 3) {
        printf("test_delete_node failed\n");
        free(list);
        return;
    }
    if (temp->next != NULL) {
        printf("test_delete_node failed\n");
    } else {
        printf("test_delete_node passed\n");
    }
    free(list);
}

int main() {
    test_init_list();
    test_insert_node();
    test_print_list();
    test_delete_node();
    return 0;
}