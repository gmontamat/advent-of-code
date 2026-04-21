#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256
#define INSTR_SIZE 16

uint32_t runProgram(char instructions[][INSTR_SIZE], size_t total) {
    uint32_t a = 1, b = 0;  // Registers
    char rgstr, sign;
    uint32_t offset;
    size_t ctr = 0;  // Counter
    while (ctr < total) {  // ctr below 0 overflows to positive
        //printf("%s\n", instructions[ctr]);
        if (strstr(instructions[ctr], "hlf") != NULL) {
            sscanf(instructions[ctr], "hlf %c", &rgstr);
            switch (rgstr) {
                case 'a':
                    a = a >> 1;
                    break;
                case 'b':
                    b = b >> 1;
                    break;
                default:
                    printf("Input error!\n");
                    break;
            }
            ctr++;
            continue;
        }
        if (strstr(instructions[ctr], "tpl") != NULL) {
            sscanf(instructions[ctr], "tpl %c", &rgstr);
            switch (rgstr) {
                case 'a':
                    a *= 3;
                    break;
                case 'b':
                    b *= 3;
                    break;
                default:
                    printf("Input error!\n");
                    break;
            }
            ctr++;
            continue;
        }
        if (strstr(instructions[ctr], "inc") != NULL) {
            sscanf(instructions[ctr], "inc %c", &rgstr);
            switch (rgstr) {
                case 'a':
                    a++;
                    break;
                case 'b':
                    b++;
                    break;
                default:
                    printf("Input error!\n");
                    break;
            }
            ctr++;
            continue;
        }
        if (strstr(instructions[ctr], "jmp") != NULL) {
            sscanf(instructions[ctr], "jmp %c%u", &sign, &offset);
            if (sign == '-') ctr -= offset;
            else ctr += offset;
            continue;
        }
        if (strstr(instructions[ctr], "jie") != NULL) {
            sscanf(instructions[ctr], "jie %c, %c%u", &rgstr, &sign, &offset);
            if ((rgstr == 'a' && a % 2 == 0) || (rgstr == 'b' && b % 2 == 0)) {
                if (sign == '-') ctr -= offset;
                else ctr += offset;
            } else {
                ctr++;
            }
            continue;
        }
        if (strstr(instructions[ctr], "jio") != NULL) {
            sscanf(instructions[ctr], "jio %c, %c%u", &rgstr, &sign, &offset);
            if ((rgstr == 'a' && a == 1) || (rgstr == 'b' && b == 1)) {
                if (sign == '-') ctr -= offset;
                else ctr += offset;
            } else {
                ctr++;
            }
            continue;
        }
        printf("Unknown instruction!\n");
    }
    return b;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution2.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;


    char instructions[BUFFER_SIZE][INSTR_SIZE];
    size_t line = 0;

    // Read instructions into memory
    while (fgets(instructions[line], INSTR_SIZE, f) != NULL && line < BUFFER_SIZE) {
        // Remove the trailing newline character if necessary
        instructions[line][strcspn(instructions[line], "\n")] = '\0';
        line++;
    }
    fclose(f);

    printf("%u\n", runProgram(instructions, line));

    return 0;
}
