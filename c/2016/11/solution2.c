#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

#define STB_DS_IMPLEMENTATION
#include "../thirdparty/stb_ds.h"

#define MAX_ELEMENTS 32
#define BUFFER_SIZE 256

typedef struct {
    char *key;
    size_t value;
} Element;

typedef struct {
    uint64_t key;
    int32_t value;
} State;  // Maps state -> minimum steps to get there

State *statemap = NULL;

bool loneMicrochip2(int32_t *generator, int32_t *microchip, size_t skip1, size_t skip2, size_t elements, int32_t floor) {
    for (size_t i = 0; i < elements; ++i) {
        if (i == skip1) continue;
        if (i == skip2) continue;
        if (microchip[i] == floor && generator[i] != floor) return true;
    }
    return false;
}

bool loneMicrochip(int32_t *generator, int32_t *microchip, size_t skip, size_t elements, int32_t floor) {
    for (size_t i = 0; i < elements; ++i) {
        if (i == skip) continue;
        if (microchip[i] == floor && generator[i] != floor) return true;
    }
    return false;
}

bool otherGeneratorsInFloor2(int32_t *generator, size_t skip1, size_t skip2, size_t elements, int32_t floor) {
    for (size_t i = 0; i < elements; ++i) {
        if (i == skip1) continue;
        if (i == skip2) continue;
        if (generator[i] == floor) return true;
    }
    return false;
}

bool otherGeneratorsInFloor(int32_t *generator, size_t skip, size_t elements, int32_t floor) {
    for (size_t i = 0; i < elements; ++i) {
        if (i == skip) continue;
        if (generator[i] == floor) return true;
    }
    return false;
}

uint64_t computeState(int32_t floor, int32_t *generator, int32_t *microchip, size_t elements) {
    uint64_t state = (uint64_t)floor;
    uint64_t mult = 10;
    for (size_t i = 0; i < elements; ++i) {
        state += (uint64_t)generator[i] * mult;
        mult *= 10;
    }
    for (size_t i = 0; i < elements; ++i) {
        state += (uint64_t)microchip[i] * mult;
        mult *= 10;
    }
    return state;
}

