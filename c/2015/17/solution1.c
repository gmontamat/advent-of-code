#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_DS_IMPLEMENTATION
#include "../thirdparty/stb_ds.h"

int compare(const void* a, const void* b) {
    int32_t arg1 = *(const int32_t*)a;
    int32_t arg2 = *(const int32_t*)b;
    if (arg1 < arg2) return 1;
    if (arg1 > arg2) return -1;
    return 0;
}

int32_t dfs(int32_t liters, int32_t *containers) {
    int32_t ways = 0;
    for (size_t i=0; i<(size_t)arrlen(containers); ++i) {
        if (containers[i] < liters) {
            int32_t *remaining = NULL;
            for (size_t j=i+1; j<(size_t)arrlen(containers); ++j) {
                arrput(remaining, containers[j]);
            }
            ways += dfs(liters - containers[i], remaining);
            arrfree(remaining);
        } else if (containers[i] == liters) {
            ways++;
        }
    }
    return ways;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    int32_t eggnog = 25;
    if (strcmp(argv[1], "input") == 0) eggnog = 150;

    // Advent of DFS and sort
    int32_t container_size;
    int32_t *containers = NULL;

    while (fscanf(f, "%d", &container_size) == 1) {
        arrput(containers, container_size);
    }

    // sort list descending
    qsort(containers, arrlen(containers), sizeof(int32_t), compare);
    // for (size_t i=0; i<(size_t)arrlen(containers); ++i) {
    //     printf("%d\n", containers[i]);
    // }

    printf("%d\n", dfs(eggnog, containers));

    return 0;
}
