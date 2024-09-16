#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct list *init_list() {
    struct list *list = (struct list *)malloc(sizeof(struct list));
    if (list == NULL) {
        perror("Error - malloc failed");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    return list;
}

struct list_node *create_node(void *data) {
    struct list_node *node = (struct list_node *)malloc(sizeof(struct list_node));
    if (node == NULL) {
        perror("Error - malloc failed");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void insert_node(struct list *list, void *data) {
    struct list_node *node = create_node(data);
    if (list->head == NULL) {
        list->head = node;
    } else {
        struct list_node *temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
        node->prev = temp;
    }
}

void print_list(const struct list *list) {
    struct list_node *temp = list->head;
    while (temp != NULL) {
        printf("%d -> ", *(int *)temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void delete_node(struct list *list, void *data) {
    if (list->head == NULL || data == NULL) {
        fprintf(stderr, "Error - the list is empty or data is NULL\n");
        return;
    }

    struct list_node *temp = list->head;
    while (temp != NULL) {
        if (*(int *)temp->data == *(int *)data) {
            if (temp->prev != NULL) {
                temp->prev->next = temp->next;
            } else {
                list->head = temp->next;
            }
            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
            }
            free(temp);
            return;
        }
        temp = temp->next;
    }

    fprintf(stderr, "Error - data not found in the list\n");
}

void free_list(struct list *list) {
    struct list_node *temp = list->head;
    while (temp != NULL) {
        struct list_node *next_node = temp->next;
        free(temp);
        temp = next_node;
    }
    free(list);
}