#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BUFFER_SIZE 32

int32_t simulate_tosses(size_t discs, int32_t *positions, int32_t *initial) {
    size_t press_time = 0;  // tracks time at which we press
    int32_t capsule = 1;    // tracks if we got the capsule
    int32_t current[BUFFER_SIZE];
    while (1) {
        capsule = 1;
        memcpy(current, initial, sizeof(*initial) * BUFFER_SIZE);
        for (size_t i = 0; i < discs; ++i) {
            // Disc rotation before press
            current[i] = (current[i] + press_time) % positions[i];
        }
        // printf("Pressed at time=%zu\n", press_time);
        for (size_t i = 0; i < discs; ++i) {
            // Rotate all discs for 1 second
            for (size_t j = 0; j < discs; ++j) {
                current[j] = (current[j] + 1) % positions[j];
            }
            // printf("time=%zu; disk=%zu; slot=%d\n", press_time + 1 + i, i + 1, current[i]);
            // Check if we hit slot on current disc
            if (current[i] > 0) {
                capsule = 0;
                break;
            }
        }
        if (capsule) return (int32_t)press_time;
        press_time++;
    }
    return -1;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    size_t disc = 0;
    int32_t positions[BUFFER_SIZE], initial[BUFFER_SIZE];
    size_t discs;

    while (fscanf(f, " Disc #%zu has %d positions; at time=0, it is at position %d.",
                  &discs, &positions[disc], &initial[disc]) == 3) {
        disc++;
    }
    fclose(f);

    printf("%d\n", simulate_tosses(discs, positions, initial));
    return 0;
}
