#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Dynamic array (based on tsoding's std::vector)
typedef struct {
    int32_t x;
    int32_t y;
} Location;

typedef struct {
    Location *items;
    size_t count;
    size_t capacity;
} Locations;

#define da_append(xs, ...) \
    do { \
        if (xs.count >= xs.capacity) { \
            if (xs.capacity == 0) xs.capacity = 256; \
            else xs.capacity *= 2; \
            xs.items = realloc(xs.items, xs.capacity * sizeof(*xs.items)); \
        } \
        xs.items[xs.count++] = (__VA_ARGS__); \
    } while (0)

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    // Read whole file to a string
    char *buffer = 0;
    long length;
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length);
    if (buffer) fread(buffer, 1, length, f);
    fclose(f);

    const int orientation[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int idx = 0;  // facing north
    int dist;
    int32_t x = 0;
    int32_t y = 0;
    Locations locations = {0};
    const char *delimiter = ", ";
    char *token;
    token = strtok(buffer, delimiter);
    da_append(locations, (Location){x, y});
    while (token != NULL) {
        if (token[0] == 'L') idx -= 1;
        else if (token[0] == 'R') idx += 1;
        if (idx < 0) idx += 4;
        if (idx >= 4) idx -= 4;
        dist = atoi(token + 1);
        // printf("%d (%d, %d) %d\n", dist, orientation[idx][0], orientation[idx][1], idx);
        for (int i = 0; i < dist; ++i) {
            x += orientation[idx][0];
            y += orientation[idx][1];
            // printf("(%d, %d)\n", x, y);
            // Check if current x, y in locations
            for (size_t j = 0; j < locations.count; ++j) {
                if (locations.items[j].x == x && locations.items[j].y == y) {
                    printf("%d\n", abs(x) + abs(y));
                    return 0;
                }
            }
            da_append(locations, (Location){x, y});
        }
        // Subsequent calls to strtok() use NULL as the first argument
        // to continue parsing the same string
        token = strtok(NULL, delimiter);
    }

    printf("No location met twice.\n");
    for (size_t j = 0; j < locations.count; ++j) {
        printf("(%d, %d)\n", locations.items[j].x, locations.items[j].y);
    }
    return 0;
}
