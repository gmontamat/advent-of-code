#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    int32_t a, b, c;
    int32_t count = 0;

    while (fscanf(f, "%d %d %d", &a, &b, &c) == 3) {
        if ((a + b) > c && (a + c) > b && (c + b) > a) count++;
    }
    fclose(f);

    printf("%d\n", count);
    return 0;
}
