#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hash_table *hash_table_init(enum data_type type, int size) {
    struct hash_table *table =
        (struct hash_table *)malloc(sizeof(struct hash_table));
    if (!table) {
        return NULL;
    }

    table->type = type;
    table->size = size;
    table->buckets = calloc(size, sizeof(struct hash_table *));
    if (!table->buckets) {
        free(table);
        return NULL;
    }

    return table;
}

int set_data(enum data_type type, struct hash_entry *entry, void *data) {
    switch (type) {
    case INT:
        entry->int_val = *(int *)data;
        break;
    case FLOAT:
        entry->float_val = *(float *)data;
        break;
    case DOUBLE:
        entry->double_val = *(double *)data;
        break;
    case CHAR:
        entry->char_val = *(char *)data;
        break;
    case LONG:
        entry->long_val = *(long *)data;
        break;
    case SHORT:
        entry->short_val = *(short *)data;
        break;
    case BOOL:
        entry->bool_val = *(bool *)data;
        break;
    case STRING:
        entry->string_val = (char *)malloc(strlen((char *)data) + 1);
        if (!entry->string_val) {
            return HASH_TABLE_ERROR_MALLOC;
        }
        strncpy(entry->string_val, (char *)data, strlen((char *)data) + 1);
        break;
    case POINTER:
        entry->pointer_val = data;
        break;
    default:
        return HASH_TABLE_ERROR_TYPE_MISMATCH;
    }
    return HASH_TABLE_SUCCESS;
}

int get_data(enum data_type type, struct hash_entry *entry, void *value) {
    switch (type) {
    case INT:
        *(int *)value = entry->int_val;
        break;
    case FLOAT:
        *(float *)value = entry->float_val;
        break;
    case DOUBLE:
        *(double *)value = entry->double_val;
        break;
    case CHAR:
        *(char *)value = entry->char_val;
        break;
    case LONG:
        *(long *)value = entry->long_val;
        break;
    case SHORT:
        *(short *)value = entry->short_val;
        break;
    case BOOL:
        *(bool *)value = entry->bool_val;
        break;
    case STRING:
        if (entry->string_val == NULL) {
            return HASH_TABLE_ERROR_NULL;
        }
        char **string_data = (char **)value;
        *string_data = (char *)malloc(strlen(entry->string_val) + 1);
        if (*string_data == NULL) {
            return HASH_TABLE_ERROR_MALLOC;
        }
        strncpy(*string_data, entry->string_val, strlen(entry->string_val) + 1);
        break;
    case POINTER:
        *(void **)value = entry->pointer_val;
        break;
    default:
        return HASH_TABLE_ERROR_TYPE_MISMATCH;
    }
    return HASH_TABLE_SUCCESS;
}

// djb2
unsigned long hash_function(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
}

int hash_table_put(struct hash_table *table, const char *key, void *value) {
    if (table == NULL) {
        fprintf(stderr, "Error - table is NULL in insert_node\n");
        return HASH_TABLE_ERROR_NULL;
    }

    unsigned long index = hash_function(key) % table->size;

    struct hash_entry *current = table->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            int set_result =
                set_data(table->type, table->buckets[index], value);
            if (set_result != HASH_TABLE_SUCCESS && table->type == STRING) {
                free(table->buckets[index]->string_val);
            }
            return set_result;
        }
        current = current->next;
    }

    struct hash_entry *new_entry =
        (struct hash_entry *)malloc(sizeof(struct hash_entry));
    if (new_entry == NULL) {
        perror("Error - malloc failed in insert_node");
        return HASH_TABLE_ERROR_MALLOC;
    }

    new_entry->key = strdup(key);
    if (new_entry->key == NULL) {
        return HASH_TABLE_ERROR_MALLOC;
    }

    int set_result = set_data(table->type, new_entry, value);
    if (set_result != HASH_TABLE_SUCCESS) {
        if (table->type == STRING) {
            free(current->string_val);
        }
        free(new_entry);
        return set_result;
    }

    new_entry->next = table->buckets[index];
    table->buckets[index] = new_entry;

    return HASH_TABLE_SUCCESS;
}

int hash_table_get(struct hash_table *table, const char *key, void *value) {
    if (table == NULL || key == NULL) {
        return HASH_TABLE_ERROR_NULL;
    }

    unsigned long index = hash_function(key) % table->size;

    struct hash_entry *current = table->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            int get_result = get_data(table->type, current, value);
            if (get_result != HASH_TABLE_SUCCESS && table->type == STRING) {
                free(current->string_val);
            }
            return get_result;
        }
        current = current->next;
    }

    return HASH_TABLE_ERROR_KEY_NOT_FOUND;
}

int hash_table_remove(struct hash_table *table, const char *key) {
    if (table == NULL || key == NULL) {
        return HASH_TABLE_ERROR_NULL;
    }

    unsigned long index = hash_function(key) % table->size;

    struct hash_entry *current = table->buckets[index];
    struct hash_entry *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                table->buckets[index] = current->next;
            }

            if (table->type == STRING) {
                free(current->string_val);
            }
            free(current->key);
            free(current);

            return HASH_TABLE_SUCCESS;
        }
        prev = current;
        current = current->next;
    }

    return HASH_TABLE_ERROR_KEY_NOT_FOUND;
}

void hash_table_free(struct hash_table *table) {
    for (unsigned long i = 0; i < table->size; i++) {
        struct hash_entry *current = table->buckets[i];

        while (current != NULL) {
            struct hash_entry *next = current->next;
            if (table->type == STRING) {
                free(current->string_val);
            }
            free(current->key);
            free(current);
            current = next;
        }
    }

    free(table->buckets);
    free(table);
}