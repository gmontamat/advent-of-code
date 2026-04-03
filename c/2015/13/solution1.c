#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_DS_IMPLEMENTATION
#include "../thirdparty/stb_ds.h"

#define BUFFER_SIZE 16

typedef struct { size_t from, to; } Pair;
typedef struct { Pair key; uint32_t value; } FeelingsTable;

int32_t dfs(FeelingsTable *table, size_t *array, int32_t current_happiness, int32_t maximum_happiness, size_t total_people) {
    // Base case
    if ((size_t)arrlen(array) == total_people) {
        Pair from_to = {array[0], arrlast(array)};
        Pair to_from = {arrlast(array), array[0]};
        current_happiness += hmget(table, from_to);
        current_happiness += hmget(table, to_from);
        if (current_happiness > maximum_happiness) return current_happiness;
        else return maximum_happiness;
    }
    // Recursion over all pairs
    for (size_t person=1; person<total_people; ++person) {
        // Check if person not in array
        bool found = false;
        for (size_t i=1; i<(size_t)arrlen(array); ++i) {
            if (person == array[i]) {
                found = true;
                break;
            }
        }
        if (found) continue;
        // Person not in array, add and call dfs
        int32_t next_happiness = current_happiness;
        Pair from_to = {arrlast(array), person};
        Pair to_from = {person, arrlast(array)};
        next_happiness += hmget(table, from_to);
        next_happiness += hmget(table, to_from);
        // Copy array adding person
        size_t *array_next = NULL;
        for (size_t i=0; i<(size_t)arrlen(array); ++i) {
            arrput(array_next, array[i]);
        }
        arrput(array_next, person);
        maximum_happiness = dfs(table, array_next, next_happiness, maximum_happiness, total_people);
    }
    return maximum_happiness;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    // Map name -> id
    size_t total_people = 0;
    struct { char *key; size_t value; } *people = NULL;
    // Map (id_from, id_to) -> happiness
    FeelingsTable *table = NULL;
    Pair from_to;

    char person_a[BUFFER_SIZE], person_b[BUFFER_SIZE];
    char happiness_sign[BUFFER_SIZE];
    // DFS note: we can't prune the search because there's 2 signs,
    // For larger input, normalize happiness by adding abs(min(happiness))
    // to all so that minumum is zero. Then change signs to minimize
    // "sadness" so as to prune current branch of DFS. You can also
    // sort by sadness during the recursion step.
    int32_t happiness;

    while (fscanf(f, "%s would %s %d happiness units by sitting next to %s",
                  person_a, happiness_sign, &happiness, person_b) == 4) {
        // Handle full stop '.'
        person_b[strlen(person_b) - 1] = '\0';
        // Parse gain/lose
        if (strcmp("lose", happiness_sign) == 0) happiness *= -1;
        // printf("%s -> %s == %d\n", person_a, person_b, happiness);

        char *person_from = malloc(strlen(person_a) + 1);
        strcpy(person_from, person_a);
        char *person_to = malloc(strlen(person_b) + 1);
        strcpy(person_to, person_b);
        
        // Put people in map (assign id)
        if (shgeti(people, person_from) == -1) shput(people, person_from, total_people++);
        if (shgeti(people, person_to) == -1) shput(people, person_to, total_people++);

        // Store (id_from, id_to) -> happines in table
        from_to = (Pair){people[shgeti(people, person_from)].value, people[shgeti(people, person_to)].value};
        hmput(table, from_to, happiness);
    }

    // Maximize happiness (minimize happiness) using DFS
    size_t *array = NULL;
    arrput(array, 0);  // this person is an anchor because the table is round!
    printf("%d\n", dfs(table, array, 0, -999, total_people));

    return 0;
}
