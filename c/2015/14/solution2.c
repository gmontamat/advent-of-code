#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define BUFFER_SIZE 32
#define SECONDS 2503

void computeDistances(int32_t *distances, int32_t fspeed, int32_t fsecs, int32_t rsecs, int32_t seconds) {
    int32_t distance = 0;
    int32_t ftime = 0;  // flying time
    int32_t rtime = 0;  // resting time

    for (int32_t i=0; i<seconds; ++i) {
        if (ftime < fsecs) {
            rtime = 0;
            ftime++;
            distance += fspeed;
        } else if (rtime < rsecs) {
            rtime++;
        }
        if (rtime == rsecs) {
            ftime = 0;
        }
        distances[i] = distance;
    }
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution2.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    char raindeer[BUFFER_SIZE];
    int32_t seconds = SECONDS;
    int32_t fspeed, fsecs, rsecs;
    int32_t raindeer_distances[BUFFER_SIZE][SECONDS];
    int32_t scores[SECONDS];
    size_t i = 0;

    // Comet can fly 14 km/s for 10 seconds, but then must rest for 127 seconds.
    while (fscanf(f, "%s can fly %d km/s for %d seconds, but then must rest for %d seconds.",
                  raindeer, &fspeed, &fsecs, &rsecs) == 4) {
        // printf("%s -> ", buffer);

        scores[i] = 0;
        computeDistances(raindeer_distances[i], fspeed, fsecs, rsecs, seconds);
        i++;
    }

    for (size_t t=0; t<SECONDS; ++t) {
        int32_t max_distance = 0;
        for (size_t j=0; j<i; ++j) {
            if (raindeer_distances[j][t] > max_distance) max_distance = raindeer_distances[j][t];
        }
        for (size_t j=0; j<i; ++j) {
            if (raindeer_distances[j][t] == max_distance) scores[j]++;
        }
    }

    int32_t max_score = 0;
    for (size_t j=0; j<i; ++j) {
        if (scores[j] > max_score) max_score = scores[j];
    }

    printf("%d\n", max_score);

    return 0;
}
