#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 131072
#define MARKER_SIZE 32

char *decompress(char *string) {
    char *decompressed = malloc(BUFFER_SIZE);
    char marker[MARKER_SIZE];
    size_t k = 0;
    size_t size, times;

    for (size_t i = 0; i < strlen(string); ++i) {
        if (string[i] != '(') {
            decompressed[k++] = string[i];
            continue;
        }
        // Handle markers (SIZExTIMES)
        size_t j = 0;
        while (string[i] != ')') marker[j++] = string[i++];
        marker[j] = string[i];  // string[i] -> ')'
        marker[++j] = '\0';
        sscanf(marker, "(%zux%zu)", &size, &times);
        char repeat[size + 1];
        for (size_t n = 0; n < size; ++n) {
            repeat[n] = string[i + n + 1];
        }
        repeat[size] = '\0';
        decompressed[k] = '\0';
        for (size_t n = 0; n < times; ++n) {
            strcat(decompressed, repeat);
            k += size;
        }
        i += size;
    }
    decompressed[k] = '\0';
    return decompressed;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    int32_t len = 0;
    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline
        char *decompressed = decompress(buffer);
        // printf("%s\n", decompressed);
        len += strlen(decompressed);
        free(decompressed);
    }
    fclose(f);

    printf("%d\n", len);
    return 0;
}
