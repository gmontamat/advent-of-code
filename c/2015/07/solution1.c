#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define BUFFER_SIZE 256
#define OPERATOR_SIZE 8

bool isNumber(char *string) {
    for (size_t i=0; string[i] != '\0'; ++i) {
        if (!isdigit(string[i])) return false;
    }
    return true;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    // Use stb_ds hash map as a dict
    struct { char *key; uint16_t value; } *circuit = NULL;

    char buffer[BUFFER_SIZE];
    char operatorA[OPERATOR_SIZE], operatorB[OPERATOR_SIZE], output[OPERATOR_SIZE];
    char *endptr;
    uint16_t valueA, valueB;
    bool complete = false;

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    while (!complete) {
        complete = true;
        fseek(f, 0, SEEK_SET);
        while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline

            if (strstr(buffer, "AND") != NULL) {
                sscanf(buffer, "%s AND %s -> %s", operatorA, operatorB, output);
                if (shgeti(circuit, output) > -1) continue;  // Skip if already solved
                // Get operatorA value
                if (isNumber(operatorA)) {
                    valueA = (uint16_t) strtol(operatorA, &endptr, 10);
                } else if (shgeti(circuit, operatorA) < 0) {
                    complete = false;
                    continue;
                } else {
                    valueA = circuit[shgeti(circuit, operatorA)].value;
                }
                // Get operatorB value
                if (isNumber(operatorB)) {
                    valueB = (uint16_t) strtol(operatorB, &endptr, 10);
                } else if (shgeti(circuit, operatorB) < 0) {
                    complete = false;
                    continue;
                } else {
                    valueB = circuit[shgeti(circuit, operatorB)].value;
                }
                char *key = malloc(strlen(output) + 1);
                strcpy(key, output);
                shput(circuit, key, valueA & valueB);
            } else if (strstr(buffer, "OR") != NULL) {
                sscanf(buffer, "%s OR %s -> %s", operatorA, operatorB, output);
                if (shgeti(circuit, output) > -1) continue;  // Skip if already solved
                // Get operatorA value
                if (isNumber(operatorA)) {
                    valueA = (uint16_t) strtol(operatorA, &endptr, 10);
                } else if (shgeti(circuit, operatorA) < 0) {
                    complete = false;
                    continue;
                } else {
                    valueA = circuit[shgeti(circuit, operatorA)].value;
                }
                // Get operatorB value
                if (isNumber(operatorB)) {
                    valueB = (uint16_t) strtol(operatorB, &endptr, 10);
                } else if (shgeti(circuit, operatorB) < 0) {
                    complete = false;
                    continue;
                } else {
                    valueB = circuit[shgeti(circuit, operatorB)].value;
                }
                char *key = malloc(strlen(output) + 1);
                strcpy(key, output);
                shput(circuit, key, valueA | valueB);
            } else if (strstr(buffer, "LSHIFT") != NULL) {
                sscanf(buffer, "%s LSHIFT %s -> %s", operatorA, operatorB, output);
                if (shgeti(circuit, output) > -1) continue;  // Skip if already solved
                // Get operatorA value
                if (isNumber(operatorA)) {
                    valueA = (uint16_t) strtol(operatorA, &endptr, 10);
                } else if (shgeti(circuit, operatorA) < 0) {
                    complete = false;
                    continue;
                } else {
                    valueA = circuit[shgeti(circuit, operatorA)].value;
                }
                // Get operatorB value
                if (isNumber(operatorB)) {
                    valueB = (uint16_t) strtol(operatorB, &endptr, 10);
                } else if (shgeti(circuit, operatorB) < 0) {
                    complete = false;
                    continue;
                } else {
                    valueB = circuit[shgeti(circuit, operatorB)].value;
                }
                char *key = malloc(strlen(output) + 1);
                strcpy(key, output);
                shput(circuit, key, valueA << valueB);
            } else if (strstr(buffer, "RSHIFT") != NULL) {
                sscanf(buffer, "%s RSHIFT %s -> %s", operatorA, operatorB, output);
                if (shgeti(circuit, output) > -1) continue;  // Skip if already solved
                // Get operatorA value
                if (isNumber(operatorA)) {
                    valueA = (uint16_t) strtol(operatorA, &endptr, 10);
                } else if (shgeti(circuit, operatorA) < 0) {
                    complete = false;
                    continue;
                } else {
                    valueA = circuit[shgeti(circuit, operatorA)].value;
                }
                // Get operatorB value
                if (isNumber(operatorB)) {
                    valueB = (uint16_t) strtol(operatorB, &endptr, 10);
                } else if (shgeti(circuit, operatorB) < 0) {
                    complete = false;
                    continue;
                } else {
                    valueB = circuit[shgeti(circuit, operatorB)].value;
                }
                char *key = malloc(strlen(output) + 1);
                strcpy(key, output);
                shput(circuit, key, valueA >> valueB);
            } else if (strstr(buffer, "NOT") != NULL) {
                sscanf(buffer, "NOT %s -> %s", operatorA, output);
                if (shgeti(circuit, output) > -1) continue;  // Skip if already solved
                // Get operatorA value
                if (isNumber(operatorA)) {
                    valueA = (uint16_t) strtol(operatorA, &endptr, 10);
                } else if (shgeti(circuit, operatorA) < 0) {
                    complete = false;
                    continue;
                } else {
                    valueA = circuit[shgeti(circuit, operatorA)].value;
                }
                char *key = malloc(strlen(output) + 1);
                strcpy(key, output);
                shput(circuit, key, ~valueA);
            } else {
                sscanf(buffer, "%s -> %s", operatorA, output);
                if (shgeti(circuit, output) > -1) continue;  // Skip if already solved
                // Get operatorA value
                if (isNumber(operatorA)) {
                    valueA = (uint16_t) strtol(operatorA, &endptr, 10);
                } else if (shgeti(circuit, operatorA) < 0) {
                    complete = false;
                    continue;
                } else {
                    valueA = circuit[shgeti(circuit, operatorA)].value;
                }
                char *key = malloc(strlen(output) + 1);
                strcpy(key, output);
                shput(circuit, key, valueA);
            }
        }
    }
    // for (long i=0; i < shlen(circuit); ++i) {
    //     printf("%s => %d\n", circuit[i].key, circuit[i].value);
    // }
    // printf("\n");

    if (shgeti(circuit, "a") > -1) printf("%d\n", circuit[shgeti(circuit, "a")].value);
    return 0;
}
