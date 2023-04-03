#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

bool htab_erase(htab_t *t, htab_key_t key) {
    if (t == NULL) {
        return false;
    }

    size_t hash = htab_hash_function(key);
    size_t index = hash % htab_bucket_count(t);

    struct htab_item *item = t->arr_ptr[index];
    struct htab_item *prev = NULL;
    while (item != NULL) {
        if (strcmp(item->pair.key, key) == 0) {
            if (prev == NULL) {
                t->arr_ptr[index] = NULL;
            } else {
                prev->next = item->next;
            }

            free(item->pair.key);
            free(item);

            return true;
        }

        prev = item;
        item = item->next;
    }

    return false;
}