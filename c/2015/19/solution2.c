#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 512

#define STB_DS_IMPLEMENTATION
#include "../thirdparty/stb_ds.h"

typedef struct {
    char *orig;
    char *dest;
} Replacement;

int compare(const void* a, const void* b) {
    Replacement arg1 = *(const Replacement*)a;
    Replacement arg2 = *(const Replacement*)b;
    if (strlen(arg1.dest) < strlen(arg2.dest)) return 1;
    if (strlen(arg1.dest) > strlen(arg2.dest)) return -1;
    return 0;
}

char* slice(const char *str, size_t start, size_t end) {
    size_t len = end - start;
    char *result = malloc(len + 1);
    strncpy(result, str + start, len);
    result[len] = '\0';
    return result;  // Remember to free()
}

int32_t solve(char *molecule, Replacement *replacements, int32_t steps, int32_t min_steps) {
    // Base case
    if (strcmp(molecule, "e") == 0) {
        printf("%d\n", steps);
        exit(0);  // Apparently there's 1 possible number of steps?
        return steps;
        if (steps < min_steps) return steps;
        else return min_steps;
    }
    // Quick optimizations
    // If there's e and other things, stop
    if (strstr(molecule, "e")) return min_steps;
    // Also stop if current steps >= min_steps:
    if (steps >= min_steps) return min_steps;
    // Recursion
    for (ptrdiff_t i = 0; i < arrlen(replacements); ++i) {
        char *ptr = strstr(molecule, replacements[i].dest);
        while (ptr) {
            // Replace and call myself
            size_t len = strlen(replacements[i].dest);
            char *newmol = malloc(strlen(molecule) - len + strlen(replacements[i].orig) + 1);
            strncpy(newmol, molecule, ptr - molecule);
            newmol[ptr-molecule] = '\0';
            strcat(newmol, replacements[i].orig);
            char *mlast = slice(molecule, ptr-molecule+len, strlen(molecule));
            strcat(newmol, mlast);
            min_steps = solve(newmol, replacements, steps + 1, min_steps);
            free(mlast);
            free(newmol);
            // Next ocurrence
            ptr = strstr(ptr+1, replacements[i].dest);
        }
    }
    return min_steps;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    // Advent of is there a greedy algorithm or good old DFS?
    char buffer[BUFFER_SIZE];
    char in[BUFFER_SIZE], out[BUFFER_SIZE];
    char molecule[BUFFER_SIZE];

    Replacement *replacements = NULL;

    while (fscanf(f, " %[^\n]\n", buffer) == 1) {
        if (buffer[0] == '\0') continue;
        if (sscanf(buffer, " %s => %s", in, out) == 2) {
            // printf("|%s|->|%s|\n", in, out);
            char *orig = malloc(strlen(in) + 1);
            strcpy(orig, in);
            char *dest = malloc(strlen(out) + 1);
            strcpy(dest, out);
            arrput(replacements, ((Replacement){orig, dest}));
        } else {
            sscanf(buffer, "%s", molecule);
        }
    }

    // Optimization: sort replacements by dest length
    qsort(replacements, arrlen(replacements), sizeof(Replacement), compare);
    // for (ptrdiff_t i = 0; i < arrlen(replacements); ++i) {
    //     printf("%s -> %s\n", replacements[i].orig, replacements[i].dest);
    // }
    // printf("<%s>\n", molecule);

    printf("%d\n", solve(molecule, replacements, 0, 1000000));

    return 0;
}
