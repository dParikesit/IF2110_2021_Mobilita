#ifndef STREAM_h
#define STREAM_h

#include <stdio.h>
#include "../../adt/machine/wordmachine.h"

// Lifecycle
/* Memulai stream baru.
   I.S. : currentChar sembarang 
   F.S. : Jika fileMode = READ, lakukan pembacaan:
          - endWord = true, dan currentChar = MARK; 
          - atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
          - currentChar karakter pertama sesudah karakter terakhir kata */
void initStream(FILE* file, FILE_MODE mode);
/* Membaca stream dari standard input.
   I.S. : currentChar sembarang 
   F.S. : Sama seperti initStream */
void initStdin();
/* Pita dikeluarkan dari mesin dan trigger EOP.
   I.S. : Terdapat pita dalam mesin (pita bukan stdin).
   F.S. : Mengeluarkan pita (menutup stream) dan menyalakan EOP.
          Jika mode write, menuliskan MARK ke dalam file terlebih dahulu. */
void closeStream();

// Helper
/* Mengembalikan true jika string a sama dengan string b. */
boolean isEqualString(char* a, char* b);

// Reader
/* Membaca baris (karakter hingga newline) dari stream
   tanpa mengabaikan karakter spasi.
   Prekondisi: endWord = false dan fileMode = STDIN */
char* readLine();
/* Membaca 1 kata dari stream.
   Prekondisi: endWord = false dan fileMode = READ */
char* readWord();
/* Membaca karakter dari stream.
   Prekondisi: endWord = false dan fileMode = READ */
char readChar();
/* Membaca integer dari stream.
   Prekondisi: endWord = false dan fileMode = READ */
int readInt();
/* Membaca boolean (unsigned char) dari stream.
   Prekondisi: endWord = false dan fileMode = READ */
boolean readBoolean();

// Writer
/* Menuliskan kalimat 
   I.S. : endWord = false dan fileMode = WRITE
   F.S. : Menuliskan karakter BLANK dan character array value ke stream */
void writeWord(char* value);
/* Menuliskan karakter ke stream.
   I.S. : endWord = false dan fileMode = WRITE
   F.S. : Menuliskan karakter BLANK dan karakter value ke stream */
void writeChar(char value);
/* Menuliskan integer ke stream.
   I.S. : endWord = false dan fileMode = WRITE
   F.S. : Menuliskan karakter BLANK dan integer value ke stream */
void writeInt(int value);
/* Menuliskan boolean (unsigned char) ke stream.
   I.S. : endWord = false dan fileMode = WRITE
   F.S. : Menuliskan karakter BLANK dan boolean (unsigned char) value ke stream */
void writeBoolean(boolean value);
/* Menuliskan MARK ke stream.
   I.S. : endWord = false dan fileMode = WRITE
   F.S. : Menuliskan karakter MARK ke stream */
void writeMark();

#endif