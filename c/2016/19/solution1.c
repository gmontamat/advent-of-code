#include <stdio.h>
#include <stdlib.h>

struct Elf {
    size_t id;
    size_t presents;
    struct Elf *next;
};

struct Elf* createElf(size_t id, size_t presents) {
    struct Elf *elf = malloc(sizeof(struct Elf));

    elf->id = id;
    elf->presents = presents;
    elf->next = NULL;

    return elf;
}

// void append(struct Elf **head, size_t id, size_t presents) {
//     // Create and add an elf to the "end of the circle"
//     struct Elf *elf = createElf(id, presents);
//     if (*head == NULL) {
//         // first item
//         *head = elf;
//         elf->next = *head;
//     } else {
//         // find last item (pointing to head)
//         struct Elf *temp = *head;
//         while (temp->next != *head) {
//             temp = temp->next;
//         }
//         temp->next = elf;
//         elf->next = *head;
//     }
// }

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

size_t solve(struct Elf *head) {
    if (head == NULL) {
        printf("Circle is empty!\n");
        return 0;
    }
    struct Elf *temp = head;
    while (1) {
        if (temp->next == temp) break;  // only one elf remains
        temp->presents += temp->next->presents;
        temp->next = temp->next->next;  // next elf is removed from circle
        temp = temp->next;  // go to next elf
    }

    return temp->id;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;  // usage ./solution1.out input

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    // Advent of circular linked lists
    // https://www.geeksforgeeks.org/c/c-program-to-implement-circular-linked-list/
    size_t elves;
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
