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
        GSTATS.returnToSender -= 1;
        break;

    default:
        break;
    }
} 