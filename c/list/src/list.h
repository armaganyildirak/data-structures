#ifndef LIST_H
#define LIST_H

struct list_node {
    void *data;
    struct list_node *next;
    struct list_node *prev;
};

struct list {
    struct list_node *head;
};

struct list *init_list();
struct list_node *create_node(void *data);
void insert_node(struct list **list, void *data);
void delete_node(struct list **list, void *data);
void print_list(struct list *list);

#endif // LIST_H