#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

static int32_t cost[5] = {53, 73, 113, 173, 229};

int32_t dfs(int32_t player_hp, int32_t player_mana, int32_t boss_hp, int32_t boss_dmg,
            int32_t shield_turns, int32_t poison_turns, int32_t recharge_turns,
            int32_t mana_spent, int32_t min_spent, bool player_turn) {
    if (mana_spent > min_spent) return min_spent;
    // Shield, Poison, and Recharge effects
    int32_t player_armor = 0;
    if (shield_turns > 0) {
        player_armor = 7;
        shield_turns--;
    }
    if (poison_turns > 0) {
        boss_hp -= 3;
        poison_turns--;
    }
    if (recharge_turns > 0) {
        player_mana += 101;
        recharge_turns--;
    }
    // Check for victory after effects
    if (boss_hp <= 0) {
        if (mana_spent < min_spent) return mana_spent;
        else return min_spent;
    }
    if (player_turn) {
        for (size_t i=0; i<5; ++i) {
            if (player_mana < cost[i]) continue;
            if (i == 2 && shield_turns > 0) continue;  // can't cast this now
            if (i == 3 && poison_turns > 0) continue;
            if (i == 4 && recharge_turns > 0) continue;
            int32_t next_player_mana, next_mana_spent;
            int32_t next_player_hp = player_hp;
            int32_t next_boss_hp = boss_hp;
            int32_t next_poison_turns = poison_turns;
            int32_t next_shield_turns = shield_turns;
            int32_t next_recharge_turns = recharge_turns;
            next_player_mana = player_mana - cost[i];
            next_mana_spent = mana_spent + cost[i];
            switch (i) {
                case 0:
                    next_boss_hp -= 4;
                    break;
                case 1:
                    next_boss_hp -= 2;
                    next_player_hp += 2;
                    break;
                case 2:
                    next_shield_turns = 6;
                    break;
                case 3:
                    next_poison_turns = 6;
                    break;
                case 4:
                    next_recharge_turns = 5;
                    break;
                default:
                    break;
            }
            // Check for victory or recurse
            if (boss_hp <= 0) {
                if (next_mana_spent < min_spent) return next_mana_spent;
                else return min_spent;
            } else {
                min_spent = dfs(
                    next_player_hp, next_player_mana, next_boss_hp, boss_dmg,
                    next_shield_turns, next_poison_turns, next_recharge_turns,
                    next_mana_spent, min_spent, false
                );
            }
        }
    } else {
        player_hp -= MAX(boss_dmg - player_armor, 1);
        if (player_hp <= 0) return min_spent;  // player loses
        min_spent = dfs(
            player_hp, player_mana, boss_hp, boss_dmg,
            shield_turns, poison_turns, recharge_turns,
            mana_spent, min_spent, true
        );
    }
    return min_spent;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    // Advent of DFS!
    int32_t player_hp = 10;
    int32_t player_mana = 250;
    if (strcmp(argv[1], "input") == 0) {
        player_hp = 50;
        player_mana = 500;
    }

    int32_t boss_hp, boss_dmg;
    if (fscanf(f, "Hit Points: %d\n", &boss_hp) != 1) return 1;
    if (fscanf(f, "Damage: %d\n", &boss_dmg) != 1) return 1;

    //printf("%d %d %d %d\n", player_hp, player_mana, boss_hp, boss_dmg);
    int32_t min_spent = dfs(
        player_hp, player_mana, boss_hp, boss_dmg,
        0, 0, 0,
        0, 9999999, true
    );
    printf("%d\n", min_spent);

    return 0;
}
