#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

int32_t allx[BUFFER_SIZE], ally[BUFFER_SIZE];
size_t ctr = 0;

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

void dfs(int32_t fav, int32_t *pathx, int32_t *pathy, int32_t steps, int32_t max_steps) {
    int32_t x = pathx[steps];
    int32_t y = pathy[steps];
    bool found = false;
    for (size_t i = 0; i < ctr; ++i) {
        if (x == allx[i] && y == ally[i]) {
            found = true;
            break;
        }
    }
    if (!found) {
        allx[ctr] = x;
        ally[ctr] = y;
        ctr++;
    }
    if (steps == max_steps) return;
    // Recursion
    if (!isBacktrack(x + 1, y, pathx, pathy, steps) && isOpenSpace(fav, x + 1, y)) {
        pathx[steps + 1] = x + 1;
        pathy[steps + 1] = y;
        dfs(fav, pathx, pathy, steps + 1, max_steps);
    }
    if (!isBacktrack(x, y + 1, pathx, pathy, steps) && isOpenSpace(fav, x, y + 1)) {
        pathx[steps + 1] = x;
        pathy[steps + 1] = y + 1;
        dfs(fav, pathx, pathy, steps + 1, max_steps);
    }
    if (x - 1 >= 0 && !isBacktrack(x - 1, y, pathx, pathy, steps) && isOpenSpace(fav, x - 1, y)) {
        pathx[steps + 1] = x - 1;
        pathy[steps + 1] = y;
        dfs(fav, pathx, pathy, steps + 1, max_steps);
    }
    if (y - 1 >= 0 && !isBacktrack(x, y - 1, pathx, pathy, steps) && isOpenSpace(fav, x, y - 1)) {
        pathx[steps + 1] = x;
        pathy[steps + 1] = y - 1;
        dfs(fav, pathx, pathy, steps + 1, max_steps);
    }
    return;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution2.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    // Advent of pathfinding!
    int32_t pathx[BUFFER_SIZE], pathy[BUFFER_SIZE];
    pathx[0] = 1;
    pathy[0] = 1;
    int32_t fav;

    while (fscanf(f, "%d", &fav) == 1);
    fclose(f);

    dfs(fav, pathx, pathy, 0, 50);
    printf("%zu\n", ctr);
    return 0;
}
