#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 16384
#define MARKER_SIZE 16

uint64_t decompress(char *string) {
    uint64_t total = 0;
    size_t size, times;

    for (size_t i = 0; i < strlen(string); ++i) {
        if (string[i] != '(') {
            total++;
            continue;
        }
        // Handle markers
        size_t j = 0;
        char marker[MARKER_SIZE];
        while (string[i] != ')') marker[j++] = string[i++];
        marker[j] = string[i];  // string[i] -> ')'
        marker[++j] = '\0';
        sscanf(marker, "(%zux%zu)", &size, &times);
        char repeat[size + 1];
        for (size_t j = 0; j < size; ++j) {
            repeat[j] = string[i + j + 1];
        }
        repeat[size] = '\0';
        // printf("%s\n", repeat);
        total += times * decompress(repeat);
        i += size;
    }
    return total;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution2.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    uint64_t len = 0;
    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline
        len += decompress(buffer);
    }
    fclose(f);

    printf("%lu\n", len);
    return 0;
}
