#include <stdio.h>
#include <stdlib.h>
#include "htab.h"
#include "io.h"

#define WORD_LENGTH 255 + 1

void print_pair(htab_pair_t *pair) {
    printf("%s\t%d\n", pair->key, pair->value);
}

int main() {
    htab_t *hash_table = htab_init(100);

    char word[1024];
    int length = 0;
    bool warned = false;

    while((length = read_word(word, WORD_LENGTH, stdin)) != EOF) {
        if (length == WORD_LENGTH - 1 && !warned) {
            warned = true;
            fprintf(stderr, "Word limit (%d chars) has been exceeded.\n", WORD_LENGTH);
        }

        htab_pair_t *pair = htab_lookup_add(hash_table, word);
        pair->value++;
    }


    htab_for_each(hash_table, &print_pair);
    htab_free(hash_table);
    return 0;
}