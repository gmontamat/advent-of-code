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
    if (argc < 2) return 1;  // usage ./solution2.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    Positions visited = {0};
    Vector2 santa = {0, 0};
    Vector2 robot = {0, 0};
    _Bool santas_turn = 1;
    int32_t houses = 1;
    int move;

    da_append(visited, santa);
    while ((move = fgetc(f)) != EOF) {
        switch (move) {
            case '>':
                if (santas_turn) santa.x++;
                else robot.x++;
                break;
            case '<':
                if (santas_turn) santa.x--;
                else robot.x--;
                break;
            case 'v':
                if (santas_turn) santa.y--;
                else robot.y--;
                break;
            case '^':
                if (santas_turn) santa.y++;
                else robot.y++;
                break;
            default:
                break;
        }
        if (santas_turn) {
            _Bool found = 0;
            for (size_t i=0; i<visited.count; ++i) {
                if (visited.items[i].x == santa.x && visited.items[i].y == santa.y) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                houses++;
                da_append(visited, santa);
            }
            santas_turn = 0;
        } else {
            _Bool found = 0;
            for (size_t i=0; i<visited.count; ++i) {
                if (visited.items[i].x == robot.x && visited.items[i].y == robot.y) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                houses++;
                da_append(visited, robot);
            }
            santas_turn = 1;
        }
    }

    printf("%d\n", houses);
    return 0;
}
