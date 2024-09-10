#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct list *init_list() {
    struct list *list = (struct list *)malloc(sizeof(struct list));
    if (list == NULL) {
        printf("Error - malloc failed\n");
        exit(1);
    }
    list->head = NULL;
    return list;
}

struct list_node *create_node(void *data) {
    struct list_node *node = (struct list_node *)malloc(sizeof(struct list_node));
    if (node == NULL) {
        printf("Error - malloc failed\n");
        exit(1);
    }
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void insert_node(struct list **list, void *data) {
    struct list_node *node = create_node(data);
    if ((*list)->head == NULL) {
        (*list)->head = node;
    } else {
        struct list_node *temp = (*list)->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
        node->prev = temp;
    }
}

void print_list(struct list *list) {
    struct list_node *temp = list->head;
    while (temp != NULL) {
        printf("%d -> ", *(int *)temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void delete_node(struct list **list, void *data) {
    if ((*list)->head == NULL || data == NULL) {
        printf("Error - the list is empty\n");
        exit(1);
    }

    if (*(int *)(*list)->head->data == *(int *)data) {
        (*list)->head = (*list)->head->next;
        return;
    }

    struct list_node *temp = (*list)->head;
    while (temp->next != NULL) {
        if (*(int *)temp->data == *(int *)data) {
            break;
        }
        temp = temp->next;
    }
    if (temp->next == NULL) {
        temp->prev->next = NULL;
    } else {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }
}