int32_t dfs(int32_t *generator, int32_t *microchip, size_t elements,
            int32_t floor, int32_t steps, int32_t min_steps) {
    // Base case: all chips & generators on 4th floor?
    bool done = true;
    for (size_t i = 0; i < elements; ++i) {
        if (generator[i] != 4) {
            done = false;
            break;
        }
        if (microchip[i] != 4) {
            done = false;
            break;
        }
    }
    if (done) {
        if (steps < min_steps) return steps;
        else return min_steps;
    }
    // If this branch is longer, already ignore it
    if (steps > min_steps) return min_steps;
    // Compute state so as not to backtrack:
    // eg. if we get to the initial state somewhere in our search
    // stop right away because we where already there at step 0!
    uint64_t state_id = computeState(floor, generator, microchip, elements);
    ptrdiff_t idx = hmgeti(statemap, state_id);
    if (idx == -1 || statemap[idx].value > steps) {
        hmput(statemap, state_id, steps);  // We got here in fewer steps, continue
    } else {
        return min_steps;
    }
    // Go up
    if (floor < 4) {
        for (size_t i = 0; i < elements; ++i) {
            // Move one generator up 1 floor
            if (generator[i] == floor) {
                bool move = true;  // Can we move it from this floor?
                // If same-type microchip and other generator in floor
                if (microchip[i] == floor && otherGeneratorsInFloor(generator, i, elements, floor)) move = false;
                // If other-type microchip without its generator in next floor
                if (loneMicrochip(generator, microchip, i, elements, floor + 1)) move = false;
                if (move) {
                    generator[i] = floor + 1;
                    min_steps = dfs(generator, microchip, elements, floor + 1, steps + 1, min_steps);
                    generator[i] = floor;  // backtrack
                }
            }
            // Move one microchip up 1 floor
            if (microchip[i] == floor) {
                bool move = true;  // Can we move it from this floor?
                // If other-type generator but type-generator not in new floor
                if (generator[i] != floor + 1 && otherGeneratorsInFloor(generator, i, elements, floor + 1)) move = false;
                if (move) {
                    microchip[i] = floor + 1;
                    min_steps = dfs(generator, microchip, elements, floor + 1, steps + 1, min_steps);
                    microchip[i] = floor;  // backtrack
                }
            }
            // Move microchip & generator (same type) up one floor
            if (generator[i] == floor && microchip[i] == floor) {
                bool move = true;  // Can we move both from this floor?
                // If other-type microchip without its generator in next floor
                if (loneMicrochip(generator, microchip, i, elements, floor + 1)) move = false;
                if (move) {
                    generator[i] = floor + 1;
                    microchip[i] = floor + 1;
                    min_steps = dfs(generator, microchip, elements, floor + 1, steps + 1, min_steps);
                    generator[i] = floor;  // backtrack
                    microchip[i] = floor;  // backtrack
                }
            }
            for (size_t j = 0; j < elements; ++j) {
                // Move 2 generators up one floor
                if (generator[i] == floor && generator[j] == floor && i < j) {
                    bool move = true;  // Can we move both from this floor?
                    // If there is a microchip of different type in new floor
                    if (loneMicrochip2(generator, microchip, i, j, elements, floor + 1)) move = false;
                    // If same-type microchip and other generator in floor
                    if ((microchip[i] == floor || microchip[j] == floor) &&
                        otherGeneratorsInFloor2(generator, i, j, elements, floor)) move = false;
                    if (move) {
                        generator[i] = floor + 1;
                        generator[j] = floor + 1;
                        min_steps = dfs(generator, microchip, elements, floor + 1, steps + 1, min_steps);
                        generator[i] = floor;  // backtrack
                        generator[j] = floor;  // backtrack
                    }
                }
                // Move 2 microchip up one floor
                if (microchip[i] == floor && microchip[j] == floor && i < j) {
                    bool move = true;  // Can we move both from this floor?
                    // If no same type generator but other generators in next floor
                    if (generator[i] != floor + 1 && otherGeneratorsInFloor(generator, i, elements, floor + 1)) move = false;
                    if (generator[j] != floor + 1 && otherGeneratorsInFloor(generator, j, elements, floor + 1)) move = false;
                    if (move) {
                        microchip[i] = floor + 1;
                        microchip[j] = floor + 1;
                        min_steps = dfs(generator, microchip, elements, floor + 1, steps + 1, min_steps);
                        microchip[i] = floor;  // backtrack
                        microchip[j] = floor;  // backtrack
                    }
                }
            }
        }
    }
    // Go down
    if (floor > 1) {
        for (size_t i = 0; i < elements; ++i) {
            // Move one generator down 1 floor
            if (generator[i] == floor) {
                bool move = true;  // Can we move it from this floor?
                // If same-type microchip and other generator in floor
                if (microchip[i] == floor && otherGeneratorsInFloor(generator, i, elements, floor)) move = false;
                // If other-type microchip without its generator in next floor
                if (loneMicrochip(generator, microchip, i, elements, floor - 1)) move = false;
                if (move) {
                    generator[i] = floor - 1;
                    min_steps = dfs(generator, microchip, elements, floor - 1, steps + 1, min_steps);
                    generator[i] = floor;  // backtrack
                }
            }
            // Move one microchip down 1 floor
            if (microchip[i] == floor) {
                bool move = true;  // Can we move it from this floor?
                // If other-type generator but type-generator not in new floor
                if (generator[i] != floor - 1 && otherGeneratorsInFloor(generator, i, elements, floor - 1)) move = false;
                if (move) {
                    microchip[i] = floor - 1;
                    min_steps = dfs(generator, microchip, elements, floor - 1, steps + 1, min_steps);
                    microchip[i] = floor;  // backtrack
                }
            }
            // Move microchip & generator (same type) down one floor
            if (generator[i] == floor && microchip[i] == floor) {
                bool move = true;  // Can we move both from this floor?
                // If other-type microchip without its generator in next floor
                if (loneMicrochip(generator, microchip, i, elements, floor - 1)) move = false;
                if (move) {
                    generator[i] = floor - 1;
                    microchip[i] = floor - 1;
                    min_steps = dfs(generator, microchip, elements, floor - 1, steps + 1, min_steps);
                    generator[i] = floor;  // backtrack
                    microchip[i] = floor;  // backtrack
                }
            }
            for (size_t j = 0; j < elements; ++j) {
                // Move 2 generators down one floor
                if (generator[i] == floor && generator[j] == floor && i < j) {
                    bool move = true;  // Can we move both from this floor?
                    // If there is a microchip of different type in new floor
                    if (loneMicrochip2(generator, microchip, i, j, elements, floor - 1)) move = false;
                    // If same-type microchip and other generator in floor
                    if ((microchip[i] == floor || microchip[j] == floor) &&
                        otherGeneratorsInFloor2(generator, i, j, elements, floor)) move = false;
                    if (move) {
                        generator[i] = floor - 1;
                        generator[j] = floor - 1;
                        min_steps = dfs(generator, microchip, elements, floor - 1, steps + 1, min_steps);
                        generator[i] = floor;  // backtrack
                        generator[j] = floor;  // backtrack
                    }
                }
                // Move 2 microchip down one floor
                if (microchip[i] == floor && microchip[j] == floor && i < j) {
                    bool move = true;  // Can we move both from this floor?
                    // If no same type generator but other generators in next floor
                    if (generator[i] != floor - 1 && otherGeneratorsInFloor(generator, i, elements, floor - 1)) move = false;
                    if (generator[j] != floor - 1 && otherGeneratorsInFloor(generator, j, elements, floor - 1)) move = false;
                    if (move) {
                        microchip[i] = floor - 1;
                        microchip[j] = floor - 1;
                        min_steps = dfs(generator, microchip, elements, floor - 1, steps + 1, min_steps);
                        microchip[i] = floor;  // backtrack
                        microchip[j] = floor;  // backtrack
                    }
                }
            }
        }
    }
    return min_steps;
}

