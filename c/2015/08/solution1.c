#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    int32_t charCount = 0, memCount = 0;

    char buffer[BUFFER_SIZE];

    FILE *f = fopen(argv[1], "rb");
    if (!f) return 1;

    while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline

        int32_t chars = strlen(buffer);
        int32_t mem = 0;
        for (size_t i=1; i < strlen(buffer) - 1; ++i) {
            if (buffer[i] == '\\') {
                if (buffer[i+1] == 'x') i += 3;  // Hex escape is \xhh
                else i++;
            }
            mem++;
        }
        // printf("%s | %d | %d\n", buffer, chars, mem);
        charCount += chars;
        memCount += mem;
    }

    //printf("Characters: %d\nMemory: %d\n", charCount, memCount);
    printf("%d\n", charCount - memCount);

    return 0;
}
