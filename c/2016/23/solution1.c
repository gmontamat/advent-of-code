#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

int32_t countParams(char *instruction) {
    int32_t params = 0;
    for (size_t i = 0; i < strlen(instruction); ++i) {
        if (instruction[i] == ' ') params++;
    }
    return params;
}

int32_t run(char program[][BUFFER_SIZE], size_t psize) {
    size_t ctr = 0;
    int32_t a = 7, b = 0, c = 0, d = 0;  // registers
    char dstreg, srcreg;
    int32_t val, jmp;

    while (ctr < psize) {
        bool jump = false;
        if (strncmp(program[ctr], "cpy", 3) == 0) {
            if (isdigit(program[ctr][4]) || program[ctr][4] == '-') {
                sscanf(program[ctr], "cpy %d %c", &val, &dstreg);
            } else {
                sscanf(program[ctr], "cpy %c %c", &srcreg, &dstreg);
                switch (srcreg) {
                    case 'a':
                        val = a;
                        break;
                    case 'b':
                        val = b;
                        break;
                    case 'c':
                        val = c;
                        break;
                    case 'd':
                        val = d;
                        break;
                    default:
                        printf("I/O error\n");
                        exit(1);
                }
            }
            switch (dstreg) {
                case 'a':
                    a = val;
                    break;
                case 'b':
                    b = val;
                    break;
                case 'c':
                    c = val;
                    break;
                case 'd':
                    d = val;
                    break;
                default:
                    printf("I/O error: %s\n", program[ctr]);
                    // exit(1);
            }
        } else if (strncmp(program[ctr], "inc", 3) == 0) {
            sscanf(program[ctr], "inc %c", &dstreg);
            switch (dstreg) {
                case 'a':
                    a++;
                    break;
                case 'b':
                    b++;
                    break;
                case 'c':
                    c++;
                    break;
                case 'd':
                    d++;
                    break;
                default:
                    printf("I/O error: %s\n", program[ctr]);
                    // exit(1);
            }
        } else if (strncmp(program[ctr], "dec", 3) == 0) {
            sscanf(program[ctr], "dec %c", &dstreg);
            switch (dstreg) {
                case 'a':
                    a--;
                    break;
                case 'b':
                    b--;
                    break;
                case 'c':
                    c--;
                    break;
                case 'd':
                    d--;
                    break;
                default:
                    printf("I/O error: %s\n", program[ctr]);
                    // exit(1);
            }
        } else if (strncmp(program[ctr], "jnz", 3) == 0) {
            jump = true;
            size_t last = strlen(program[ctr]) - 1;
            if (isdigit(program[ctr][4]) || program[ctr][4] == '-') {
                if (isdigit(program[ctr][last])) {
                    sscanf(program[ctr], "jnz %d %d", &val, &jmp);
                } else {
                    sscanf(program[ctr], "jnz %d %c", &val, &dstreg);
                    switch (dstreg) {
                        case 'a':
                            jmp = a;
                            break;
                        case 'b':
                            jmp = b;
                            break;
                        case 'c':
                            jmp = c;
                            break;
                        case 'd':
                            jmp = d;
                            break;
                        default:
                            printf("I/O error: %s\n", program[ctr]);
                            jump = false;
                            // exit(1);
                    }
                }
                if (val == 0) jump = false;
            } else {
                if (isdigit(program[ctr][last])) {
                    sscanf(program[ctr], "jnz %c %d", &srcreg, &jmp);
                    switch (srcreg) {
                        case 'a':
                            if (a == 0) jump = false;
                            break;
                        case 'b':
                            if (b == 0) jump = false;
                            break;
                        case 'c':
                            if (c == 0) jump = false;
                            break;
                        case 'd':
                            if (d == 0) jump = false;
                            break;
                        default:
                            printf("I/O error: %s\n", program[ctr]);
                            jump = false;
                            // exit(1);
                    }
                } else {
                    sscanf(program[ctr], "jnz %c %c", &srcreg, &dstreg);
                    switch (srcreg) {
                        case 'a':
                            if (a == 0) jump = false;
                            break;
                        case 'b':
                            if (b == 0) jump = false;
                            break;
                        case 'c':
                            if (c == 0) jump = false;
                            break;
                        case 'd':
                            if (d == 0) jump = false;
                            break;
                        default:
                            printf("I/O error: %s\n", program[ctr]);
                            exit(1);
                    }
                    switch (dstreg) {
                        case 'a':
                            jmp = a;
                            break;
                        case 'b':
                            jmp = b;
                            break;
                        case 'c':
                            jmp = c;
                            break;
                        case 'd':
                            jmp = d;
                            break;
                        default:
                            printf("I/O error: %s\n", program[ctr]);
                            exit(1);
                    }
                }
            }
            if (jump) ctr += jmp;
        } else if (strncmp(program[ctr], "tgl", 3) == 0) {
            if (isdigit(program[ctr][4]) || program[ctr][4] == '-') {
                sscanf(program[ctr], "tgl %d", &val);
            } else {
                sscanf(program[ctr], "tgl %c", &srcreg);
                switch (srcreg) {
                    case 'a':
                        val = a;
                        break;
                    case 'b':
                        val = b;
                        break;
                    case 'c':
                        val = c;
                        break;
                    case 'd':
                        val = d;
                        break;
                    default:
                        printf("I/O error\n");
                        exit(1);
                }
            }
            if ((int32_t)ctr + val < (int32_t)psize && (int32_t)ctr + val >= 0) {
                int32_t params = countParams(program[ctr + val]);
                if (params == 1) {
                    if (strncmp(program[ctr + val], "inc", 3) == 0) {
                        program[ctr + val][0] = 'd';
                        program[ctr + val][1] = 'e';
                        program[ctr + val][2] = 'c';
                    } else {
                        program[ctr + val][0] = 'i';
                        program[ctr + val][1] = 'n';
                        program[ctr + val][2] = 'c';
                    }
                } else if (params == 2) {
                    if (strncmp(program[ctr + val], "jnz", 3) == 0) {
                        program[ctr + val][0] = 'c';
                        program[ctr + val][1] = 'p';
                        program[ctr + val][2] = 'y';
                    } else {
                        program[ctr + val][0] = 'j';
                        program[ctr + val][1] = 'n';
                        program[ctr + val][2] = 'z';
                    }
                } else {
                    printf("I/O error\n");
                    exit(1);
                }
            }
        } else {
            printf("I/O error\n");
            exit(1);
        }
        if (!jump) ctr++;
    }
    return a;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    char program[BUFFER_SIZE][BUFFER_SIZE];
    size_t ctr = 0;

    while (fgets(program[ctr], BUFFER_SIZE, f) != NULL) {
        program[ctr][strcspn(program[ctr], "\n")] = '\0';  // Remove trailing newline
        ctr++;
    }
    fclose(f);

    printf("%d\n", run(program, ctr));
    return 0;
}
