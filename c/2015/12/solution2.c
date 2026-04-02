#include <stddef.h>
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

int32_t sumObject(char *string) {
    int32_t sum;

    const char* pattern = ":\"red\"";  // check if "red" is a value in object
    regex_t regex;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return 1;
    }

    if (!regexec(&regex, string, 0, NULL, 0)) {
        // printf("Match: %s\n", string);
        sum = 0;
    } else {
        // If no red value
        sum = sumNumbers(string);
    }

    regfree(&regex);

    return sum;
}

int32_t sumNonRedObjects(char *string) {
    int32_t sum;

    char reduced_string[BUFFER_SIZE];  // here we copy the string without the innermost objects
    size_t last_idx = 0;

    const char* pattern = "\\{[^{}]*\\}";  // only matches innermost objects
    regex_t regex;
    regmatch_t match;
    const char *cursor = string;
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return 1;
    }

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        int start = (int)match.rm_so;
        int end = (int)match.rm_eo;

        //printf("Match: %.*s\n", (end - start), cursor + start);

        // Build original string up to start
        for (size_t i=0; i<(size_t)start; ++i) {
            reduced_string[last_idx++] = cursor[i];
        }

        // Sum numbers in the innermost object or 0 when red
        char match_str[end - start + 1];
        snprintf(match_str, end - start + 1, "%.*s", end - start, cursor + start);
        int32_t inner_sum = sumObject(match_str);

        // Replace innermost object with "inner_sum"
        char inner_number[NUM_SIZE];
        sprintf(inner_number, "%d", inner_sum);
        reduced_string[last_idx++] = '"';
        for (size_t i=0; i<(size_t)strlen(inner_number); ++i) {
            reduced_string[last_idx++] = inner_number[i];
        }
        reduced_string[last_idx++] = '"';

        cursor += end;
    }
    size_t i = 0;
    while (cursor[i] != '\0') {
        reduced_string[last_idx++] = cursor[i++];
    }
    reduced_string[last_idx] = '\0';

    regfree(&regex);

    // Call again without the inner matches (to avoid complex regexes or proper JSON parsing)
    if (strcmp(string, reduced_string) != 0) {
        sum = sumNonRedObjects(reduced_string);
    } else {
        // Base case - no more matches
        sum = sumNumbers(reduced_string);
    }

    return sum;
}

int main(int argc, char **argv) {
    // Advent of regex
    if (argc < 2) return 1;  // usage ./solution2.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline

        // printf("%s -> ", buffer);
        int32_t sum = sumNonRedObjects(buffer);
        printf("%d\n", sum);
    }

    return 0;
}
