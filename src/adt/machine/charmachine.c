/* File: charmachine.c */
/* Implementasi Character Engine */

#include "charmachine.h"
#include <stdio.h>

char currentChar;
boolean eot;

static FILE * tape;
static int retval;

void start(FILE* file) {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : currentChar adalah karakter pertama pada pita
          Jika currentChar != MARK maka EOP akan padam (false)
          Jika currentChar = MARK maka EOP akan menyala (true) */

	/* Algoritma */
       if (tape != file) { // Avoid set tape if file same
              if (tape != NULL && tape != stdin) { // Close last stream if not null and not stdin
                     close();
              }
              tape = file;
              adv();
       }
}

void startStdin() {
       start(stdin);
}

void adv() {
/* Pita dimajukan satu karakter. 
   I.S. : Karakter pada jendela = currentChar, currentChar != MARK
   F.S. : currentChar adalah karakter berikutnya dari currentChar yang lama, 
          currentChar mungkin = MARK
		      Jika  currentChar = MARK maka EOP akan menyala (true) */
	/* Algoritma */
	retval = fscanf(tape,"%c",&currentChar);
	eot = (currentChar == MARK);
}

void write(char c) {
/* Pita menulis satu karakter. 
   I.S. : Karakter pada jendela = currentChar, currentChar != MARK
   F.S. : currentChar adalah karakter berikutnya dari currentChar yang lama, 
          currentChar mungkin = MARK
		      Jika  currentChar = MARK maka EOP akan menyala (true) */
       /* Algoritma */
	retval = fwrite(&c, sizeof(char), 1, tape);
	eot = (currentChar == MARK);
}

void close() {
/* Pita dikeluarkan dari mesin. */
       /* Algoritma */
       fclose(tape);
       eot = true;
}
