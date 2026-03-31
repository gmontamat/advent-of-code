#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 32

bool isValid(char *password) {
    size_t pair_equal = 0;
    char pair = '-';  // to be discarded by first pair found
    bool triple_increasing = false;
    for (size_t i=0; i<strlen(password) - 2; ++i) {
        if (password[i] == 'i' || password[i] == 'l' || password[i] == 'o') {
            return false;
        } else if (password[i] == password[i+1] && password[i] != pair) {
            pair_equal += 1;
            pair = password[i];
        } else if (password[i] + 2 == password[i+1] + 1 && password[i] + 2 == password[i+2]) {
            triple_increasing = true;
        }
    }
    if (!triple_increasing) return false;
    if (password[strlen(password) - 2] == password[strlen(password) - 1] &&
        password[strlen(password) - 2] != pair) pair_equal += 1;
    if (pair_equal > 1) return true;
    return false;
}

void updatePassword(char *password) {
    for (int i = strlen(password) - 1; i >= 0; --i) {
        if (password[i] == 'z') password[i] = 'a';
        else {
            password[i] += 1;
            break;
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline

        printf("%s", buffer);
        updatePassword(buffer);
        while (!isValid(buffer)) {
            updatePassword(buffer);
        }
        printf(" -> %s\n", buffer);
    }

    return 0;
}
