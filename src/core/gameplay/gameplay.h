#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "../../include/boolean.h"

void doMoveplayer();
/*
I.S  
*/
void doPickUp(); 
// Put getPickUpItem into the bag

void doDropOff(boolean hasVIPItem); 
// Pop bag and remove currentItem in progress list

int countTimeAddition(); 
// Count how much time should be added



#endif