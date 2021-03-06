// File: ability.h

#ifndef ABILITY_H
#define ABILITY_H

#include "../item/item.h"
#include "../../adt/listlinked/list_linked.h"
#include "../../include/wrapper.h"

typedef enum abilitytype {
    SPEED_BOOST = 0,
    INCREASE_CAPACITY = 1,
    RETURN_TO_SENDER = 2,
} AbilityType;
void addAbility(AbilityType ability); // Add ability to stats for durated ability
void applyAbility(AbilityType ability); // Apply effect of the selected ability
void retAbility(); // Return to sender ability implementation
void removeAbility(AbilityType ability); // Remove ability from stats for durated ability
#endif
