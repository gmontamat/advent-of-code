#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100
#define BUFFER_SIZE 128

void update(bool grid[][MAX_SIZE], int32_t size) {
    bool new_grid[MAX_SIZE][MAX_SIZE];

    for (int32_t i=0; i<size; ++i) {
        for (int32_t j=0; j<size; ++j) {
            // Count neighbors of each cell
            size_t neighbors = 0;

            if (i-1>=0 && j-1>=0 && grid[i-1][j-1]) neighbors++;
            if (i-1>=0 && grid[i-1][j]) neighbors++;
            if (i-1>=0 && j+1<size && grid[i-1][j+1]) neighbors++;

            if (j-1>=0 && grid[i][j-1]) neighbors++;
            if (j+1<size && grid[i][j+1]) neighbors++;
            
            if (i+1<size && j-1>=0 && grid[i+1][j-1]) neighbors++;
            if (i+1<size && grid[i+1][j]) neighbors++;
            if (i+1<size && j+1<size && grid[i+1][j+1]) neighbors++;

            // Update
            if (grid[i][j]) {
                if (neighbors == 2 || neighbors == 3) new_grid[i][j] = true;
                else new_grid[i][j] = false;
            } else {
                if (neighbors == 3) new_grid[i][j] = true;
                else new_grid[i][j] = false;
            }
        }
    }

    memcpy(grid, new_grid, sizeof(new_grid));
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    size_t steps = 4;
    if (strcmp(argv[1], "input") == 0) steps = 100;

    // Advent of Game of Life
    bool grid[MAX_SIZE][MAX_SIZE];
    char buffer[BUFFER_SIZE];

    int32_t row = 0;
    while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline

        for (size_t i=0; i<strlen(buffer); ++i) {
            if (buffer[i] == '#') grid[row][i] = true;
            else if (buffer[i] == '.') grid[row][i] = false;
            else {
                printf("Input error\n");
                return 1;
            }
        }

        row++;
    }

    // run Game of Life
    for (size_t i=0; i<steps; ++i) update(grid, row);

    // Count lights on
    size_t count = 0;
    for (int32_t i=0; i<row; ++i) {
        for (int32_t j=0; j<row; ++j) {
            if (grid[i][j]) count++;
        }
    }
    printf("%zu\n", count);

    return 0;
}
