#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_COLS 256

size_t countSafe(char grid[][MAX_COLS], size_t rows, size_t cols) {
    size_t ctr_safe = 0;
    for (size_t j = 0; j < cols; ++j) {
        if (grid[0][j] == '.') ctr_safe++;
    }
    bool left, center, right;
    // Complete columns and count
    for (size_t i = 1; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (j == 0 || grid[i-1][j-1] == '.') left = false;
            else left = true;
            if (grid[i-1][j] == '.') center = false;
            else center = true;
            if (j == cols - 1 || grid[i-1][j+1] == '.') right = false;
            else right = true;
            // Safe or trap
            if ((left && center && !right) || (center && right && !left) ||
                (left && !center && !right) || (right && !center && !left)) {
                grid[i][j] = '^';
            } else {
                grid[i][j] = '.';
                ctr_safe++;
            }
        }
    }
    return ctr_safe;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    size_t rows = 10, cols = 0;
    if (strcmp(argv[1], "input") == 0) rows = 40;
    char grid[rows][MAX_COLS];

    while (fgets(grid[0], MAX_COLS, f) != NULL) {
        grid[0][strcspn(grid[0], "\n")] = '\0';  // Remove trailing newline
        cols = strlen(grid[0]);
    }
    fclose(f);

    printf("%zu\n", countSafe(grid, rows, cols));
    return 0;
}
