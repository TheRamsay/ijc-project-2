#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

void htab_free(htab_t *t) {
    if (t == NULL) {
        return;
    }

    htab_clear(t);
    free(t->arr_ptr);
    free(t);
}