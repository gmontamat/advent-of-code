#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define PI 3.14159265358979323846

struct Elf {
    size_t id;
    size_t presents;
    double_t position;  // unit circle distance
    struct Elf *next;
};

size_t elves;  // global to help find the positions

struct Elf* createElf(size_t id, size_t presents) {
    struct Elf *elf = malloc(sizeof(struct Elf));

    elf->id = id;
    elf->presents = presents;
    elf->position = (double_t)(id-1) / (double_t)elves * 2.0 * PI;
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

struct Elf* findOpposite(struct Elf *elf) {
    double_t target = elf->position + PI;
    //printf("opposite of %zu is near %f: ", elf->id, target);
    if (target > 2 * PI) target -= 2 * PI;
    struct Elf *opposite = elf -> next;
    while (1) {
        if (fabs(target - opposite->next->position) < DBL_EPSILON) return opposite->next;
        if (target - opposite->next->position < 0.0 || opposite->next == elf) break;
        opposite = opposite->next;
    }
    return opposite;
}

void removeElf(struct Elf **head, struct Elf *elf) {
    elves--;
    size_t pos = 0;
    if (*head == elf) {
        *head = elf->next;
    }
    struct Elf *temp = *head;
    while (1) {
        temp->position = (double_t)pos++ / (double_t)elves * 2.0 * PI;
        //printf("id: %zu, pos: %f\n", temp->id, temp->position);
        // skip elf that is removed
        if (temp->next == elf) temp->next = elf->next;
        temp = temp->next;
        if (temp == *head) break;
    }
}

size_t solve(struct Elf *head) {
    if (head == NULL) {
        printf("Circle is empty!\n");
        return 0;
    }
    struct Elf *temp = head;
    while (1) {
        if (temp->next == temp) break;  // only one elf remains
        // Any loops within the main loops will slow down the simulation
        struct Elf *opposite = findOpposite(temp);
        //printf("%zu setals from %zu\n", temp->id, opposite->id);
        temp->presents += opposite->presents;
        removeElf(&head, opposite);  // remove opposite and update elves' positions
        temp = temp->next;  // go to next elf
        if (elves % 100 == 0) printf("remaining %zu..\n", elves);
    }

    return temp->id;
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
