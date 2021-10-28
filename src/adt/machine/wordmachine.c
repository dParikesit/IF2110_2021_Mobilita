#include <stdio.h>
#include "wordmachine.h"

boolean endWord;
boolean emptyTape;
Word currentWord;

void ignoreBlankWordM() {
    while (isBlank(currentChar) && !eot)
        advCharM();
}

void startWordM(FILE* file, FILE_MODE mode) {
    startCharM(file, mode);
    if (mode == READ) {
        ignoreBlankWordM();
        endWord = eot;
    }
}

void advWordM() {
    ignoreBlankWordM();
    if (eot) {
        endWord = true;
        emptyTape = true;
    } else {
        emptyTape = false;
        copyWordM();
        ignoreBlankWordM();
    }
}

void copyWordM() {
    currentWord.length = 0;
    while (!isBlank(currentChar) && !eot) {
        if (currentWord.length < CHAR_CAP) { // jika lebih akan terpotong
            currentWord.contents[currentWord.length++] = currentChar;
        }
        advCharM();
    }
    currentWord.contents[currentWord.length++] = '\0';
}

void writeWordM(char* word) {
    // KAMUS LOKAL
    int i;
    char c;
    // ALGORITMA
    writeCharM(' ');
    i = 0;
    c = word[i];
    currentWord.length = 0;
    while (c != '\0') {
        if (currentWord.length < CHAR_CAP) { // jika lebih akan terpotong
            if (!isBlank(c)) {
                currentWord.contents[currentWord.length++] = c;
                writeCharM(c);
            }
            i++;
            c = word[i];
        }
    }
    currentWord.contents[currentWord.length++] = '\0';
}