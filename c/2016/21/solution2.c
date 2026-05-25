#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

void swapPosition(char *string, size_t x, size_t y) {
    char temp = string[x];
    string[x] = string[y];
    string[y] = temp;
}

void swapLetter(char *string, char letter1, char letter2) {
    for (size_t i = 0; i < strlen(string); ++i) {
        if (string[i] == letter1) string[i] = letter2;
        else if (string[i] == letter2) string[i] = letter1;
    }
}

void rotate(char *string, bool left, int32_t steps) {
    // how do I do it in-place?
    size_t len = strlen(string);
    char newstring[len + 1];
    if (steps == 0) return;
    if (left) steps *= -1;
    // proper modulo: int mod = ((a % b) + b) % b;
    for (size_t i = 0; i < len; ++i) {
        newstring[i] = string[(((int32_t)i - steps) % (int32_t)len + (int32_t)len) % (int32_t)len];
    }
    newstring[len] = '\0';
    memcpy(string, newstring, len + 1);
}

void rotateBasedOnLetter(char *string, char letter) {
    size_t idx = 0;
    size_t len = strlen(string);
    for (size_t i = 0; i < len; ++i) {
        if (string[i] == letter) {
            idx = i;
            break;
        }
    }
    rotate(string, false, 1);
    rotate(string, false, idx);
    if (idx >= 4) rotate(string, false, 1);
}

void rotateBasedOnLetterInv(char *string, char letter) {
    size_t len = strlen(string);
    char *temp = malloc(len + 1);
    // try all possible rotations, check which one fits
    for (size_t i = 0; i < len; ++i) {
        strcpy(temp, string);
        rotate(temp, true, i);
        rotateBasedOnLetter(temp, letter);
        if (strcmp(string, temp) == 0) {
            rotate(string, true, i);
            free(temp);
            return;
        }
    }
}

void reverse(char *string, size_t x, size_t y) {
    char temp;
    while (x < y) {
        temp = string[x];
        string[x] = string[y];
        string[y] = temp;
        x++;
        y--;
    }
}

void move(char *string, size_t x, size_t y) {
    char temp = string[x];
    if (x < y) {
        for (size_t i = x; i < y; ++i) {
            string[i] = string[i+1];
        }
    } else {
        for (size_t i = x; i > y; --i) {
            string[i] = string[i-1];
        }
    }
    string[y] = temp;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution2.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    char password[BUFFER_SIZE] = "abcde";
    if (strcmp(argv[1], "input") == 0) strcpy(password, "fbgdceah");

    // advent of boring string manipulations
    size_t i = 0;
    char buffer[BUFFER_SIZE][BUFFER_SIZE];
    size_t x, y;
    char xc, yc;
    int32_t steps;

    while (fgets(buffer[i], BUFFER_SIZE, f) != NULL) {
        buffer[i][strcspn(buffer[i], "\n")] = '\0';  // Remove trailing newline
        i++;
    }

    for (int j = i-1; j >= 0; --j) {
        if (strncmp(buffer[j], "swap position", 13) == 0) {
            sscanf(buffer[j], "swap position %zu with position %zu", &x, &y);
            swapPosition(password, x, y);  // self-symmetric operation, no changes
        } else if (strncmp(buffer[j], "swap letter", 11) == 0) {
            sscanf(buffer[j], "swap letter %c with letter %c", &xc, &yc);
            swapLetter(password, xc, yc);  // self-symmetric operation, no changes
        } else if (strncmp(buffer[j], "rotate based on position of letter", 34) == 0) {
            sscanf(buffer[j], "rotate based on position of letter %c", &xc);
            rotateBasedOnLetterInv(password, xc);  // custom inverse function
        } else if (strncmp(buffer[j], "rotate", 6) == 0) {
            if (strncmp(buffer[j], "rotate left", 11) == 0) {
                sscanf(buffer[j], "rotate left %d", &steps);
                rotate(password, false, steps);  // swapped left and right, rotate the other way round
            } else if (strncmp(buffer[j], "rotate right", 12) == 0) {
                sscanf(buffer[j], "rotate right %d", &steps);
                rotate(password, true, steps);  // swapped left and right, rotate the other way round
            } else {
                printf("I/O error: %s\n", buffer[j]);
                return 1;
            }
        } else if (strncmp(buffer[j], "reverse positions", 17) == 0) {
            sscanf(buffer[j], "reverse positions %zu through %zu", &x, &y);
            reverse(password, x, y);  // self-symmetric operation, no changes
        } else if (strncmp(buffer[j], "move position", 13) == 0) {
            sscanf(buffer[j], "move position %zu to position %zu", &x, &y);
            move(password, y, x);  // swapped x with y
        } else {
            printf("I/O error: %s\n", buffer[j]);
            return 1;
        }
        // printf("%s: %s\n", buffer[j], password);
    }
    fclose(f);

    printf("%s\n", password);
    return 0;
}
