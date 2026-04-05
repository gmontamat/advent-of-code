#include <stdint.h>
#include <stdio.h>

#define BUFFER_SIZE 32

int32_t computeDistance(int32_t fspeed, int32_t fsecs, int32_t rsecs, int32_t seconds) {
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
    }

    return distance;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    char raindeer[BUFFER_SIZE];
    int32_t seconds = 2503;
    int32_t fspeed, fsecs, rsecs;
    int32_t max_distance = 0;

    // Comet can fly 14 km/s for 10 seconds, but then must rest for 127 seconds.
    while (fscanf(f, "%s can fly %d km/s for %d seconds, but then must rest for %d seconds.",
                  raindeer, &fspeed, &fsecs, &rsecs) == 4) {
        // printf("%s -> ", buffer);

        int32_t distance = computeDistance(fspeed, fsecs, rsecs, seconds);
        if (distance > max_distance) max_distance = distance;
    }

    printf("%d\n", max_distance);

    return 0;
}
