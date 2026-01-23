#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution2b.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    // Simpler version without dynamic arrays
    int32_t floor = 0;
    int32_t ctr = 0;
    int c;
    while ((c = fgetc(f)) != EOF) {
        ctr++;
        if (c == '(') floor++;
        else floor--;
        if (floor < 0) {
            printf("%d\n", ctr);
            break;
        }
    }

    fclose(f);
    return 0;
}
