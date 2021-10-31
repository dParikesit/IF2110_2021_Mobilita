#ifndef MAP_H
#define MAP_H

#include "../../adt/matrix/matrix.h"
#include "../../adt/listdin/listdin.h"
#include "../../include/boolean.h"
#include "../../object/building/building.h"
#include "../gamemanager/gamemanager.h"
#include <stdio.h>

typedef struct {
	Matrix path; // Adjacency Matrix building relationship
	Matrix loc; // Adjacency Matrix representation of path and building
	ListDin buildingList;
	ListDin temp;
	Building hq; // Headquarter building. Should have letter ‘8’.
	Point mobitaPos;
} Map;

#define HQ(map) (map).hq
#define MOBITAPOS(map) (map).mobitaPos
#define BUILDINGLIST(map) (map).buildingList
#define LOC(map) (map).loc
#define PATH(map) (map).path
#define TEMP(map) (map).temp

boolean isInHQ();
// Check if mobitaPos in hqPos
void navigateAndMoveMobita();
// Show reachable destination from current position and move player to desired destination.
void displayMap(); // Display map to stdin
void initMap(); // To be called after deserialization. Initialize map: compute loc, reset mobitaPos (to hq point).
void SerializeMap(Map* s, FILE* inp);
void DeserializeMap(Map* s, FILE* res); // loc should be computed 

void displayReachableDestination();

#endif