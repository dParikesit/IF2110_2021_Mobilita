// Run with:
// gcc *.c -o main

#include "prioqueue.h"
#include "../../object/building/building.h"
#include <stdio.h>

int main() {
    PrioQueue p;
    CreatePrioQueue(&p);
    int i, N;
    Item* item;
    Building b1, b2;
    b1.letter = 'A';
    b2.letter = 'B';
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        item = (Item*)malloc(sizeof(Item));
        scanf("%d %c", &item->timePickUp, &item->type);
        if (item->type == PERISHABLE) {
            scanf("%d", &item->maxDuration);
            item->currentDuration = item->maxDuration;
        }
        item->pickUp = &b1;
        item->dropOff = &b2;
        enqueue(&p, item);
    }
    printf("Ini item yang telah terurut:\n");
    for (int i = 0; i < N; i++) {
        dequeue(&p, &item);
        printf(
            "%c (Pickup %c -> Drop Off %c)",
            item->type,
            item->pickUp->letter,
            item->dropOff->letter
        );
        if (item->type == PERISHABLE) {
            printf(" [%ds/%ds]", item->currentDuration, item->maxDuration);
        }
        printf("\n");
    }
    return 0;
}