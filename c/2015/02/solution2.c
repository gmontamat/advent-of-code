#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution2.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    int32_t sq_feet = 0;
    int l, w, h;
    while (fscanf(f, "%dx%dx%d", &l, &w, &h) == 3) {
        sq_feet += l * w * h;  // cubic feet for bow
        if (l < w && l < h) {
            if (w < h) sq_feet += 2 * l + 2 * w;
            else sq_feet += 2 * l + 2 * h;
        } else if (w < h) {
            if (l < h) sq_feet += 2 * w + 2 * l;
            else sq_feet += 2 * w + 2 * h;
        } else if (w < l) sq_feet += 2 * h + 2 * w;
        else sq_feet += 2 * h + 2 * l;
    }
    fclose(f);

    printf("%d\n", sq_feet);
    return 0;
}
