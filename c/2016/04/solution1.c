#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 64
#define ASCII_SIZE 256

int compare(const void* a, const void* b) {
    int32_t arg1 = *(const int32_t*)a;
    int32_t arg2 = *(const int32_t*)b;
    if (arg1 < arg2) return 1;
    if (arg1 > arg2) return -1;
    return 0;
}

bool isReal(char *name, char *checksum) {
    // Count letters in name
    int32_t counts[ASCII_SIZE];
    for (size_t i = 0; i<ASCII_SIZE; ++i) counts[i] = 0;
    for (size_t i = 0; i<strlen(name); ++i) counts[(int)name[i]]++;
    counts[(int)'-'] = 0;

    // Sort by popularity to check most common 5
    int32_t sorted_counts[ASCII_SIZE];
    memcpy(sorted_counts, counts, sizeof(counts));
    qsort(sorted_counts, ASCII_SIZE, sizeof(int32_t), compare);

    // Validate order
    if (strlen(checksum) != 5) return false;
    int32_t last_count = BUFFER_SIZE;
    for (size_t i = 0; i<strlen(checksum); ++i) {
        // If not the ith most common char
        if (counts[(int)checksum[i]] != sorted_counts[i]) return false;
        if ((counts[(int)checksum[i]] < last_count) ||
            (counts[(int)checksum[i]] == last_count && checksum[i-1] < checksum[i])) {
            last_count = counts[(int)checksum[i]];
        } else {
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    char name[BUFFER_SIZE];
    char checksum[BUFFER_SIZE];
    int32_t sector_id;
    int32_t sum = 0;

    while (fscanf(f, " %[^0-9]%d[%[^]]]", name, &sector_id, checksum) == 3) {
        name[strlen(name)-1] = '\0';  // Remove last dash from name
        if (isReal(name, checksum)) sum += sector_id;
    }
    fclose(f);

    printf("%d\n", sum);
    return 0;
}
