// File: ability.c

#include <stdio.h>
#include "ability.h"

void addAbility(AbilityType ability){
    // Add ability to stats for durated ability
    switch (ability)
    {
    case SPEED_BOOST:
        GSTATS.speedBoostDuration = 5;
        GTIME.isHalt = true;
        GTIME.deltaTime = 1;
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
        break;

    default:
        break;
    }
}

void removeAbility(AbilityType ability) {
    // Remove ability from stats for durated ability
    switch (ability) {
        case SPEED_BOOST:
            GSTATS.speedBoostDuration = 0;
            GTIME.isHalt = false;
            printf("Ability speed boost hilang karena ada heavy item di bag\n");
            break;
    }
}

void retAbility(){
    Item* now;
    now = getCurrentItem();
    if (now == NULL)
    {
        printf("Tidak ada barang yang bisa di return.\n");
    }
    else
    {
        if (now->type == VIP)
        {
            printf("Ability ini tidak dapat diaktifkan untuk pesanan VIP Item.\n");
        } else {
            GSTATS.returnToSender -= 1;
            if (now->type == PERISHABLE)
                now->currentDuration = now->maxDuration;
            printf("Berhasil mengembalikan %s!\n", getItemTypeName(now->type));
            insertLastListLinked(&GSTATS.toDoList, now);
            deleteLastListLinked(&GSTATS.inProgressList, &now);
            pop(&GSTATS.bag, &now);
            if (GSTATS.senterPengecil) {
                GSTATS.senterPengecil = false;
                printf("Senter pengecil habis karena item sudah di return.\n");
            }
        }
    }
}
