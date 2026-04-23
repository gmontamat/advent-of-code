#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 32

size_t min_size = 99;  // minimum size of group 1 tracked globally (minimum entanglement locally in the DFS call)

int compare(const void* a, const void* b) {
    uint64_t arg1 = *(const uint64_t*)a;
    uint64_t arg2 = *(const uint64_t*)b;
    if (arg1 < arg2) return 1;
    if (arg1 > arg2) return -1;
    return 0;
}

uint64_t dfs(uint64_t *weights, int32_t *assignments, size_t item, uint64_t min_entanglement, uint64_t sectionw,
             uint64_t *group_weights, uint64_t current_entanglement, size_t current_count, size_t packages) {
    if (item == packages) {
        if (current_count < min_size) {
            min_size = current_count;
            min_entanglement = current_entanglement;
            // printf("> %lu (%zu)\n", min_entanglement, min_size);
            return min_entanglement;
        } else if (current_count == min_size && current_entanglement < min_entanglement) {
            min_entanglement = current_entanglement;
            // printf("> %lu (%zu)\n", min_entanglement, min_size);
            return min_entanglement;
        }
        return min_entanglement;
    }

    if (current_count == min_size && current_entanglement >= min_entanglement) return min_entanglement;

    uint64_t w = weights[item];
    for (size_t i = 0; i < 4; ++i) {
        if (i == 0 && current_count + 1 > min_size) continue;
        if (group_weights[i] + w > sectionw) continue;
        // Assign item to group i
        assignments[item] = (int32_t)i;
        group_weights[i] += w;
        // Variables for recursion
        uint64_t next_entanglement = current_entanglement;
        size_t next_count = current_count;
        if (i == 0) {
            next_entanglement *= w;
            next_count++;
            if (next_entanglement >= min_entanglement) {
                // Backtrack and continue
                group_weights[i] -= w;
                assignments[item] = -1;
                continue;
            }
        }
        // Recursion and then backtrack
        min_entanglement = dfs(
            weights, assignments, item + 1, min_entanglement, sectionw, group_weights,
            next_entanglement, next_count, packages);
        group_weights[i] -= w;
        assignments[item] = -1;
    }
    return min_entanglement;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution2.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    // This is basically solution1.c with optimizations:
    // * Do not use dynamic arrays
    // * Do not re-compute number or packages (compute while reading and pass along)
    // * Do not copy assignments (use -1 and backtrack)
    // * Do not re-compute group weights (keep track and backtrack)
    uint64_t weights[BUFFER_SIZE];
    size_t packages = 0;
    int32_t assignments[BUFFER_SIZE];
    uint64_t min_entanglement = UINT64_MAX;

    while (fscanf(f, "%lu", &weights[packages]) == 1) packages++;
    fclose(f);

    uint64_t totalw = 0;
    for (size_t i = 0; i < packages; ++i) totalw += weights[i];
    uint64_t sectionw = totalw / 4;

    // Sort packages by weight (descending)
    qsort(weights, packages, sizeof(uint64_t), compare);

    for (size_t i = 0; i < packages; ++i) assignments[i] = -1;
    uint64_t group_weights[4] = {0,0,0,0};
    uint64_t entanglement = dfs(weights, assignments, 0, min_entanglement, sectionw, group_weights, 1, 0, packages);

    // printf("%lu (Group 1 packages: %zu)\n", entanglement, min_size);
    printf("%lu\n", entanglement);
    return 0;
}
