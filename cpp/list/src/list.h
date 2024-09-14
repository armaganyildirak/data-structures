#ifndef LIST_H
#define LIST_H

template <typename T>
class List {
public:
    struct ListNode {
        T data;
        ListNode *next;
        ListNode *prev;
    };

    ListNode* head;

public:
    List();
    ~List();

    void insert_node(const T &data);

    void delete_node(const T &data);

    void print_list();
};

#include "list.tpp"

#endif // LIST_H