size_t getElements(char *buffer, Element **hash) {
    size_t elements = 0;

    const char* pattern = "[a-z]+-compatible";
    regex_t regex;
    regmatch_t match;
    const char *cursor = buffer;
    char element[BUFFER_SIZE];

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return 1;
    }

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        int start = (int)match.rm_so;
        int end = (int)match.rm_eo;

        char match_str[end - start + 1];
        snprintf(match_str, end - start + 1, "%.*s", end - start, cursor + start);
        sscanf(match_str, "%[^-]-compatible", element);
        // printf("%s\n", element);
        shput(*hash, element, elements++);
        cursor += end;
    }

    regfree(&regex);

    return elements;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    // Read the whole file
    char *buffer = 0;
    long length;
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length + 1);
    if (buffer) {
        fread(buffer, 1, length, f);
    }
    buffer[length] = '\0';
    // Map elements found in file
    Element *hash = NULL;  // map element name to id
    sh_new_strdup(hash);   // use strdup for string management (slow)
    size_t elements = getElements(buffer, &hash);
    free(buffer);
    // Add space for 2 more elements (problem statement)
    int32_t generator[elements + 2];  // Store floor of generators[element]
    int32_t microchip[elements + 2];  // Store floor of microchips[element]

    // Read line by line assigning values
    int32_t floor = 1;
    char linebuff[BUFFER_SIZE];
    fseek(f, 0, SEEK_SET);
    while (fgets(linebuff, BUFFER_SIZE, f) != NULL) {
        linebuff[strcspn(linebuff, "\n")] = '\0';  // Remove trailing newline
        for (ptrdiff_t i=0; i < shlen(hash); ++i) {
            // Check if generator is in this floor
            char gen[BUFFER_SIZE] = "";
            strcat(gen, hash[i].key);
            strcat(gen, " generator");
            if (strstr(linebuff, gen)) generator[hash[i].value] = floor;
            // Check if microchip is in this floor
            char mic[BUFFER_SIZE] = "";
            strcat(mic, hash[i].key);
            strcat(mic, "-compatible microchip");
            if (strstr(linebuff, mic)) microchip[hash[i].value] = floor;
        }
        floor++;
    }
    fclose(f);

    // for (size_t i = 0; i < elements; ++i) {
    //     printf("%s; mc floor: %d gen floor: %d\n", hash[i].key, microchip[i], generator[i]);
    // }
    shfree(hash);

    // An elerium generator.
    // An elerium-compatible microchip.
    // A dilithium generator.
    // A dilithium-compatible microchip.
    generator[elements] = 1;
    microchip[elements] = 1;
    elements++;
    generator[elements] = 1;
    microchip[elements] = 1;
    elements++;

    // limit search by optimistically assuming <100 steps
    int32_t min_steps = dfs(generator, microchip, elements, 1, 0, 99);
    printf("%d\n", min_steps);
    return 0;
}
