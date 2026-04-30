#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

bool supportsSSL(char *ipv7) {
    bool bracket = false;
    char ba[BUFFER_SIZE][2];  // 2 chars, no null (not printed)
    size_t idx = 0;           // index of ABAs found
    // Check string within brackets
    for (size_t i = 0; i < strlen(ipv7) - 2; ++i) {
        if (ipv7[i] == '[') {
            bracket = true;
            continue;
        }
        if (ipv7[i] == ']') {
            bracket = false;
            continue;
        }
        // Find ABAs outside brackets
        if (bracket) continue;
        if (ipv7[i] == ipv7[i+2]) {
            ba[idx][0] = ipv7[i+1];
            ba[idx][1] = ipv7[i];  // no need to store b again
            idx++;
        }
    }
    // Check if BAB in brackets
    for (size_t i = 0; i < strlen(ipv7) - 2; ++i) {
        if (ipv7[i] == '[') {
            bracket = true;
            continue;
        }
        if (ipv7[i] == ']') {
            bracket = false;
            continue;
        }
        // Find ABAs outside brackets
        if (!bracket) continue;
        for (size_t j = 0; j < idx; ++j) {
            if (ba[j][0] == ipv7[i] && ba[j][1] == ipv7[i+1] && ba[j][0] == ipv7[i+2])
                return true;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    int32_t ctr = 0;
    char ipv7[BUFFER_SIZE];

    while (fscanf(f, "%s", ipv7) == 1) {
        if (supportsSSL(ipv7)) ctr++;
    }
    fclose(f);

    printf("%d\n", ctr);
    return 0;
}
