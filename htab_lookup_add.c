#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

#define MAX_LOAD_FACTOR 0.75

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    if (t == NULL) {
        return NULL;
    }

    htab_pair_t *pair = htab_find(t, key);

    if (pair!= NULL) {
        return pair;
    }

    struct htab_item *item = malloc(sizeof(*item));
    if (item == NULL) {
        return NULL;
    }

    item->next = NULL;
    item->pair.value = 0;
    item->pair.key = malloc(sizeof(char) * (strlen(key) + 1));
    if (item->pair.key == NULL) {
        free(item);
        return NULL;
    }

    strcpy(item->pair.key, key);

    size_t index = htab_hash_function(key) % t->arr_size;

    if (t->arr_ptr[index] == NULL) {
        t->arr_ptr[index] = item;
    } else {
        struct htab_item *prev = t->arr_ptr[index];
        while (prev->next != NULL) {
            prev = prev->next;
        }

        prev->next = item;
    }

    t->size++;

    return &item->pair;
}