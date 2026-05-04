#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX    2000  // bots:       0 through  999
#define OFFSET 1000  // outputs: 1000 through 1999

#define BUFFER_SIZE 256

// Define values to be found globally
int32_t find1 = 5, find2 = 2;

void propagate(size_t *graph_lo, size_t *graph_hi, int32_t *values, int32_t value, size_t to) {
    //printf("%d %zu\n", value, to);
    if (to >= OFFSET) return;  // an output
    if (values[to] == -1) {
        values[to] = value;
        return;
    }
    // we need to propagate!
    //printf("propagate, compare %d - %d\n", value, values[to]);
    if ((value == find1 && values[to] == find2) ||
        (value == find2 && values[to] == find1)) {
        printf("%zu\n", to);
        exit(0);
    }
    int32_t lo, hi;
    if (values[to] > value) {
        hi = values[to];
        lo = value;
    } else {
        hi = value;
        lo = values[to];
    }
    values[to] = -1;
    propagate(graph_lo, graph_hi, values, lo, graph_lo[to]);
    propagate(graph_lo, graph_hi, values, hi, graph_hi[to]);
    return;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    if (strcmp(argv[1], "input") == 0) {
        find1 = 61;
        find2 = 17;
    }

    size_t graph_lo[MAX], graph_hi[MAX];  // graph[from] -> to
    int32_t values[MAX];                  // -1 if empty
    char buffer[BUFFER_SIZE], buffer1[BUFFER_SIZE], buffer2[BUFFER_SIZE];

    int32_t value;
    size_t from, tolo, tohi, to;

    while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline
        if (strstr(buffer, "gives")) {
            sscanf(buffer, "bot %zu gives low to %s %zu and high to %s %zu", &from, buffer1, &tolo, buffer2, &tohi);
            if (strcmp(buffer1, "output") == 0) tolo += OFFSET;
            if (strcmp(buffer2, "output") == 0) tohi += OFFSET;
            graph_lo[from] = tolo;
            graph_hi[from] = tohi;
        }
    }

    // Initialize values bots hold
    for (size_t i = 0; i < MAX; ++i) {
        values[i] = -1;
    }
    fseek(f, 0, SEEK_SET);
    while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline
        if (strstr(buffer, "value")) {
            sscanf(buffer, "value %d goes to bot %zu", &value, &to);
            propagate(graph_lo, graph_hi, values, value, to);
        }
    }
    fclose(f);

    printf("You should't see this message\n");
    return 0;
}
