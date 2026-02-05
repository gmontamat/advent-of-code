#include <stdio.h>


int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    const int numpad[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t idx = 4;  // Starts with number 5
    size_t i = 0;
    int code[32];

    int move;
    while ((move = fgetc(f)) != EOF) {
        switch (move) {
            case 'U':
                if (idx > 2) idx -= 3;
                break;
            case 'L':
                if (idx % 3 > 0) idx--;
                break;
            case 'R':
                if (idx % 3 < 2) idx++;
                break;
            case 'D':
                if (idx < 6) idx += 3;
                break;
            case '\n':
                code[i++] = numpad[idx];
            default:
                break;
        }
    }

    for (size_t j=0; j<i; ++j) {
        printf("%d", code[j]);
    }
    printf("\n");
    return 0;
}
