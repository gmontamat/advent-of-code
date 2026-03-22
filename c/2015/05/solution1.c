#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

bool threeVowels(char *string) {
    int32_t count = 0;
    for (size_t i=0; i < strlen(string); ++i) {
        if (string[i] == 'a' || string[i] == 'e' || string[i] == 'i' ||
            string[i] == 'o' || string[i] == 'u') {
                count++;
        }
    }
    return count > 2;
}

bool twiceInARow(char *string) {
    for (size_t i=0; i < strlen(string) - 1; ++i) {
        if (string[i] == string[i+1]) {
            return true;
        }
    }
    return false;
}

bool noBannedStrings(char *string) {
    for (size_t i=0; i < strlen(string) - 1; ++i) {
        if ((string[i] == 'a' && string[i+1] == 'b') ||
            (string[i] == 'c' && string[i+1] == 'd') ||
            (string[i] == 'p' && string[i+1] == 'q') ||
            (string[i] == 'x' && string[i+1] == 'y')) {
                return false;
        }
    }
    return true;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    char buffer[BUFFER_SIZE];
    int32_t count = 0;

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline
        if (threeVowels(buffer) &&
            twiceInARow(buffer) &&
            noBannedStrings(buffer)) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}
