#ifndef MAP_H
#define MAP_H

#include "../../adt/matrix/matrix.h"
#include "../../adt/listdin/listdin.h"
#include "../../include/boolean.h"
#include "../../object/building/building.h"
#include <stdio.h>

typedef struct {
	Matrix path; // Adjacency Matrix building relationship
	Matrix loc; // Adjacency Matrix representation of path and building
	ListDin buildingList;
	ListDin temp;
	Building hq; // Headquarter building. Should have letter ‘8’.
	Building* mobitaPos;
} Map;

#define HQ GMAP.hq
#define MOBITAPOS GMAP.mobitaPos
#define BUILDINGLIST GMAP.buildingList
#define LOC GMAP.loc
#define PATH GMAP.path
#define TEMP GMAP.temp

boolean isInHQ();
// Check if mobitaPos in hqPos

boolean navigateAndMoveMobita(boolean fromPintuKemanaSaja);
// I.S. Map terdefinisi
// F.S. Mobita berpindah tempat sesuai input user

void displayMap();
// I.S. Map terdefinisi
// F.S. Map ditampilkan ke layar 

void initMap(int rowInput, int colInput); // To be called after deserialization. Initialize map: compute loc, reset mobitaPos (to hq point).
// I.S. sembarang
// F.S. terdefinisi Map dengan ukuran sesuai input baris dan kolom

void SerializeMap();
// I.S. Map terdefinisi
// F.S. Map dituliskan ke file sesuai dengan input user

void DeserializeMap(); // loc should be computed 
// I.S. Sembarang
// F.S. Map dibaca dari input file konfigurasi

int displayReachableDestination();
// Mengembalikan banyaknya building yang dapat dicapai oleh mobita dan menampilaknnya ke layar

void addBuildingToLoc(Building* elmt);

boolean isMobitaThere(Building* elmt);

boolean isLetterInReachable(char letter);

void updateReachable();

#endif