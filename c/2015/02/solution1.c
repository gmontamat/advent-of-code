#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    int32_t sq_feet = 0;
    int l, w, h;
    while (fscanf(f, "%dx%dx%d", &l, &w, &h) == 3) {
        sq_feet += 2 * l * w +  2 * w * h + 2 * h * l;
        if (l * w < w * h && l * w < h * l) sq_feet += l * w;
        else if (w * h < h * l) sq_feet += w * h;
        else sq_feet += h * l;
    }
    fclose(f);

    printf("%d\n", sq_feet);
    return 0;
}
