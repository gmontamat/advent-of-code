#include <stdio.h>
#include <stdlib.h>

struct Elf {
    size_t id;
    size_t presents;
    struct Elf *next;
};

size_t elves;  // global to help find the positions

struct Elf* createElf(size_t id, size_t presents) {
    struct Elf *elf = malloc(sizeof(struct Elf));

    elf->id = id;
    elf->presents = presents;
    elf->next = NULL;

    return elf;
}

struct Elf* appendFast(struct Elf **head, struct Elf *last, size_t id, size_t presents) {
    struct Elf *elf = createElf(id, presents);
    if (*head == NULL) {
        // first elf
        *head = elf;
        elf->next = *head;
    } else {
        // new elf
        last->next = elf;
        elf->next = *head;
    }
    // return pointer to last elf added to add a new one faster
    return elf;
}

struct Elf* findRightToVictim(struct Elf *elf) {
    struct Elf *right_to_victim = elf;
    for (size_t i = 0; i < elves / 2 - 1; ++i) {
        right_to_victim = right_to_victim->next;
    }
    return right_to_victim;
}

size_t solve(struct Elf *head) {
    if (head == NULL) {
        printf("Circle is empty!\n");
        return 0;
    }
    struct Elf *current = head;
    // First victim found via loop
    struct Elf *right_to_victim = findRightToVictim(current);
    struct Elf *victim = right_to_victim->next;
    while (1) {
        if (current->next == current) break;  // only one elf remains
        // printf("%zu steals from %zu\n", current->id, victim->id);
        // Remove current victim & choose next victim
        right_to_victim->next = victim->next;  // removes victim from circle
        if (elves % 2 == 0) {
            // the elf right to the next victim is the same as it is now
            victim = victim->next;
        } else {
            right_to_victim = victim->next;
            victim = victim->next->next;
        }
        elves--;
        // Next elf
        current = current->next;  // go to next elf
        // if (elves % 100 == 0) printf("remaining %zu..\n", elves);
    }
    return current->id;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution2.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    // Advent of circular linked lists
    // https://www.geeksforgeeks.org/c/c-program-to-implement-circular-linked-list/
    struct Elf *head = NULL;
    struct Elf *last = head;

    while (fscanf(f, "%zu", &elves) == 1);
    fclose(f);

    for (size_t i = 0; i < elves; ++i) {
        // append elves
        last = appendFast(&head, last,  i+1, 1);
    }
    printf("%zu\n", solve(head));

    return 0;
}
