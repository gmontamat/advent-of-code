#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

bool pairTwice(char *string) {
    char pair1, pair2;
    for (size_t i=0; i < strlen(string) - 3; ++i) {
        pair1 = string[i];
        pair2 = string[i+1];
        for (size_t j=i+2; j < strlen(string) - 1; ++j) {
            if (string[j] == pair1 && string[j+1] == pair2) {
                return true;
            }
        }
    }
    return false;
}

bool repeatLetterWithOneBetween(char *string) {
    for (size_t i=0; i < strlen(string) - 2; ++i) {
        if (string[i] == string[i+2]) return true;
    }
    return false;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution2.out input

    char buffer[BUFFER_SIZE];
    int32_t count = 0;

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline
        if (pairTwice(buffer) && repeatLetterWithOneBetween(buffer)) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}
