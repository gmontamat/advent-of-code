#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 16
#define CHAR_SIZE 

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    size_t n = 6;
    if (strcmp(argv[1], "input") == 0) n = 8;

    int32_t ctr[n][26];
    char buffer[BUFFER_SIZE];
    char output[BUFFER_SIZE];

    // Initialize counters
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < 26; ++j) {
            ctr[i][j] = 0;
        }
    }

    // Count frequencies
    while (fscanf(f, "%s", buffer) == 1) {
        for (size_t i = 0; i < n; ++i) {
            ctr[i][(int)buffer[i] - 97]++;
        }
    }
    fclose(f);

    // Recover word
    for (size_t i = 0; i < n; ++i) {
        char letter = 'a';
        int32_t min = INT32_MAX;
        for (size_t j = 0; j < 26; ++j) {
            if (ctr[i][j] == 0) continue;
            if (ctr[i][j] < min) {
                min = ctr[i][j];
                letter = 'a' + j;
            }
        }
        output[i] = letter;
    }
    output[n] = '\0';

    printf("%s\n", output);
    return 0;
}
