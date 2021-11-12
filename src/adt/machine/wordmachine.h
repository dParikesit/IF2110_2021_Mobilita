/* File: wordmachine.h */
/* Definisi Word Engine */

#ifndef WORD_ENGINE_H
#define WORD_ENGINE_H

#include "charmachine.h"

#define CHAR_CAP 150

// Blank character is a non-printable character + space (0x20) in ASCII
#define isBlank(x) ((x < 0x21 || x > 0x7e)) 

typedef struct Word {
   char contents[CHAR_CAP+1]; /* container penyimpan kata, indeks yang dipakai [0..CHAR_CAP-1] dengan CHAR_CAP untuk '\0' */
   int length;
} Word;

/* Word Engine State */
extern boolean emptyTape;
extern boolean endWord;
extern boolean startMark;
extern Word currentWord;

/* Mengabaikan satu atau beberapa BLANK
   I.S. : currentChar sembarang 
   F.S. : currentChar bukan BLANK atau currentChar = MARK */
void ignoreBlankWordM();

/* I.S. : currentChar sembarang 
   F.S. : Jika fileMode = READ, ignore blank, dengan salah satu final state berikut:
          - endWord = true, dan currentChar = MARK;
          - endWord = false, currentWord tidak terdefinisi
            currentChar karakter pertama dari kata yang akan diambil */
void startWordM(FILE* file, FILE_MODE mode);

/* I.S. : fileMode = READ. currentChar adalah karakter pertama kata yang akan diakuisisi.
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi, 
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, endWord = true.		  
   Proses : Akuisisi kata menggunakan procedure copyWord */
void advWordM();

/* Mengakuisisi kata, menyimpan dalam currentWord
   I.S. : fileMode = READ. currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi kata yang sudah diakuisisi, diakhiri dengan '\0'.
          currentChar is BLANK atau currentChar = MARK; 
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi CHAR_CAP, maka sisa kata terpotong */
void copyWordM();

/* Mengakuisisi baris (kata hingga newline) dengan tidak mengabaikan karakter spasi,
   menyimpan dalam currentWord.
   I.S. : fileMode = READ. currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi baris yang sudah diakuisisi, diakhiri dengan '\0'
          serta dapat berisi karakter spasi.
          currentChar is BLANK atau currentChar = MARK; 
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi CHAR_CAP, maka sisa kata terpotong */
void copyLineWordM();

/* Menulis kata, menyimpan dalam currentWord.
   I.S. : fileMode = WRITE
   F.S. : Menuliskan karakter spasi (" ") kemudian kata word dengan skip karakter BLANK.
          currentWord = word, currentChar = karakter terakhir dari word yang bukan BLANK.
          Jika panjang kata melebihi CHAR_CAP, maka sisa kata tidak akan ditulis */
void writeWordM(char* word);

#endif
