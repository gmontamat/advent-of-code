#include <stdio.h>
#include <stdint.h>
#include <math.h>

uint32_t findHouse(uint32_t min_presents) {
    uint32_t house = 2;
    uint32_t presents;
    while (1) {
        presents = 0;
        for (uint32_t elve=1; (double)elve<=floor(sqrt((double)house)); ++elve) {
            if (house % elve == 0) {
                presents += 10 * elve;
                if (house / elve != elve) presents += 10 * (house / elve);
            }
        }
        if (presents >= min_presents) return house;
        house++;
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    // Advent of divisors
    uint32_t num;

    FILE *file = fopen(argv[1], "r");
    if (!file) return 1;

    while (fscanf(file, " %u", &num) == 1) {
        printf("%u\n", findHouse(num));
    }

    return 0;
}
