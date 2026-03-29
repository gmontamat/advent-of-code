#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 262144
#define DIVIDE_SIZE 65536
#define DIVIDE_IDX  32768

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

size_t lenLookAndSay(char *string, size_t steps) {
    for (size_t i=0; i<steps; ++i) {
        // If the sequence is too long, split in 2
        if (strlen(string) > DIVIDE_SIZE) {
            for (size_t j=DIVIDE_IDX; j<BUFFER_SIZE; ++j) {
                // see https://www.youtube.com/watch?v=ea7lJkEhytA
                // Big problem here is WHERE to split sequence:
                // Find a string that ends with 2 (will always end in 2) and
                // Tin atom "13211" which should always start with 1 or 3
                if (string[j] == '2' && string[j+1] == '1' && string[j+2] == '3' &&
                    string[j+3] == '2' && string[j+4] == '1' && string[j+5] == '1') {
                    // Split at string[:j+1] and string[j+1:]
                    size_t left_len = j + 1;
                    size_t right_len = (size_t)strlen(string) - left_len;
                    char *lh = malloc(BUFFER_SIZE);
                    char *rh = malloc(BUFFER_SIZE);
                    strncpy(lh, string, left_len);
                    lh[left_len] = '\0';
                    strncpy(rh, string + left_len, right_len);
                    rh[right_len] = '\0';
                    // Recurse on each half with remaining steps
                    size_t length = 0;
                    length += lenLookAndSay(lh, steps - i);
                    length += lenLookAndSay(rh, steps - i);
                    free(lh);
                    free(rh);
                    return length;
                }
            }
        }
        // If not large enough, update in place
        lookAndSay(string);
    }
    return (size_t)strlen(string);
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution2.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    char input[BUFFER_SIZE];
    size_t size = 0;

    if (fgets(input, BUFFER_SIZE, f) != NULL) {
        // Divide(!) and conquer
        size = lenLookAndSay(input, 50);
    }

    printf("%ld\n", size);

    return 0;
}
