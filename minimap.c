#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE 1000000

struct entry {
    char *key;
    void *value;
    struct entry *next;
};

struct hash_table {
    struct entry *entries[HASH_TABLE_SIZE];
};

struct hash_table *create_hash_table() {
    struct hash_table *table = malloc(sizeof(struct hash_table));
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        table->entries[i] = NULL;
    }
    return table;
}

int hash_function(char *key) {
    int hash = 0;
    for (int i = 0; i < strlen(key); i++) {
        hash = (hash + key[i]) % HASH_TABLE_SIZE;
    }
    return hash;
}

void set(struct hash_table *table, char *key, void *value) {
    int hash = hash_function(key);
    struct entry *entry = table->entries[hash];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;
            return;
        }
        entry = entry->next;
    }
    entry = malloc(sizeof(struct entry));
    entry->key = key;
    entry->value = value;
    // linked list
    entry->next= table->entries[hash];
    table->entries[hash] = entry;
}

void *get(struct hash_table *table, char *key) {
    int hash = hash_function(key);
    struct entry *entry = table->entries[hash];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

void delete(struct hash_table *table, char *key) {
    int hash = hash_function(key);
    struct entry *entry = table->entries[hash];
    struct entry *prev = NULL;
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            if (prev == NULL) {
                table->entries[hash] = entry->next;
            } else {
                prev->next = entry->next;
            }
            free(entry);
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

