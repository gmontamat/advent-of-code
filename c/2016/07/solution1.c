#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

bool supportsTLS(char *ipv7) {
    bool bracket = false;
    bool found = false;
    // Check string within brackets
    for (size_t i = 0; i < strlen(ipv7) - 3; ++i) {
        if (ipv7[i] == '[') {
            bracket = true;
            continue;
        }
        if (ipv7[i] == ']') {
            bracket = false;
            continue;
        }
        if (ipv7[i] == ipv7[i+3] && ipv7[i+1] == ipv7[i+2] && ipv7[i] != ipv7[i+1]) {
            if (bracket) return false;
            else found = true;
        }
    }
    return found;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    int32_t ctr = 0;
    char ipv7[BUFFER_SIZE];

    while (fscanf(f, "%s", ipv7) == 1) {
        if (supportsTLS(ipv7)) ctr++;
    }
    fclose(f);

    printf("%d\n", ctr);
    return 0;
}
