#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define STB_DS_IMPLEMENTATION
#include "../thirdparty/stb_ds.h"

uint32_t findHouse(uint32_t min_presents) {
    uint32_t house = 2;
    uint32_t presents;

    // Count elve's visited houses
    struct { uint32_t key; size_t value; } *elves = NULL;
    hmdefault(elves, 0);

    while (1) {
        presents = 0;
        for (uint32_t elve=1; (double)elve<=floor(sqrt((double)house)); ++elve) {
            if (house % elve == 0) {
                size_t delivered = hmget(elves, elve);
                if (delivered < 50) {
                    presents += 11 * elve;
                    hmput(elves, elve, delivered+1);
                }
                if (house / elve != elve) {
                    size_t delivered2 = hmget(elves, house / elve);
                    if (delivered2 < 50) {
                        presents += 11 * (house / elve);
                        hmput(elves, house / elve, delivered2 + 1);
                    }
                }
            }
        }
        if (presents >= min_presents) return house;
        house++;
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution2.out input

    // Advent of divisors
    uint32_t num;

    FILE *file = fopen(argv[1], "r");
    if (!file) return 1;

    while (fscanf(file, " %u", &num) == 1) {
        printf("%u\n", findHouse(num));
    }

    return 0;
}
