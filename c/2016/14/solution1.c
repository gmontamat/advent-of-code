#include <openssl/md5.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 200000

void md5_to_hex_fast(unsigned char *digest, char *output) {
    static const char hex_chars[] = "0123456789abcdef";
    for (int i = 0; i < 16; i++) {
        output[i * 2]     = hex_chars[(digest[i] >> 4) & 0x0F];
        output[i * 2 + 1] = hex_chars[digest[i] & 0x0F];
    }
    output[32] = '\0';
}

char three_in_row(char string[33]) {
    for (size_t i = 0; i < 30; ++i) {
        if (string[i] == string[i+1] && string[i] == string[i + 2])
            return string[i];
    }
    return 'X';
}

bool five_in_row(char string[33], char c) {
    for (size_t i = 0; i < 28; ++i) {
        if (string[i] == c && string[i+1] == c && string[i+2] == c &&
            string[i+3] == c && string[i+4] == c) return true;
    }
    return false;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    char salt[BUFSIZ];
    fscanf(f, "%s", salt);
    fclose(f);

    size_t len = strlen(salt);

    char md5[MAX_SIZE][33];
    char num[10];
    for (size_t i = 0; i < MAX_SIZE; ++i) {
        // salt + idx
        salt[len] = '\0';
        sprintf(num, "%zu", i);
        strcat(salt, num);
        // to md5
        unsigned char digest[MD5_DIGEST_LENGTH];
        MD5((const unsigned char *)salt, strlen(salt), digest);
        md5_to_hex_fast(digest, md5[i]);
    }

    // Get 64th key
    size_t ctr = 0, last = 0;
    while (ctr < 64 && last < MAX_SIZE - 1000) {
        char c = three_in_row(md5[last]);
        if (c != 'X') {
            for (size_t i = last + 1; i < last + 1000; ++i) {
                if (five_in_row(md5[i], c)) {
                    ctr++;
                    break;
                }
            }
        }
        last++;
    }

    printf("%zu\n", --last);
    return 0;
}
