#include "building.h"
#include "../../include/wrapper.h"

// Operator equal, mengembalikan true jika karakter building sama dan posisi sama
boolean isEqualBuilding(Building b1, Building b2) {
    return (b1.letter == b2.letter && EQPoint(b1.pos, b2.pos));
}

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
    writeInt(b->pos.X);
    writeInt(b->pos.Y);
    writeMark();
}

/* Membaca stream dan parse ke Building.
   I.S. Building sembarang, stream terdefinisi, fileMode = WRITE.
   F.S. Menginisialisasi Building dengan data di stream. */
void DeserializeBuilding(Building* b) {
    char let = readChar();
    int x = readInt();
    int y = readInt();

    b->letter = let;
    b->pos = MakePoint(x,y);
}
void displayBuilding(Building* elmt){
    printf("%c ", LETTER(*elmt));
    TulisPoint(POS(*elmt));
}