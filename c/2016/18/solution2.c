#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLS 128

size_t countSafe(char *grid, size_t rows, size_t cols) {
    size_t ctr_safe = 0;
    for (size_t j = 0; j < cols; ++j) {
        if (grid[0 * MAX_COLS + j] == '.') ctr_safe++;
    }
    bool left, center, right;
    // Complete columns and count
    for (size_t i = 1; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (j == 0 || grid[(i - 1) * MAX_COLS + (j - 1)] == '.') left = false;
            else left = true;
            if (grid[(i - 1) * MAX_COLS + j] == '.') center = false;
            else center = true;
            if (j == cols - 1 || grid[(i-1) * MAX_COLS + (j + 1)] == '.') right = false;
            else right = true;
            // Safe or trap
            if ((left && center && !right) || (center && right && !left) ||
                (left && !center && !right) || (right && !center && !left)) {
                grid[i * MAX_COLS + j] = '^';
            } else {
                grid[i * MAX_COLS + j] = '.';
                ctr_safe++;
            }
        }
    }
    return ctr_safe;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution2.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    size_t rows = 10, cols = 0;
    if (strcmp(argv[1], "input") == 0) rows = 400000;
    // 2D fixed-column-size array of chars == 1D array with tricks to access it
    // We access grid[row][col] by doing grid[row * MAX_COLS + col]
    char *grid = malloc(rows * MAX_COLS * sizeof(char));

    while (fgets(grid, MAX_COLS, f) != NULL) {
        grid[0 * MAX_COLS + strcspn(grid, "\n")] = '\0';  // Remove trailing newline
        cols = strlen(grid);
    }
    fclose(f);

    printf("%zu\n", countSafe(grid, rows, cols));
    return 0;
}
