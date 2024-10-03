#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

enum data_type { 
    INT,
    FLOAT,
    STRING,
    DOUBLE,
    CHAR,
    LONG,
    SHORT,
    BOOL,
    POINTER,
};

struct list_node {
    union {
        int int_val;
        float float_val;
        char *string_val;
        double double_val;
        char char_val;
        long long_val;
        short short_val;
        bool bool_val;
        void *pointer_val;
    };
    struct list_node *next;
    struct list_node *prev;
};

struct list {
    struct list_node *head;
    enum data_type type;
    int size;
};

enum list_error_code {
    LIST_SUCCESS = 0,
    LIST_ERROR_NULL = -1,
    LIST_ERROR_EMPTY = -2,
    LIST_ERROR_MALLOC = -3,
    LIST_ERROR_TYPE_MISMATCH = -4, 
    LIST_ERROR_INDEX_OUT_OF_BOUNDS = -5
};

struct list *init_list(enum data_type type);
int insert_node(struct list *list, void *data, int idx);
int delete_node(struct list *list, int idx);
void print_list(const struct list *list);
void free_list(struct list *list);
#endif // LIST_H