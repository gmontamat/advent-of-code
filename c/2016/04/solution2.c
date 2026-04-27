#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 64

bool decipher(char *name, int32_t sector_id) {
    char deciphered[strlen(name)];

    for (size_t i=0; i<strlen(name); ++i) {
        if (name[i] == '-') deciphered[i] = ' ';
        else deciphered[i] = 97 + ((int)name[i] - 97 + sector_id) % 26;
    }
    deciphered[strlen(name)] = '\0';

    if (strcmp(deciphered, "northpole object storage") == 0) {
        printf("%d\n", sector_id);
        return true;
    }

    return false;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    char name[BUFFER_SIZE];
    char checksum[BUFFER_SIZE];
    int32_t sector_id;

    while (fscanf(f, " %[^0-9]%d[%[^]]]", name, &sector_id, checksum) == 3) {
        name[strlen(name)-1] = '\0';  // Remove last dash from name
        if (decipher(name, sector_id)) {
            fclose(f);
            return 0;
        }
    }

    fclose(f);
    printf("northpole object storage not found!\n");

    return 0;
}
