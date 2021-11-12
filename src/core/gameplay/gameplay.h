#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "../../include/boolean.h"

void doMovePlayer();
/*
I.S  
*/
void doPickUp(); 
// Put getPickUpItem into the bag

void doDropOff(); 
// Pop bag and remove currentItem in progress list

int countTimeAddition(); 
// Count how much time should be added

void checkEndGame();
// Check if the game is ended

#endif