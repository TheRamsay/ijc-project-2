#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 4095

typedef struct {
    int read_index;
    int write_index;
    int size;
    char **data;
} CircularBuffer;

CircularBuffer *cb_create(int n) {
    char **data_ptr = malloc(sizeof(char*) * n);

    if (data_ptr == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        char *item_ptr = malloc(sizeof(char) * LINE_LENGTH);
        if (data_ptr == NULL) {
            free(data_ptr);
            return NULL;
        }

        data_ptr[i] = item_ptr;
    }

    CircularBuffer *cb = malloc(sizeof(*cb)) ;
    if (cb == NULL) {
        for (int i = 0; i < n; i++) {
            free(data_ptr[i]);
        }
        
        free(data_ptr);
    }

    *cb = (CircularBuffer) { .data = data_ptr, .size = n };
    return cb;
}

void cb_put(CircularBuffer *cb, char *line) {
    strcpy(cb->data[cb->write_index++], line);
    cb->write_index %= cb->size;
}

char *cb_get(CircularBuffer *cb) {
    char *item = cb->data[cb->read_index++];
    cb->read_index %= cb->size;
    return item;
}

void cb_free(CircularBuffer *cb) {
    for (int i = 0; i < cb->size; i++) {
        free(cb->data[i]);
    }
    
    free(cb->data);
    free(cb);
}

int main(int argc, char** argv) {
    FILE *f;
    int lines_limit = 10;
    char *file_name = "";

    if (argc > 4) {
        fprintf(stderr, "Unknown arguments.\n");
        return EXIT_FAILURE;
    }

    switch (argc) {
        case 2:
            file_name = argv[1];
            break;
        case 3:
            if (strcmp(argv[1], "-n") != 0) {
                fprintf(stderr, "Unknown arguments.\n");
                return EXIT_FAILURE;
            }

            lines_limit = atoi(argv[2]);
            break;
        case 4: ;
            int n_pos = 0;
            for (int i = 1; i < argc - 1; i++) {
                if (strcmp(argv[i], "-n") == 0) {
                    lines_limit = atoi(argv[i + 1]);
                    n_pos = i;
                    break;
                }
            }

            if (n_pos == 0) {
                fprintf(stderr, "Expected value for -n parameter.\n");
                return EXIT_FAILURE;
            }

            if (n_pos - 1 >= 1) {
                file_name = argv[n_pos - 1];
            } else if (n_pos + 2 < argc) {
                file_name = argv[n_pos + 2];
            } else {
                fprintf(stderr, "Expected [FILE_NAME].\n");
                return EXIT_FAILURE;
            }

            break;
    }

    if (strlen(file_name) == 0) {
        f = stdin;
    } else {
        f = fopen(file_name, "r");
    }

    char line[LINE_LENGTH];
    CircularBuffer *cb = cb_create(lines_limit);

    while (fgets(line, LINE_LENGTH, f) != NULL) {
        cb_put(cb, line);
    }

    cb->read_index = (cb->write_index + lines_limit) % cb->size;

    for (int i = 0; i < lines_limit; i++) {
        printf("%s", cb_get(cb));
    }

    cb_free(cb);
    fclose(f);
}