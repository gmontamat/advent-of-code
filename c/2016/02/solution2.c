#include <stdio.h>


int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution2.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    const char numpad[] = {
        '0', '0', '1', '0', '0',
        '0', '2', '3', '4', '0',
        '5', '6', '7', '8', '9',
        '0', 'A', 'B', 'C', '0',
        '0', '0', 'D', '0', '0' 
    };
    size_t idx = 10;  // Starts with number 5
    size_t i = 0;
    char code[32];

    int move;
    while ((move = fgetc(f)) != EOF) {
        switch (move) {
            case 'U':
                if (idx > 4 && numpad[idx-5] != '0') idx -= 5;
                break;
            case 'L':
                if (idx % 5 > 0 && numpad[idx-1] != '0') idx--;
                break;
            case 'R':
                if (idx % 5 < 4 && numpad[idx+1] != '0') idx++;
                break;
            case 'D':
                if (idx < 20 && numpad[idx+5] != '0') idx += 5;
                break;
            case '\n':
                code[i++] = numpad[idx];
            default:
                break;
        }
    }
    code[i++] = '\0';
    printf("%s\n", code);

    return 0;
}
