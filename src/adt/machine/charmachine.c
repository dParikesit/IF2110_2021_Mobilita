/* File: charmachine.c */
/* Implementasi Character Engine */

#include "charmachine.h"
#include <stdio.h>

char currentChar;
boolean eot;
FILE_MODE fileMode;

static FILE * tape;
static int retval;

void startCharM(FILE* file, FILE_MODE mode) {
	/* Algoritma */
       // Set tape only if file different or mode changed.
       if (tape != file || fileMode != mode) {
              // Close last stream if not null and not stdin
              if (tape != NULL && tape != stdin) {
                     closeCharM();
              }
              fileMode = mode;
              tape = file;
              eot = false;
              if (mode == READ)
                     advCharM();
       }
}

void advCharM() {
	/* Algoritma */
	retval = fscanf(tape,"%c",&currentChar);
       if (fileMode == STDIN) {
              eot = (currentChar == MARK);
       } else {
              eot = (retval == EOF);
       }
}

void writeCharM(char c) {
       /* Algoritma */
	fwrite(&c, sizeof(char), 1, tape);
       currentChar = c;
}

void closeCharM() {
       /* Algoritma */
       if (fileMode == WRITE) {
              writeCharM(MARK);
       }
       currentChar = '\0';
       fclose(tape);
       eot = true;
       tape = NULL;
}
