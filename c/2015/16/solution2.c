#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define STB_DS_IMPLEMENTATION
#include "../thirdparty/stb_ds.h"

#define BUFFER_SIZE 32

typedef struct {
    char *key;
    int32_t value;
} HashTable;

bool shmatch2(HashTable *suedata, char *key, int32_t value) {
    if (strcmp(key, "cats") == 0 || strcmp(key, "trees") == 0) {
        if (suedata[shgeti(suedata, key)].value < value) return true;
        else return false;
    } else if (strcmp(key, "pomeranians") == 0 || strcmp(key, "goldfish") == 0) {
        if (suedata[shgeti(suedata, key)].value > value) return true;
        else return false;
    } else {
        if (suedata[shgeti(suedata, key)].value == value) return true;
        else return false;
    }
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution2.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    HashTable *realsue = NULL;

    shput(realsue, "children", 3);
    shput(realsue, "cats", 7);
    shput(realsue, "samoyeds", 2);
    shput(realsue, "pomeranians", 3);
    shput(realsue, "akitas", 0);
    shput(realsue, "vizslas", 0);
    shput(realsue, "goldfish", 5);
    shput(realsue, "trees", 3);
    shput(realsue, "cars", 2);
    shput(realsue, "perfumes", 1);

    char item[3][BUFFER_SIZE];
    int32_t sue, quantity[3];

    // Sue 1: children: 1, cars: 8, vizslas: 7
    while (fscanf(f, " Sue %d: %[^:]: %d, %[^:]: %d, %[^:]: %d",
                  &sue, item[0], &quantity[0], item[1], &quantity[1], item[2], &quantity[2]) == 7) {
        int32_t matches = 0;
        for (size_t i=0; i<3; ++i) {
            if (shmatch2(realsue, item[i], quantity[i])) matches++;
        }
        if (matches==3) printf("%d\n", sue);
    }

    return 0;
}
