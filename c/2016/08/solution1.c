#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 256

void rotateRow(size_t width, bool screen[][width], size_t row, size_t by) {
    bool shifted[width];
    for (size_t j = 0; j < width; ++j) {
        shifted[(j+by)%width] = screen[row][j];
    }
    for (size_t j = 0; j < width; ++j) {
        screen[row][j] = shifted[j];
    }
    return;
}

void rotateCol(size_t height, size_t width, bool screen[][width], size_t col, size_t by) {
    bool shifted[height];
    for (size_t i = 0; i < height; ++i) {
        shifted[(i+by)%height] = screen[i][col];
    }
    for (size_t i = 0; i < height; ++i) {
        screen[i][col] = shifted[i];
    }
    return;
}

void drawRect(size_t width, bool screen[][width], size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            screen[i][j] = true;
        }
    }
    return;
}

// void display(size_t height, size_t width, bool screen[][width]) {
//     for (size_t i = 0; i < height; ++i) {
//         for (size_t j = 0; j < width; ++j) {
//             if (screen[i][j]) printf("#");
//             else printf(".");
//         }
//         printf("\n");
//     }
//     return;
// }

int32_t countPixels(size_t height, size_t width, bool screen[][width]) {
    int32_t ctr = 0;
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            if (screen[i][j]) ctr++;
        }
    }
    return ctr;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    // Define screen
    size_t height = 3, width = 7;
    if (strcmp(argv[1], "input") == 0) {
        height = 6;
        width = 50;
    }
    bool screen[height][width];
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            screen[i][j] = false;
        }
    }

    // Parse instructions
    char buffer[BUFFER_SIZE];
    size_t a, b;
    while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline
        if (strstr(buffer, "rect ")) {
            sscanf(buffer, "rect %zux%zu", &b, &a);
            drawRect(width, screen, a, b);
        } else if (strstr(buffer, "rotate column ")) {
            sscanf(buffer, "rotate column x=%zu by %zu", &a, &b);
            rotateCol(height, width, screen, a, b);
        } else if (strstr(buffer, "rotate row ")) {
            sscanf(buffer, "rotate row y=%zu by %zu", &a, &b);
            rotateRow(width, screen, a, b);
        } else {
            printf("I/O error: %s\n", buffer);
            return 1;
        }
        // display(height, width, screen);
        // printf("\n");
    }
    fclose(f);

    printf("%d\n", countPixels(height, width, screen));
    return 0;
}
