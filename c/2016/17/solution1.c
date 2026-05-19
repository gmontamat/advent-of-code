#include <openssl/md5.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BUFFER_SIZE 256

void md5_to_hex_fast(unsigned char *digest, char *output) {
    static const char hex_chars[] = "0123456789abcdef";
    for (int i = 0; i < 16; i++) {
        output[i * 2]     = hex_chars[(digest[i] >> 4) & 0x0F];
        output[i * 2 + 1] = hex_chars[digest[i] & 0x0F];
    }
    output[32] = '\0';
}

int32_t dfs(char *passcode, char *path, int32_t x, int32_t y, int32_t steps, int32_t min_steps, char *min_path) {
    // Base case: we reached the vault
    if (x == 3 && y == 3) {
        if (steps < min_steps) {
            memcpy(min_path, path, strlen(path) + 1);  // copy the \0 too!
            return steps;
        } else {
            return min_steps;
        }
    }
    // Prune
    if (steps >= min_steps) return min_steps;
    // Recursion
    // Compute md5 of current position
    size_t len = strlen(path);
    char string[BUFFER_SIZE] = "";
    strcat(string, passcode);
    strcat(string, path);
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((const unsigned char *)string, strlen(string), digest);
    char hex[33];
    md5_to_hex_fast(digest, hex);
    // Go up?
    if (y > 0 && (hex[0] == 'b' || hex[0] == 'c' || hex[0] == 'd' || hex[0] == 'e' || hex[0] == 'f')) {
        strcat(path, "U");
        min_steps = dfs(passcode, path, x, y - 1, steps + 1, min_steps, min_path);
        path[len] = '\0';  // backtrack
    }
    // Go down?
    if (y < 3 && (hex[1] == 'b' || hex[1] == 'c' || hex[1] == 'd' || hex[1] == 'e' || hex[1] == 'f')) {
        strcat(path, "D");
        min_steps = dfs(passcode, path, x, y + 1, steps + 1, min_steps, min_path);
        path[len] = '\0';  // backtrack
    }
    // Go left?
    if (x > 0 && (hex[2] == 'b' || hex[2] == 'c' || hex[2] == 'd' || hex[2] == 'e' || hex[2] == 'f')) {
        strcat(path, "L");
        min_steps = dfs(passcode, path, x - 1, y, steps + 1, min_steps, min_path);
        path[len] = '\0';  // backtrack
    }
    // Go right?
    if (x < 3 && (hex[3] == 'b' || hex[3] == 'c' || hex[3] == 'd' || hex[3] == 'e' || hex[3] == 'f')) {
        strcat(path, "R");
        min_steps = dfs(passcode, path, x + 1, y, steps + 1, min_steps, min_path);
        path[len] = '\0';  // backtrack
    }
    return min_steps;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    char passcode[BUFFER_SIZE], path[BUFFER_SIZE], min_path[BUFFER_SIZE];

    while (fgets(passcode, BUFFER_SIZE, f) != NULL) {
        passcode[strcspn(passcode, "\n")] = '\0';  // Remove trailing newline
        path[0] = '\0';      // path is an empty string at the beginning
        min_path[0] = '\0';
        int32_t min_steps = dfs(passcode, path, 0, 0, 0, INT32_MAX, min_path);
        if (min_steps < INT32_MAX) printf("%s\n", min_path);
        else printf("Vault not reachable\n");
    }
    fclose(f);

    return 0;
}
