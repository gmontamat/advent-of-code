#include <stdint.h>
#include <stdio.h>

int32_t computeSequence(int32_t row, int32_t col) {
    uint64_t code = 20151125;
    int32_t last_row = 1;
    int32_t current_row = 1, current_col = 1;

    while (1) {
        code = (code * 252533) % 33554393;
        current_col++;
        current_row--;
        if (current_row == 0) {
            current_row = ++last_row;
            current_col = 1;
        }
        if (current_row == row && current_col == col) return code;
    }
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    int32_t row, col;

    // To continue, please consult the code grid in the manual.  Enter the code at row 2947, column 3029.
    while (fscanf(f, "To continue, please consult the code grid in the manual.  Enter the code at row %d, column %d.", &row, &col) == 2);
    fclose(f);

    // printf("%d, %d\n", row, col);
    printf("%d\n", computeSequence(row, col));

    return 0;
}
