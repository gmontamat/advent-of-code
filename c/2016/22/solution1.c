#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BUFFER_SIZE 1024

int32_t countViablePairs(size_t nodes, int32_t *used, int32_t *avail) {
    int32_t count = 0;
    for (size_t i = 0; i < nodes; ++i) {
        for (size_t j = 0; j<nodes; ++j) {
            if (used[i] > 0 && i != j && used[i] <= avail[j]) {
                count++;
            }
        }
    }
    return count;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    size_t nodes = 0;
    char buffer[BUFFER_SIZE];
    char name[BUFFER_SIZE][32];
    int32_t size[BUFFER_SIZE], used[BUFFER_SIZE], avail[BUFFER_SIZE], usage[BUFFER_SIZE];

    // skip first 2 lines
    for (size_t i = 0; i < 2; ++i) {
        fgets(buffer, BUFFER_SIZE, f);
    }

    while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline
        sscanf(buffer, "/dev/grid/%s %dT %dT %dT %d%%", name[nodes], &size[nodes], &used[nodes], &avail[nodes], &usage[nodes]);
        nodes++;
    }
    fclose(f);

    printf("%d\n", countViablePairs(nodes, used, avail));
    return 0;
}
