#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


// Dynamic array (based on tsoding's std::vector)
typedef struct {
    char *items;
    size_t count;
    size_t capacity;
} String;

#define da_append(xs, x) \
    do { \
        if (xs.count >= xs.capacity) { \
            if (xs.capacity == 0) xs.capacity = 256; \
            else xs.capacity *= 2; \
            xs.items = realloc(xs.items, xs.capacity * sizeof(*xs.items)); \
        } \
        xs.items[xs.count++] = x; \
    } while (0)

void solve(String input) {
    int32_t floor = 0;

    for (size_t i = 0; i < input.count; ++i) {
        if (input.items[i] == '(') floor++;
        else if (input.items[i] == ')') floor--;
        else printf("WARNING: check your input!\n");
        if (floor < 0) {
            printf("%zu\n", ++i);
            break;
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1 input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    String input = {0};
    int c;
    while ((c = fgetc(f)) != EOF) da_append(input, c);

    solve(input);
    return 0;
}
