#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256
#define GRID_HEIGHT 1000
#define GRID_WIDTH 1000

void toggle(bool grid[][GRID_WIDTH], int32_t xMin, int32_t yMin, int32_t xMax, int32_t yMax) {
    for (int32_t i=yMin; i<=yMax; ++i) {
        for (int32_t j=xMin; j<=xMax; ++j) {
            grid[i][j] = !grid[i][j];
        }
    }
}

void turnOn(bool grid[][GRID_WIDTH], int32_t xMin, int32_t yMin, int32_t xMax, int32_t yMax) {
    for (int32_t i=yMin; i<=yMax; ++i) {
        for (int32_t j=xMin; j<=xMax; ++j) {
            grid[i][j] = true;
        }
    }
}

void turnOff(bool grid[][GRID_WIDTH], int32_t xMin, int32_t yMin, int32_t xMax, int32_t yMax) {
    for (int32_t i=yMin; i<=yMax; ++i) {
        for (int32_t j=xMin; j<=xMax; ++j) {
            grid[i][j] = false;
        }
    }
}

int countOn(bool grid[][GRID_WIDTH]) {
    int32_t count = 0;
    for (size_t i=0; i<GRID_HEIGHT; ++i) {
        for (size_t j=0; j<GRID_WIDTH; ++j) {
            if (grid[i][j]) count++;
        }
    }
    return count;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    char buffer[BUFFER_SIZE];
    int32_t xMin, yMin, xMax, yMax;

    // Initialize grid
    bool grid[GRID_HEIGHT][GRID_WIDTH];
    for (size_t i=0; i < GRID_HEIGHT; ++i) {
        for (size_t j=0; j < GRID_WIDTH; ++j) {
            grid[i][j] = false;
        }
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline

        if (strncmp(buffer, "turn on", 7) == 0) {
            sscanf(buffer, "turn on %d,%d through %d,%d", &xMin, &yMin, &xMax, &yMax);
            turnOn(grid, xMin, yMin, xMax, yMax);
        } else if (strncmp(buffer, "turn off", 8) == 0) {
            sscanf(buffer, "turn off %d,%d through %d,%d", &xMin, &yMin, &xMax, &yMax);
            turnOff(grid, xMin, yMin, xMax, yMax);
        } else if (strncmp(buffer, "toggle", 6) == 0) {
            sscanf(buffer, "toggle %d,%d through %d,%d", &xMin, &yMin, &xMax, &yMax);
            toggle(grid, xMin, yMin, xMax, yMax);
        } else {
            printf("Unknown command: %s\n", buffer);
            continue;
        }
    }

    printf("%d\n", countOn(grid));
    return 0;
}
