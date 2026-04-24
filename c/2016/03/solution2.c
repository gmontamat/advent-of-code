#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    int32_t col[3][3] = {
        {-1, -1, -1},
        {-1, -1, -1},
        {-1, -1, -1}
    };
    size_t i = 0;
    int32_t count = 0;

    while (fscanf(f, "%d %d %d", &col[0][i], &col[1][i], &col[2][i]) == 3) {
        i++;
        if (i==3) {
            for (size_t j = 0; j < 3; ++j) {
                if ((col[j][0] + col[j][1]) > col[j][2] &&
                    (col[j][0] + col[j][2]) > col[j][1] &&
                    (col[j][1] + col[j][2]) > col[j][0]) count++;
            }
            i = 0;
        }
    }
    fclose(f);

    printf("%d\n", count);
    return 0;
}
