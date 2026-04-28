#include <openssl/md5.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

char md5_5zeros_6thdigit(const unsigned char digest[16]) {
    // First 4 hex zeros => first 2 bytes are 0
    if (digest[0] != 0x00) return '*';
    if (digest[1] != 0x00) return '*';
    // 5th zero => high nibble of digest[2] is 0
    if ((digest[2] & 0xF0) == 0x00) {
        char md5string[33]; // 32 chars + null terminator
        for(int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
            sprintf(&md5string[i*2], "%02x", digest[i]);
        }
        return md5string[5];
    }
    return '*';
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    int ch;
    char buf[32];
    size_t i = 0;
    while (i + 1 < sizeof(buf) && (ch = fgetc(f)) != EOF) {
        if ((char)ch != '\n') buf[i++] = (char)ch;
    }
    buf[i] = '\0';
    fclose(f);

    // Advent of bitcoin
    int32_t num = 0;
    int32_t ctr = 0;
    char s[256];
    while (ctr < 8) {
        num++;
        strcpy(s, buf);
        char snum[256];
        snprintf(snum, sizeof(snum), "%d", num);
        strcat(s, snum);

        unsigned char digest[MD5_DIGEST_LENGTH];
        MD5((const unsigned char *)s, strlen(s), digest);

        // Check if it has leading zeros
        char digit = md5_5zeros_6thdigit(digest);
        if (digit != '*') {
            printf("%c", digit);
            ctr++;
        }
    }

    printf("\n");
    return 0;
}
