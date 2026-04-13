#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 512

#define STB_DS_IMPLEMENTATION
#include "../thirdparty/stb_ds.h"

typedef struct {
    char *orig;
    char *dest;
} Replacement;

char* slice(const char *str, size_t start, size_t end) {
    size_t len = end - start;
    char *result = malloc(len + 1);
    strncpy(result, str + start, len);
    result[len] = '\0';
    return result;  // Remember to free()
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    // Advent of Hash Sets
    char buffer[BUFFER_SIZE];
    char in[BUFFER_SIZE], out[BUFFER_SIZE];
    char molecule[BUFFER_SIZE];

    Replacement *replacements = NULL;
    struct { char *key; _Bool value; } *hashset = NULL;

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

    // for (ptrdiff_t i = 0; i < arrlen(replacements); ++i) {
    //     printf("%s -> %s\n", replacements[i].orig, replacements[i].dest);
    // }
    // printf("<%s>\n", molecule);

    for (size_t i = 0; i < strlen(molecule); ++i) {
        size_t maxlen = strlen(molecule) - i;
        for (ptrdiff_t j = 0; j < arrlen(replacements); ++j) {
            size_t len = strlen(replacements[j].orig);
            if (len > maxlen) continue;
            char *mmid = slice(molecule, i, i + len);
            if (strcmp(mmid, replacements[j].orig) == 0) {
                // Ugly, but string manipulation in C is a lost cause
                char *newmol = malloc(strlen(molecule) + strlen(replacements[j].dest) - len + 1);
                strncpy(newmol, molecule, i);
                newmol[i] = '\0';
                strcat(newmol, replacements[j].dest);
                char *mlast = slice(molecule, i+len, strlen(molecule));
                strcat(newmol, mlast);
                shput(hashset, newmol, 1);
                free(mlast);
            }
            free(mmid);
        }
    }

    printf("%zu\n", shlen(hashset));

    return 0;
}
