#include <cstddef>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define STB_DS_IMPLEMENTATION
#include "../thirdparty/stb_ds.h"

typedef struct {
    int32_t x;
    int32_t y;
} Position;

int32_t height = 6;
int32_t width = 11;

Position getNodePosition(char grid[][width], char node) {
    for (int32_t i = 0; i < height; ++ i) {
        for (int32_t j = 0; j < width; ++j) {
            if (grid[i][j] == node) return (Position){i, j};
        }
    }
    printf("node %c not found!", node);
    exit(1);
}

int32_t estimateDistance(char grid[][width], Position a, Position b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int32_t astar(char grid[][width], Position start, Position goal) {
    // https://en.wikipedia.org/wiki/A*_search_algorithm
    struct { Position key; _Bool value; } *open_set = NULL;
    hmput(open_set, start, 1);
    struct { Position key; int32_t value; } *g_score = NULL;
    hmdefault(g_score, INT32_MAX);
    hmput(g_score, start, 0);
    struct { Position key; int32_t value; } *f_score = NULL;
    hmdefault(f_score, INT32_MAX);
    hmput(f_score, start, estimateDistance(grid, start, goal));
    while (1) {
        if (hmlen(open_set) == 0) break;
        //         current := the node in open_set having the lowest f_score[] value
        int32_t lowest = INT32_MAX;
        Position current = {0, 0};
        for (ptrdiff_t i = 0; i < hmlen(f_score); ++i) {
            if (hmgeti(f_score,))
        }
    }
    return hmget(g_score, goal); // failure to find a path
}

int32_t minDistance(char grid[][width], char nodea, char nodeb) {
    Position a = getNodePosition(grid, nodea);
    Position b = getNodePosition(grid, nodeb);


}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    // advent of pathfinding
    // I'll do A* to find minimum distance from node A to node B
    // and DFS to pick best order of nodes from 0
    if (strcmp(argv[1], "input") == 0) height = 45, width = 177; 
    char grid[height][width];

    while (fscanf(f, "%d %d %d", &a, &b, &c) == 3) {
        if ((a + b) > c && (a + c) > b && (c + b) > a) count++;
    }
    fclose(f);

    printf("%d\n", count);
    return 0;
}
