#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    // Read whole file to a string
    char *buffer = 0;
    long length;
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length);
    if (buffer) {
        fread(buffer, 1, length, f);
    }
    fclose(f);

    // Divide string in tokens
    const int orientation[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int idx = 0;  // facing north
    int dist;
    int32_t x = 0;
    int32_t y = 0;
    const char *delimiter = ", ";
    char *token;
    token = strtok(buffer, delimiter);
    while (token != NULL) {
        if (token[0] == 'L') idx -= 1;
        else if (token[0] == 'R') idx += 1;
        if (idx < 0) idx += 4;
        if (idx >= 4) idx -= 4;
        dist = atoi(token + 1);
        // printf("%d (%d, %d) %d\n", dist, orientation[idx][0], orientation[idx][1], idx);
        x += orientation[idx][0] * dist;
        y += orientation[idx][1] * dist;
        // Subsequent calls to strtok() use NULL as the first argument
        // to continue parsing the same string
        token = strtok(NULL, delimiter);
    }

    printf("%d\n", abs(x) + abs(y));
    return 0;
}
