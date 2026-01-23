#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1b.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    // Simpler version without dynamic arrays
    int32_t floor = 0;
    int c;
    while ((c = fgetc(f)) != EOF) {
        if (c == '(') floor++;
        else floor--;
    }
    printf("%d\n", floor);

    fclose(f);
    return 0;
}
