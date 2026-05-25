#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
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
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    char password[BUFFER_SIZE] = "abcde";
    if (strcmp(argv[1], "input") == 0) strcpy(password, "abcdefgh");

    // advent of boring string manipulations
    char buffer[BUFFER_SIZE];
    size_t x, y;
    char xc, yc;
    int32_t steps;

    while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline
        if (strncmp(buffer, "swap position", 13) == 0) {
            sscanf(buffer, "swap position %zu with position %zu", &x, &y);
            swapPosition(password, x, y);
        } else if (strncmp(buffer, "swap letter", 11) == 0) {
            sscanf(buffer, "swap letter %c with letter %c", &xc, &yc);
            swapLetter(password, xc, yc);
        } else if (strncmp(buffer, "rotate based on position of letter", 34) == 0) {
            sscanf(buffer, "rotate based on position of letter %c", &xc);
            rotateBasedOnLetter(password, xc);
        } else if (strncmp(buffer, "rotate", 6) == 0) {
            if (strncmp(buffer, "rotate left", 11) == 0) {
                sscanf(buffer, "rotate left %d", &steps);
                rotate(password, true, steps);
            } else if (strncmp(buffer, "rotate right", 12) == 0) {
                sscanf(buffer, "rotate right %d", &steps);
                rotate(password, false, steps);
            } else {
                printf("I/O error: %s\n", buffer);
                return 1;
            }
        } else if (strncmp(buffer, "reverse positions", 17) == 0) {
            sscanf(buffer, "reverse positions %zu through %zu", &x, &y);
            reverse(password, x, y);
        } else if (strncmp(buffer, "move position", 13) == 0) {
            sscanf(buffer, "move position %zu to position %zu", &x, &y);
            move(password, x, y);
        } else {
            printf("I/O error: %s\n", buffer);
            return 1;
        }
        // printf("%s: %s\n", buffer, password);
    }
    fclose(f);

    printf("%s\n", password);
    return 0;
}
