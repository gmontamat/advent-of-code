#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

bool play(int32_t player_hp, int32_t player_att, int32_t player_def, int32_t enemy_hp, int32_t enemy_att, int32_t enemy_def) {
    int32_t damage2enemy = MAX(1, player_att - enemy_def);
    int32_t damage2player = MAX(1, enemy_att - player_def);
    if (enemy_hp * damage2player <= player_hp * damage2enemy) return true;
    return false;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution2.out input

    // Optimization: sort descending
    const int32_t weapon_cst[] = {8, 10, 25, 40, 74};
    const int32_t weapon_pts[] = {4, 5, 6, 7, 8};
    const int32_t armor_cst[] = {13, 31, 53, 75, 102, 0};
    const int32_t armor_pts[] = {1, 2, 3, 4, 5, 0};
    const int32_t ring_cst[] = {25, 50, 100, 20, 40, 80, 0, 0};
    const int32_t ring_pts[] = {1, 2, 3, -1, -2, -3, 0, 0};

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    int32_t player_hp = 8;
    if (strcmp(argv[1], "input") == 0) player_hp = 100;
    int32_t player_att;
    int32_t player_def;
    int32_t enemy_hp;
    int32_t enemy_att;
    int32_t enemy_def;

    int32_t max_cost = 0;

    if (fscanf(f, "Hit Points: %d\n", &enemy_hp) != 1) return 1;
    if (fscanf(f, "Damage: %d\n", &enemy_att) != 1) return 1;
    if (fscanf(f, "Armor: %d\n", &enemy_def) != 1) return 1;

    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 6; ++j) {
            for (size_t k = 0; k < 7; ++k) {
                for (size_t l = k + 1; l < 8; ++l) {  // never 2 rings of the same type
                    player_att = 0;
                    if (ring_pts[k] > 0) player_att += ring_pts[k];
                    if (ring_pts[l] > 0) player_att += ring_pts[l];
                    player_att += weapon_pts[i];
                    player_def = armor_pts[j];
                    if (ring_pts[k] < 0) player_def -= ring_pts[k];
                    if (ring_pts[l] < 0) player_def -= ring_pts[l];
                    if (weapon_cst[i] + armor_cst[j] + ring_cst[k] + ring_cst[l] > max_cost) {
                        if (!play(player_hp, player_att, player_def, enemy_hp, enemy_att, enemy_def)) {
                            max_cost = weapon_cst[i] + armor_cst[j] + ring_cst[k] + ring_cst[l];
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", max_cost);

    return 0;
}
