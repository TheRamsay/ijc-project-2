#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

htab_pair_t *htab_find(const htab_t *t, htab_key_t key) {
    if (t == NULL) {
        return NULL;
    }

    size_t index = htab_hash_function(key)% t->arr_size;

    struct htab_item *item = t->arr_ptr[index];
    while (item != NULL) {
        if (strcmp(item->pair.key, key) == 0) {
            return &(item->pair);
        }

        item = item->next;
    }

    return NULL;
}