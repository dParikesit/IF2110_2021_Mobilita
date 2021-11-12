// File: ability.c

#include <stdio.h>
#include "ability.h"

void addAbility(AbilityType ability){
    // Add ability to stats for durated ability
    switch (ability)
    {
    case SPEED_BOOST:
        GSTATS.speedBoostDuration = 5;
        break;

    case RETURN_TO_SENDER:
        GSTATS.returnToSender += 1;
        break;

    default:
        break;
    }
}

void applyAbility(AbilityType ability){
    // Apply effect of the selected ability
    switch (ability)
    {
    case INCREASE_CAPACITY:
        GSTATS.bagCapEff += 1;
        break;

    case RETURN_TO_SENDER:
        retAbility();
        GSTATS.returnToSender -= 1;
        break;

    default:
        break;
    }
}

void retAbility(){
    Item* now;
    now = getCurrentItem();
    if (now == NULL)
    {
        printf("Tidak ada barang yang bisa di return");
    }
    else if (now != NULL)
    {
        if (now->type == VIP)
        {
            printf("Ability ini tidak dapat diaktifkan untuk pesanan VIP Item.");
        }
        else{
            if (now->type == PERISHABLE)
                {
                    now->currentDuration = now->maxDuration;
                }
            insertLastLinkedList(&GSTATS.toDoList, now);
            pop(&GSTATS.bag, &now);
        
            if (GSTATS.senterPengecil) {
                GSTATS.senterPengecil = false;
                printf("Senter pengecil habis karena item sudah di return.");
            }
        }
    }
}