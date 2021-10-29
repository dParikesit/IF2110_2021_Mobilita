/* File: charmachine.h */
/* Definisi Character Engine */

#ifndef CHAR_ENGINE_H
#define CHAR_ENGINE_H

#include <stdio.h>
#include "../../include/boolean.h"

#define MARK '\n'
// DEFINISI MARK UNTUK STDIN
// Definisi MARK untuk file adalah EOF

typedef enum FILE_MODE {
   READ = 0,
   WRITE = 1,
   STDIN = 2
} FILE_MODE;

/* Char Engine State */
extern char currentChar;
extern boolean eot;
extern FILE_MODE fileMode;

void startCharM(FILE* file, FILE_MODE mode);
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca/ditulis sesuai mode.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : Mengeluarkan pita sebelumnya jika ada dan file != stdin serta set fileMode = mode.
          Jika mode READ, membaca pita hingga currentChar adalah karakter pertama pada pita:
          - Jika currentChar != MARK maka EOP akan padam (false)
          - Jika currentChar = MARK maka EOP akan menyala (true) */

void advCharM();
/* Pita dimajukan satu karakter. 
   I.S. : Karakter pada jendela = currentChar, currentChar != MARK, fileMode = READ.
   F.S. : currentChar adalah karakter berikutnya dari currentChar yang lama, 
          currentChar mungkin = MARK
          Jika currentChar = MARK, atau tape sudah EOF, atau saat tape stdin currentChar
          yang didapat adalah newline, maka EOP akan menyala (true) */

void writeCharM(char c);
/* Pita menulis satu karakter. 
   I.S. : Karakter pada jendela = currentChar, currentChar != MARK, fileMode = WRITE.
   F.S. : currentChar adalah karakter berikutnya dari currentChar yang lama, 
          currentChar mungkin = MARK
	       Jika currentChar = MARK maka EOP akan menyala (true) */

void closeCharM();
/* Pita dikeluarkan dari mesin dan trigger EOP.
   I.S. : Terdapat pita dalam mesin (pita bukan stdin) dan tidak EOP.
   F.S. : Mengeluarkan pita (menutup stream), tape = NULL, dan menyalakan EOP.
          Jika mode write, menuliskan MARK ke dalam file terlebih dahulu. */

#endif