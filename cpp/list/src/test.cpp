#include <cassert>
#include "list.h"

void test_insert_node() {
    List<int> list;
    int data1 = 10;
    int data2 = 20;
    int data3 = 30;

    list.insert_node(data1);
    assert(list.head->data == 10);

    list.insert_node(data2);
    assert(list.head->next->data == 20);

    list.insert_node(data3);
    assert(list.head->next->next->data == 30);
    assert(list.head->next->next->next == nullptr);
}

void test_delete_node() {
    List<int> list;
    int data1 = 10;
    int data2 = 20;
    int data3 = 30;

    list.insert_node(data1);
    list.insert_node(data2);
    list.insert_node(data3);

    list.delete_node(data2);
    assert(list.head->next->data == 30);

    list.delete_node(data1);
    assert(list.head->data == 30);

    list.delete_node(data3);
    assert(list.head == nullptr);
}

void test_print_list() {
    List<int> list;
    int data1 = 10;
    int data2 = 20;
    int data3 = 30;

    list.insert_node(data1);
    list.insert_node(data2);
    list.insert_node(data3);

    list.print_list();
}

int main() {
    test_insert_node();
    test_delete_node();
    test_print_list();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}