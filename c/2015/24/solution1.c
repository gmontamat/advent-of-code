#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_DS_IMPLEMENTATION
#include "../thirdparty/stb_ds.h"

ptrdiff_t min_size = PTRDIFF_MAX;

uint64_t calculateWeight(uint64_t *weights, ptrdiff_t *assignments, ptrdiff_t group) {
    uint64_t weight = 0;
    for (ptrdiff_t i = 0; i < arrlen(assignments); ++i) {
        if (assignments[i] == group) weight += weights[i];
    }
    return weight;
}

uint64_t calculateEntanglement(uint64_t *weights, ptrdiff_t *assignments) {
    uint64_t product = 1;
    for (ptrdiff_t i = 0; i < arrlen(assignments); ++i) {
        if (assignments[i] == 0) product *= weights[i];
    }
    return product;
}

ptrdiff_t countPackages(ptrdiff_t *assignments, ptrdiff_t group) {
    ptrdiff_t count = 0;
    for (ptrdiff_t i = 0; i < arrlen(assignments); ++i) {
        if (assignments[i] == group) count++;
    }
    return count;
}

uint64_t dfs(uint64_t *weights, ptrdiff_t *assignments, ptrdiff_t item, uint64_t min_entanglement, uint64_t sectionw) {
    // Base case
    if (item == arrlen(weights)) {
        if (countPackages(assignments, 0) < min_size) {
            min_size = countPackages(assignments, 0);
            return calculateEntanglement(weights, assignments);
        } else {
            if (countPackages(assignments, 0) == min_size) {
                if (calculateEntanglement(weights, assignments) < min_entanglement) {
                    return calculateEntanglement(weights, assignments);
                } else {
                    return min_entanglement;
                }
            } else {
                return min_entanglement;
            }
        }
    }
    // Prune branches
    if (countPackages(assignments, 0) == min_size) {
        if (calculateEntanglement(weights, assignments) >= min_entanglement) return min_entanglement;
    }
    // Recursion (assign item to group and update next item)
    for (ptrdiff_t i = 0; i < 3; ++i) {
        if (i == 0 && countPackages(assignments, 0) + 1 > min_size) continue;
        if (calculateWeight(weights, assignments, i) + weights[item] <= sectionw) {
            ptrdiff_t *next_assignments = NULL;
            for (ptrdiff_t j = 0; j < arrlen(assignments); ++j) arrput(next_assignments, assignments[j]);
            arrput(next_assignments, i);
            min_entanglement = dfs(weights, next_assignments, item + 1, min_entanglement, sectionw);
            arrfree(next_assignments);
        }
    }
    return min_entanglement;
}

int compare(const void* a, const void* b) {
    uint64_t arg1 = *(const uint64_t*)a;
    uint64_t arg2 = *(const uint64_t*)b;
    if (arg1 < arg2) return 1;
    if (arg1 > arg2) return -1;
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    uint64_t *weights = NULL;
    uint64_t weight;
    ptrdiff_t *assignments = NULL;
    uint64_t min_entanglement = UINT64_MAX;

    // Read package weights
    while (fscanf(f, "%lu", &weight) == 1) {
        arrput(weights, weight);
    }
    fclose(f);

    uint64_t totalw = 0;
    for (ptrdiff_t i = 0; i<arrlen(weights); ++i) totalw += weights[i];
    uint64_t sectionw = totalw / 3;

    // Sort packages by weight (descending)
    qsort(weights, arrlen(weights), sizeof(uint64_t), compare);
    // Solve
    printf("%lu\n", dfs(weights, assignments, 0, min_entanglement, sectionw));
    // printf(" (Group 1 packages: %td)\n", min_size);
    return 0;
}
