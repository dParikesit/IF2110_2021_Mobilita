#ifndef _BUILDING_h
#define _BUILDING_h

#include "../../adt/point/point.h"

typedef struct Building {
    // Posisi Bangunan
    Point pos;
    // Karakter Bangunan
    char letter;
} Building;

#define LETTER(build) (build).letter
#define POS(build) (build).pos

void CreateBuilding(Building* b, char letter); // Create new building

// Operator equal, mengembalikan true jika karakter building sama dan posisi sama
boolean isEqualBuilding(Building b1, Building b2);

// Mendapatkan referensi bangunan dengan letter tertentu.
Building* getLetterRefBuilding(char letter);

// Serialization Guide
/* Format:
   "<letter> <pos.x> <pos.y>\n"
*/

/* Menuliskan building ke dalam stream.
   I.S. Building terdefinisi, stream terdefinisi, fileMode = WRITE.
   F.S. Menuliskan building ke dalam stream. */
void SerializeBuilding(Building* b);
/* Membaca stream dan parse ke Building.
   I.S. Building sembarang, stream terdefinisi, fileMode = WRITE.
   F.S. Menginisialisasi Building dengan data di stream. */
void DeserializeBuilding(Building* b);

void displayBuilding(Building* b);

#endif