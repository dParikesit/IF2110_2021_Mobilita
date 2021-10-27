#include <stdio.h>
#include "wordmachine.h"

boolean endWord;
Word currentWord;

void ignoreBlank() {
/* Mengabaikan satu atau beberapa BLANK
   I.S. : currentChar sembarang 
   F.S. : currentChar ≠ BLANK atau currentChar = MARK */
    while (currentChar == BLANK)
        adv();
}

void startWord(FILE* file) {
/* I.S. : currentChar sembarang 
   F.S. : endWord = true, dan currentChar = MARK; 
          atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */
    start(file);
    ignoreBlank();
    if (currentChar == MARK) {
        endWord = true;
    } else {
        endWord = false;
        copyWord();
    }
}

void advWord() {
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi 
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi, 
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, endWord = true.		  
   Proses : Akuisisi kata menggunakan procedure copyWord */
    ignoreBlank();
    if (currentChar == MARK) {
        endWord = true;
    } else {
        copyWord();
        ignoreBlank();
    }
}

void copyWord() {
/* Mengakuisisi kata, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi kata yang sudah diakuisisi; 
          currentChar = BLANK atau currentChar = MARK; 
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */
    currentWord.length = 0;
    while (currentChar != BLANK && currentChar != MARK) {
        if (currentWord.length < CAPACITY) { // jika lebih akan terpotong
            currentWord.contents[currentWord.length++] = currentChar;
            adv();
        } else
            break;
    }
}