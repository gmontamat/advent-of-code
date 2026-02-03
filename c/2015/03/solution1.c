#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Dynamic array (based on tsoding's std::vector)
typedef struct {
    int32_t x;
    int32_t y;
} Vector2;

typedef struct {
    Vector2 *items;
    size_t count;
    size_t capacity;
} Positions;

#define da_append(xs, x) \
    do { \
        if (xs.count >= xs.capacity) { \
            if (xs.capacity == 0) xs.capacity = 256; \
            else xs.capacity *= 2; \
            xs.items = realloc(xs.items, xs.capacity * sizeof(*xs.items)); \
        } \
        xs.items[xs.count++] = x; \
    } while (0)


int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    Positions visited = {0};
    Vector2 position = {0, 0};
    int32_t houses = 0;
    int move;

    while ((move = fgetc(f)) != EOF) {
        houses++;
        for (size_t i=0; i<visited.count; ++i) {
            if (visited.items[i].x == position.x && visited.items[i].y == position.y) {
                houses--;
                break;
            }
        }
        da_append(visited, position);
        switch (move) {
            case '>':
                position.x++;
                break;
            case '<':
                position.x--;
                break;
            case 'v':
                position.y--;
                break;
            case '^':
                position.y++;
                break;
            default:
                break;
        }
    }
    houses++;
    for (size_t i=0; i<visited.count; ++i) {
        if (visited.items[i].x == position.x && visited.items[i].y == position.y) {
            houses--;
            break;
        }
    }

    printf("%d\n", houses);
    return 0;
}
