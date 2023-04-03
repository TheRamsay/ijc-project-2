#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "htab.h"
#include "htab_private.h"

void htab_statistics(const htab_t *t) {
    if (t == NULL) {
        return;
    }

    int min = INT_MAX;
    int max = 0;
    
    int *list_lengths = calloc(t->arr_size, sizeof(*list_lengths));
    if (list_lengths == NULL) {
        return;
    }

    for (size_t i = 0; i < t->arr_size; i++) {
        struct htab_item *item = t->arr_ptr[i];
        while (item != NULL) {
            list_lengths[i]++;
            if (list_lengths[i] > max) {
                max = list_lengths[i];
            }

            if (list_lengths[i] < min) {
                min = list_lengths[i];
            }

            item = item->next;
        }
    }

    int sum = 0;

    for (size_t i = 0; i < t->arr_size; i++) {
        sum += list_lengths[i];
    }

    fprintf(stderr, "min: %d\n", min);
    fprintf(stderr, "max: %d\n", max);
    fprintf(stderr, "avg: %f\n", (double) sum / (double) t->arr_size);
}