#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 2048
#define RANGE_SIZE 22
// eg. 4294967294-4294967295\0

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int compare(const void* a, const void* b) {
    const char *str1 = (char *)a;
    const char *str2 = (char *)b;
    uint32_t range1_min, range1_max;
    uint32_t range2_min, range2_max;
    sscanf(str1, "%u-%u", &range1_min, &range1_max);
    sscanf(str2, "%u-%u", &range2_min, &range2_max);
    if (range1_min < range2_min) return -1;
    if (range1_min > range2_min) return 1;
    // range mins are the same, check range max
    if (range1_max < range2_max) return -1;
    if (range1_max > range2_max) return 1;
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution2.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    size_t ctr = 0;
    char ranges[BUFFER_SIZE][RANGE_SIZE];

    while (fscanf(f, " %s", ranges[ctr++]) == 1);
    fclose(f);

    // sort ranges
    qsort(ranges, ctr, RANGE_SIZE, compare);

    // convert to uint32
    uint32_t range_min[BUFFER_SIZE], range_max[BUFFER_SIZE];
    uint32_t max=0;
    for (size_t i = 0; i < ctr; ++i) {
        sscanf(ranges[i], "%u-%u", &range_min[i], &range_max[i]);
        if (range_max[i] > max) max = range_max[i];
    }
    uint32_t sum = 0;
    uint32_t current = 0;
    size_t idx = 0;

    // for the example use 9 instead of UINT32_MAX on lines 54 and 62
    while (current < UINT32_MAX) {
        if (current < range_min[idx]) sum += range_min[idx] - current;
        if (range_max[idx] == UINT32_MAX) break;
        current = MAX(current, range_max[idx] + 1);
        idx++;
    }
    // didn't happen with my input, but if input's absolute max is
    // lower than possible IP max, we need to count the last IPs
    if (max < UINT32_MAX) sum += UINT32_MAX - max;

    printf("%u\n", sum);
    return 0;
}
