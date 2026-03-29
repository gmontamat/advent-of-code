#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 262144

void lookAndSay(char *current) {
    char next[BUFFER_SIZE];
    size_t idx_current = 0, idx_next = 0;
    while (idx_current < strlen(current)) {
        char current_digit = current[idx_current];
        size_t count = 1;
        for (size_t j=idx_current+1; j<strlen(current); ++j) {
            if (current[j] == current_digit) count++;
            else break;
        }
        idx_current += count;
        // Write next
        if (count == 1) {
            next[idx_next++] = '1';
        } else if (count == 2) {
            next[idx_next++] = '2';
        } else {
            next[idx_next++] = '3';
        }
        next[idx_next++] = current_digit;
    }
    next[idx_next] = '\0';
    strcpy(current, next);
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    char current[BUFFER_SIZE];

    if (fgets(current, BUFFER_SIZE, f) != NULL) {
        // printf("%s\n", current);
        for (size_t i=0; i<40; ++i) {
            lookAndSay(current);
            // printf("%d: %s\n", (int)i+1, current);
        }
    }

    printf("%d\n", (int)strlen(current));

    return 0;
}
