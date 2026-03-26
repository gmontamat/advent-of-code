#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    int32_t charCount = 0, encodedCount = 0;

    char buffer[BUFFER_SIZE];

    FILE *f = fopen(argv[1], "rb");
    if (!f) return 1;

    while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline

        int32_t chars = strlen(buffer);
        int32_t encoded = 6;  // "\"  and \""
        for (size_t i=1; i < strlen(buffer) - 1; ++i) {
            if (buffer[i] == '\\') encoded++;
            else if (buffer[i] == '\"') encoded++;
            encoded++;
        }
        // printf("%s | %d | %d\n", buffer, chars, mem);
        charCount += chars;
        encodedCount += encoded;
    }

    //printf("Characters: %d\nMemory: %d\n", charCount, memCount);
    printf("%d\n", encodedCount - charCount);

    return 0;
}
