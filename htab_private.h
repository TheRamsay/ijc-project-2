#ifndef HTAB_PRIVATE_H
#define HTAB_PRIVATE_H

#include <stdlib.h>
#include "htab.h"

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item **arr_ptr;
};

struct htab_item {
    struct htab_pair pair;
    struct htab_item *next;
};

#endif