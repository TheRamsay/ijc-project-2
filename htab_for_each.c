#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
    if (t == NULL || f == NULL) {
        return;
    }

    for (size_t i = 0; i < t->arr_size; i++) {
        struct htab_item *item = t->arr_ptr[i];
        while (item != NULL) {
            f(&item->pair);
            item = item->next;
        }
    }    
}