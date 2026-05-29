#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define STB_DS_IMPLEMENTATION
#include "../thirdparty/stb_ds.h"

#define BUFFER_SIZE 256
#define INF 9999999

typedef struct {
    int32_t x;
    int32_t y;
} Position;

typedef struct {
    char a;
    char b;
} Pair;

int32_t height = 5;
int32_t width = 11;

struct { Pair key; int32_t value; } *memoization = NULL;

int32_t estimateDistance(Position a, Position b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

Position getNeighbor(Position current, size_t i) {
    Position neighbor = current;
    switch (i) {
        case 0:
            neighbor.x++;
            return neighbor;
        case 1:
            neighbor.x--;
            return neighbor;
        case 2:
            neighbor.y++;
            return neighbor;
        case 3:
            neighbor.y--;
            return neighbor;
    }
    return neighbor;
}

int32_t astar(char grid[][width], Position start, Position goal) {
    // https://en.wikipedia.org/wiki/A*_search_algorithm
    struct { Position key; _Bool value; } *open_set = NULL;  // slow, replace with priority queue
    hmdefault(open_set, 0);
    hmput(open_set, start, 1);
    struct { Position key; int32_t value; } *g_score = NULL;
    hmdefault(g_score, INF);
    hmput(g_score, start, 0);
    struct { Position key; int32_t value; } *f_score = NULL;
    hmdefault(f_score, INF);
    hmput(f_score, start, estimateDistance(start, goal));
    while (1) {
        if (hmlen(open_set) == 0) break;
        // current is the node in open_set having the lowest f_score[] value
        int32_t lowest = INF;
        Position current = {-1, -1};
        for (ptrdiff_t i = 0; i < hmlen(f_score); ++i) {
            if (hmget(open_set, f_score[i].key) == 0) continue;
            if (f_score[i].value < lowest) {
                lowest = f_score[i].value;
                current = f_score[i].key;
            }
        }
        // is it the goal?
        if (current.x == goal.x && current.y == goal.y) return hmget(g_score, goal);
        hmput(open_set, current, 0);
        for (size_t i = 0; i < 4; ++i) {
            Position neighbor = getNeighbor(current, i);
            if (neighbor.x >= 0 && neighbor.x < width &&
                    neighbor.y >= 0 && neighbor.y < height &&
                    grid[neighbor.y][neighbor.x] != '#') {
                int32_t tentative_g = hmget(g_score, current) + 1;
                if (tentative_g < hmget(g_score, neighbor)) {
                    hmput(g_score, neighbor, tentative_g);
                    hmput(f_score, neighbor, tentative_g + estimateDistance(neighbor, goal));
                    if (hmget(open_set, neighbor) == 0) hmput(open_set, neighbor, 1);
                }
            }
        }

    }
    return INT32_MAX; // failure to find a path
}

Position getNodePosition(char grid[][width], char node) {
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            if (grid[i][j] == node) return (Position){j, i};
        }
    }
    printf("node %c not found...\n", node);
    exit(1);
}

int32_t minDistance(char grid[][width], char nodea, char nodeb) {
    // memoize distance a->b
    Pair pair = {nodea, nodeb};
    if (hmgeti(memoization, pair) > -1) {
        return hmget(memoization, pair);
    }
    Position a = getNodePosition(grid, nodea);
    Position b = getNodePosition(grid, nodeb);
    int32_t distance = astar(grid, a, b);
    hmput(memoization, pair, distance);
    // Optimization: also memoize b->a
    pair.a = nodeb;
    pair.b = nodea;
    hmput(memoization, pair, distance);
    return distance;
}

int32_t dfs(char grid[][width], char *path, int32_t steps, int32_t min_steps, size_t visits) {
    // Base case
    // printf("|%s|\n", path);
    size_t len = strlen(path);
    if (len == visits) {
        if (steps < min_steps) {
            // printf("|%s| -> %d\n", path, steps);
            return steps;
        }
        else return min_steps;
    }
    // Prune
    if (steps >= min_steps) return min_steps;
    // Recursion
    for (size_t i = 1; i < visits; ++i) {
        // convert to char
        char next = '0' + i;
        // next in path?
        _Bool found = 0;
        for (size_t j = 1; j < len; ++j) {
            if (path[j] == next) {
                found = 1;
                break;
            }
        }
        if (found) continue;
        path[len] = next;
        path[len + 1] = '\0';
        int32_t distance = minDistance(grid, path[len-1], path[len]);
        min_steps = dfs(grid, path, steps + distance, min_steps, visits);
        path[len] = '\0';  // backtrack
    }
    return min_steps;
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
    char buffer[BUFFER_SIZE];
    size_t row = 0;

    while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline
        for (size_t i = 0; i < (size_t)width; ++i) {
            grid[row][i] = buffer[i];
        }
        row++;
    }
    fclose(f);

    size_t visits = 0;
    for (size_t i = 0; i < (size_t)height; ++i) {
        for (size_t j = 0; j < (size_t)width; ++j) {
            // printf("%c", grid[i][j]);
            if (grid[i][j] != '.' && grid[i][j] != '#') {
                visits++;
            }
        }
        //printf("\n");
    }
    char path[visits + 1];
    path[0] = '\0';
    strcat(path, "0");

    printf("%d\n", dfs(grid, path, 0, INT32_MAX, visits));
    return 0;
}
