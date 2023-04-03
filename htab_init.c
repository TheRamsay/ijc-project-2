#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

htab_t *htab_init(const size_t n) {
    htab_t *hash_table = malloc(sizeof(*hash_table));

    if (hash_table == NULL) {
        return NULL;
    }

    hash_table->arr_ptr = malloc(sizeof(*hash_table->arr_ptr) * n);

    if (hash_table->arr_ptr == NULL) {
        free(hash_table);
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        hash_table->arr_ptr[i] = NULL;
    }

    hash_table->size = 0;
    hash_table->arr_size = n;

    return hash_table;
}