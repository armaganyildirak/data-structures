#include <stdio.h>
#include "list.h"


void test_list_operations() {
    struct list *list = init_list();

    int data1 = 10, data2 = 20, data3 = 30;

    insert_node(&list, &data1);
    insert_node(&list, &data2);
    insert_node(&list, &data3);

    printf("List after inserting 3 elements: ");
    print_list(list);

    delete_node(&list, &data2);
    printf("List after deleting the second element: ");
    print_list(list);

    delete_node(&list, &data3);
    printf("List after deleting the third element: ");
    print_list(list);

    delete_node(&list, &data1);
    printf("List after deleting the second element: ");
    print_list(list);
}

int main() {
    test_list_operations();

    return 0;
}