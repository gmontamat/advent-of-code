#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateData(char *data, size_t disk_size) {
    if (strlen(data) >= disk_size) {
        data[disk_size] = '\0';
        return;
    }
    // We need to generate more data
    size_t len = strlen(data);
    char *b = malloc(len + 1);
    char aux;
    memcpy(b, data, len + 1);
    // Reverse b
    for (size_t i = 0; i < len / 2; ++i) {
        aux = b[i];
        b[i] = b[len - i - 1];
        b[len - i - 1] = aux;
    }
    // Swap 0s and 1s in b
    for (size_t i = 0; i < len; ++i) {
        if (b[i] == '0') b[i] = '1';
        else b[i] = '0'; 
    }
    // append 0 + "b" to a
    strcat(data, "0");
    strcat(data, b);
    free(b);
    generateData(data, disk_size);
}

void computeChecksum(char *checksum) {
    size_t len = strlen(checksum), ctr = 0;
    if (len % 2 == 1) return;
    char *newchecksum = malloc(len / 2 + 1);
    for (size_t i = 0; i < len - 1; i+=2) {
        if (checksum[i] == checksum[i+1]) newchecksum[ctr++] = '1';
        else newchecksum[ctr++] = '0';
    }
    newchecksum[ctr] = '\0';
    memcpy(checksum, newchecksum, ctr + 1);
    free(newchecksum);
    computeChecksum(checksum);
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution2.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    size_t disk_size = 20, ctr = 0;
    if (strcmp(argv[1], "input") == 0) disk_size = 35651584;

    // We don't have all that space in the stack
    // but we can use the heap
    char *data = malloc(disk_size * 2 + 1);
    char *checksum = malloc(disk_size);

    while (fgets(data, disk_size * 2 + 1, f) != NULL) {
        data[strcspn(data, "\n")] = '\0';  // Remove trailing newline
    }
    fclose(f);

    generateData(data, disk_size);
    // first checksum iteration
    for (size_t i = 0; i < disk_size - 1; i+=2) {
        if (data[i] == data[i+1]) checksum[ctr++] = '1';
        else checksum[ctr++] = '0';
    }
    checksum[ctr] = '\0';
    computeChecksum(checksum);
    printf("%s\n", checksum);
    return 0;
}
