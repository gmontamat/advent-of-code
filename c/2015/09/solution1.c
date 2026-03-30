#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_DS_IMPLEMENTATION
#include "../thirdparty/stb_ds.h"

#define CITY_SIZE 32

typedef struct { size_t from, to; } Pair;
typedef struct { Pair key; uint32_t value; } DistanceGraph;

uint32_t dfs(DistanceGraph *graph, size_t *array, uint32_t currentDistance, uint32_t minDistance, size_t totalCities) {
    // printf("{");
    // for (size_t j=0; j<(size_t)arrlen(array); ++j) {
    //     printf(" %zu ", array[j]);
    // }
    // printf("} %d\n", currentDistance);
    if ((size_t)arrlen(array) == totalCities) return currentDistance;
    for (size_t i=0; i<totalCities; ++i) {
        // Check if item not in array
        bool found = false;
        for (size_t j=0; j<(size_t)arrlen(array); ++j) {
            if (array[j] == i) {
                found = true;
                break;
            }
        }
        if (found) continue;
        // Recurse for each city not in the array
        uint32_t nextDistance = currentDistance;
        if (arrlen(array) > 0) {
            Pair fromTo = {arrlast(array), i};
            nextDistance += hmget(graph, fromTo);
        }
        if (nextDistance < minDistance) {
            // Copy array and add i
            size_t *arrayNext = NULL;
            for (size_t j=0; j<(size_t)arrlen(array); ++j) {
                arrput(arrayNext, array[j]);
            }
            arrput(arrayNext, i);
            minDistance = dfs(graph, arrayNext, nextDistance, minDistance, totalCities);
        }
    }
    return minDistance;
}

int main(int argc, char **argv) {
    // Advent of Traveling Salesman
    if (argc < 2) return 1;  // usage ./solution1.out input

    int32_t distance;
    Pair fromTo;
    size_t totalCities = 0;
    char cityFrom[CITY_SIZE], cityTo[CITY_SIZE];
    // Map cityName -> cityId
    struct { char *key; size_t value; } *cityMap = NULL;
    // Map idFrom, idTo -> distance
    DistanceGraph *graph = NULL;

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    while (fscanf(f, "%s to %s = %d", cityFrom, cityTo, &distance) == 3) {
        // printf("%s -> %s | ", cityFrom, cityTo);
        // printf("%d\n", distance);
        // Add cityFrom to map if not there
        char *city1 = malloc(strlen(cityFrom) + 1);
        strcpy(city1, cityFrom);
        if (shgeti(cityMap, city1) < 0) shput(cityMap, city1, totalCities++);
        // Add cityTo to map if not there
        char *city2 = malloc(strlen(cityTo) + 1);
        strcpy(city2, cityTo);
        if (shgeti(cityMap, city2) < 0) shput(cityMap, city2, totalCities++);
        // Add (from, to) -> distance to the graph
        fromTo = (Pair){cityMap[shgeti(cityMap, cityFrom)].value, cityMap[shgeti(cityMap, cityTo)].value};
        hmput(graph, fromTo, distance);
        fromTo = (Pair){cityMap[shgeti(cityMap, cityTo)].value, cityMap[shgeti(cityMap, cityFrom)].value};
        hmput(graph, fromTo, distance);
    }

    // Use DFS to solve
    size_t *array = NULL;
    printf("%d\n", dfs(graph, array, 0, 999999, totalCities));

    // printf("%zu\n", totalCities);
    // for (long i=0; i < shlen(cityMap); ++i) {
    //     printf("%s => %zu\n", cityMap[i].key, cityMap[i].value);
    // }
    // printf("\n");

    return 0;
}
