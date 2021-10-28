#ifndef _BUILDING_h
#define _BUILDING_h

typedef struct Building {
    // Karakter Bangunan
    char letter;
    // Posisi Bangunan
    // TODO: Uncomment this if Point declared.
    //Point pos;
} Building;

void CreateBuilding(Building* b, char letter); // Create new building

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

#endif