#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <openssl/md5.h>

static int md5_has_6_leading_hex_zeros(const unsigned char digest[16]) {
    // First 6 hex zeros => first 3 bytes are 0
    if (digest[0] != 0x00) return 0;
    if (digest[1] != 0x00) return 0;
    if (digest[2] != 0x00) return 0;
    return 1;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    int ch;
    char buf[128];
    size_t i = 0;
    while (i + 1 < sizeof(buf) && (ch = fgetc(f)) != EOF) {
        buf[i++] = (char)ch;
    }
    buf[i] = '\0';

    // Advent of bitcoin
    int32_t num = 0;
    char s[256];
    while (1) {
        num++;
        strcpy(s, buf);
        char snum[128];
        snprintf(snum, sizeof(snum), "%d", num);
        strcat(s, snum);

        unsigned char digest[MD5_DIGEST_LENGTH];
        MD5((const unsigned char *)s, strlen(s), digest);

        // Check if it has trailing zeros
        if (md5_has_6_leading_hex_zeros(digest)) {
            printf("%d\n", num);
            break;
        }
    }

    return 0;
}
