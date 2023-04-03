#include <stdlib.h>

#ifndef HASHTEST

// http://www.cse.yorku.ca/~oz/hash.html - varianta sdbm):
size_t htab_hash_function(const char *str) {
    int h = 0;
    const unsigned char *p;

    for (p = (const unsigned char*)str; *p != '\0'; p++) {
        h = 65599 * h + *p;
    }

    return h;
}

#else

// Dummy hash function
size_t htab_hash_function(const char *str) {
    size_t h = 0;

    for (int i = 0, str[i] != '\0', i++) {
        h += (int)str[i];
    }

    return h;
}

#endif