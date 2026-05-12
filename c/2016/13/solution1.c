#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 1024

bool isOpenSpace(int32_t fav, int32_t x, int32_t y) {
    int32_t num = x * x + 3 * x + 2 * x * y + y + y * y + fav;
    size_t ones = 0;
    while (num > 0) {
        if (num % 2 == 1) ones++;
        num = num >> 1;
    }
    return (ones % 2 == 0);
}

bool isBacktrack(int32_t x, int32_t y, int32_t *pathx, int32_t *pathy, int32_t steps) {
    for (size_t i = 0; i < (size_t)steps; ++i) {
        if (x == pathx[i] && y == pathy[i]) return true;
    }
    return false;
}

int32_t dfs(int32_t fav, int32_t x_goal, int32_t y_goal, int32_t *pathx, int32_t *pathy, int32_t steps, int32_t min_steps) {
    int32_t x = pathx[steps];
    int32_t y = pathy[steps];
    // Base case
    if (x == x_goal && y == y_goal) {
        if (steps < min_steps) return steps;
        else return min_steps;
    }
    // Prune
    if (steps > min_steps) return min_steps;
    // Recursion
    if (!isBacktrack(x + 1, y, pathx, pathy, steps) && isOpenSpace(fav, x + 1, y)) {
        pathx[steps + 1] = x + 1;
        pathy[steps + 1] = y;
        min_steps = dfs(fav, x_goal, y_goal, pathx, pathy, steps + 1, min_steps);
    }
    if (!isBacktrack(x, y + 1, pathx, pathy, steps) && isOpenSpace(fav, x, y + 1)) {
        pathx[steps + 1] = x;
        pathy[steps + 1] = y + 1;
        min_steps = dfs(fav, x_goal, y_goal, pathx, pathy, steps + 1, min_steps);
    }
    if (x - 1 >= 0 && !isBacktrack(x - 1, y, pathx, pathy, steps) && isOpenSpace(fav, x - 1, y)) {
        pathx[steps + 1] = x - 1;
        pathy[steps + 1] = y;
        min_steps = dfs(fav, x_goal, y_goal, pathx, pathy, steps + 1, min_steps);
    }
    if (y - 1 >= 0 && !isBacktrack(x, y - 1, pathx, pathy, steps) && isOpenSpace(fav, x, y - 1)) {
        pathx[steps + 1] = x;
        pathy[steps + 1] = y - 1;
        min_steps = dfs(fav, x_goal, y_goal, pathx, pathy, steps + 1, min_steps);
    }
    return min_steps;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    // Advent of pathfinding!
    // This one looks too simple for A*
    // we'll also build the map as we explore
    int32_t x_goal = 7, y_goal = 4;
    if (strcmp(argv[1], "input") == 0) {
        x_goal = 31;
        y_goal = 39;
    }
    int32_t pathx[BUFFER_SIZE], pathy[BUFFER_SIZE];
    pathx[0] = 1;
    pathy[0] = 1;
    int32_t fav;

    while (fscanf(f, "%d", &fav) == 1);
    fclose(f);

    printf("%d\n", dfs(fav, x_goal, y_goal, pathx, pathy, 0, BUFFER_SIZE));
    return 0;
}
