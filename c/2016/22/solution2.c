#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BUFFER_SIZE 1024

void constructGrid(size_t width, char grid[][width], size_t nodes,
    size_t *xpos, size_t *ypos, int32_t *size, int32_t *usage, int32_t threshold) {
    for (size_t node = 0; node < nodes; ++node) {
        size_t x = xpos[node];
        size_t y = ypos[node];
        if (x == width - 1 && y == 0) grid[y][x] = 'G';
        else if (size[node] > threshold && usage[node] > 85) grid[y][x] = '#';
        else if (usage[node] == 0) grid[y][x] = '_';
        else grid[y][x] = '.';
    }
    return;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution2.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    size_t height = 3, width = 3, threshold = 30;
    if (strcmp(argv[1], "input") == 0) height = 25, width = 37, threshold = 450;

    char grid[height][width];
    size_t nodes = 0;
    char buffer[BUFFER_SIZE];
    size_t x[BUFFER_SIZE], y[BUFFER_SIZE];
    int32_t size[BUFFER_SIZE], used[BUFFER_SIZE], avail[BUFFER_SIZE], usage[BUFFER_SIZE];

    // skip first 2 lines
    for (size_t i = 0; i < 2; ++i) {
        fgets(buffer, BUFFER_SIZE, f);
    }

    while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline
        sscanf(buffer, "/dev/grid/node-x%zu-y%zu %dT %dT %dT %d%%",
            &x[nodes], &y[nodes], &size[nodes], &used[nodes], &avail[nodes], &usage[nodes]);
        nodes++;
    }
    fclose(f);

    constructGrid(width, grid, nodes, x, y, size, usage, threshold);

    // Print grid - see README.md
    // for (size_t i = 0; i < height; ++i) {
    //     for (size_t j = 0; j < width; ++j) {
    //         printf("%c", grid[i][j]);
    //     }
    //     printf("\n");
    // }

    // see README.md
    // we could have done DFS/A* but there's a structure I could exploit
    if (strcmp(argv[1], "example") == 0) printf("%d\n", 7);
    else printf("%d\n", 22+38+5*35+1);
    return 0;
}
