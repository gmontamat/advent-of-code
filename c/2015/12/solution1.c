#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define BUFFER_SIZE 32768
#define NUM_SIZE 32

int32_t sumNumbers(char *string) {
    int32_t sum = 0;

    const char* pattern = "-?[0-9]+"; 
    regex_t regex;
    regmatch_t match;
    const char *cursor = string;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return 1;
    }

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        int start = (int)match.rm_so;
        int end = (int)match.rm_eo;

        char match_str[end - start + 1];
        snprintf(match_str, end - start + 1, "%.*s", end - start, cursor + start);
        char *endptr;
        int32_t num = strtol(match_str, &endptr, 10);
        sum += num;

        cursor += end;
    }

    regfree(&regex);

    return sum;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline

        // printf("%s -> ", buffer);
        int32_t sum = sumNumbers(buffer);
        printf("%d\n", sum);
    }

    return 0;
}
