#include "building.h"
#include "../../include/wrapper.h"

// Mendapatkan referensi bangunan dengan letter tertentu.
Building* getLetterRefBuilding(char letter) {
    // TODO: get the building list from _gm.map.building, return to pointer
    //       of a building where building.letter = letter.
    return NULL;
}

/* Menuliskan building ke dalam stream.
   I.S. Building terdefinisi, stream terdefinisi, fileMode = WRITE.
   F.S. Menuliskan building ke dalam stream. */
void SerializeBuilding(Building* b) {
    writeChar(b->letter);
    // TODO: uncomment this if pos declared.
    //writeInt(b->pos.x);
    //writeInt(b->pos.y);
    writeMark();
}

/* Membaca stream dan parse ke Building.
   I.S. Building sembarang, stream terdefinisi, fileMode = WRITE.
   F.S. Menginisialisasi Building dengan data di stream. */
void DeserializeBuilding(Building* b) {
    b->letter = readChar();
    // TODO: uncomment this if pos declared.
    //Point p;
    //CreatePoint(p);
    //p.x = readInt();
    //p.y = readInt();
    //b->pos = p;
}
