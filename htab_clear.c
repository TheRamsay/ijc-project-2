#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

void htab_clear(htab_t *t) {
    if (t == NULL) {
        return;
    }

    for (size_t i = 0; i < t->arr_size; i++) {
        struct htab_item *item = t->arr_ptr[i];

        while (item != NULL) {
            struct htab_item *prev = item;
            item = item->next;
            free(prev->pair.key);
            free(prev);
        }

        t->arr_ptr[i] = NULL;
    }

    t->size = 0;
}