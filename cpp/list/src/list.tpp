#include <iostream>
#include <stdexcept>
#include "list.h"

template <typename T>
List<T>::List() : head(nullptr) {}

template <typename T>
List<T>::~List() {
    while (head != nullptr) {
        ListNode *temp = head;
        head = head->next;

        if (head != nullptr) {
            head->prev = nullptr;
        }

        delete temp;
    }
}

template <typename T>
void List<T>::insert_node(const T &data) {
    ListNode *new_node = new ListNode;
    if (new_node == nullptr) {
        throw std::runtime_error("Error - Memory allocation failed");
    }
    new_node->data = data;
    new_node->next = nullptr;
    new_node->prev = nullptr;

    if (head == nullptr) {
        head = new_node;
    } else {
        ListNode *temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->prev = temp;
    }
}

template <typename T>
void List<T>::delete_node(const T &data) {
    if (head == nullptr) {
        throw std::underflow_error("Error - List is empty");
    }
    
    ListNode *temp = head;
    while (temp != nullptr) {
        if (temp->data == data) {
            if (temp->prev != nullptr) {
                temp->prev->next = temp->next;
            } else {
                head = temp->next;
            }

            if (temp->next != nullptr) {
                temp->next->prev = temp->prev;
            }

            delete temp;
            return;
        }
        temp = temp->next;
    }
    throw std::runtime_error("Error - Node not found");
}

template <typename T>
void List<T>::print_list() {
    ListNode *temp = head;
    while (temp != nullptr) {
        std::cout << temp->data << " -> ";
        temp = temp->next;
    }
    std::cout << "NULL" << std::endl;
}