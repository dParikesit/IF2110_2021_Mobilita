#ifndef _BUILDING_h
#define _BUILDING_h
#include "../../include/wrapper.h"

typedef struct {
    char letter;
} Building;

void CreateBuilding(Building* b, char letter); // Create new building

#endif