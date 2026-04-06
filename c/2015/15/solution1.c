#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 32
#define MAX_ITEMS 8

int32_t findTotal(size_t idx, size_t ingredients, size_t teaspoons,
                  size_t *mix, int32_t max_score,
                  int32_t *capacity, int32_t *durability, int32_t *flavor,
                  int32_t *texture, int32_t *calories) {
    // Base case
    if (idx == ingredients - 1) {
        mix[idx] = teaspoons;  // use what's left, do not loop
        // for (size_t j=0; j<ingredients; ++j) printf("%zu ", mix[j]);
        int32_t cap = 0, dur = 0, fla = 0, tex = 0;
        for (size_t j=0; j<ingredients; ++j) {
            cap += (int32_t)mix[j] * capacity[j];
            dur += (int32_t)mix[j] * durability[j];
            fla += (int32_t)mix[j] * flavor[j];
            tex += (int32_t)mix[j] * texture[j];
        }
        if (cap < 0) cap = 0;
        if (dur < 0) dur = 0;
        if (fla < 0) fla = 0;
        if (tex < 0) tex = 0;
        int32_t score = cap * dur * fla * tex;
        // printf("==> %d\n", score);
        if (score > max_score) return score;
        else return max_score;
    }
    // Recursion
    for (size_t q=0; q<=teaspoons; ++q) {
        size_t *next_mix = malloc(ingredients * sizeof *next_mix);
        for (size_t j=0; j<idx; ++j) next_mix[j] = mix[j];
        next_mix[idx] = q;
        max_score = findTotal(
            idx+1, ingredients, teaspoons-q,
            next_mix, max_score, capacity, durability,
            flavor, texture, calories
        );
    }
    return max_score;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    char ingredient[BUFFER_SIZE];
    size_t i = 0;
    int32_t capacity[MAX_ITEMS];
    int32_t durability[MAX_ITEMS];
    int32_t flavor[MAX_ITEMS];
    int32_t texture[MAX_ITEMS];
    int32_t calories[MAX_ITEMS];

    // Butterscotch: capacity -1, durability -2, flavor 6, texture 3, calories 8
    while (fscanf(f, "%[^:]: capacity %d, durability %d, flavor %d, texture %d, calories %d",
                  ingredient, &capacity[i], &durability[i], &flavor[i], &texture[i], &calories[i]) == 6) {
        i++;
    }

    size_t mix[i];
    for (size_t j=0; j<i; ++j) mix[j] = 0;

    printf("%d\n", findTotal(0, i, 100, mix, 0, capacity, durability, flavor, texture, calories));

    return 0;
}
