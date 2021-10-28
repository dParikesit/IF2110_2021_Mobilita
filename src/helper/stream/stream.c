#include <stdlib.h>
#include "stream.h"

static char* _inp = NULL;

void initStream(FILE* file, FILE_MODE mode) {
    startWordM(file, mode);
    if (_inp == NULL)
        _inp = (char*)malloc(sizeof(char) * CHAR_CAP);
}

void initStdin() {
    initStream(stdin, STDIN);
}

void closeStream() {
    endWord = true;
    closeCharM();
}

boolean isEqualString(char* a, char* b) {
    // KAMUS LOKAL
    int i;
    // ALGORITMA
    i = 0;
    while (a[i] != '\0' && b[i] != '\0') { // Selama salah satunya bukan karakter '\0' (mark)...
        // ...lakukan komparasi a[i] dan b[i]. Jika tidak sama, kembalikan false.
        if (a[i] != b[i]) {
            return false;
        }
        i++;
    }
    // Jika keduanya sama (karakter '\0'), kembalikan true. Jika tidak, kembalikan false.
    if (a[i] == b[i]) {
        return true;
    } else {
        return false;
    }
}

/* Mengabaikan kata dari karakter BLANK pertama hingga MARK.
   I.S. : Stream diinisialisasi dengan stdin.
   F.S. : currentChar = MARK dan EOT */
static void _ignoreUntilMark() {
    while (currentChar != MARK)
        advCharM();
}

/* Advance mesin kata hingga mendapatkan satu kata (jika ada).
   I.S. : Stream sudah diinisialisasi.
   F.S. : Mendapatkan satu kata dari stream.
          Jika tape merupakan stdin, flush input (ignore until mark).
          Jika tidak ada kata namun tape berupa stdin, ulangi hingga ada kata.
          Jika tidak ada kata namun file sudah EOF, set konten currentWord menjadi '\0'. */
static void _advUntilWord() {
    if (fileMode == STDIN) {
        do {
            eot = false;
            advWordM();
            _ignoreUntilMark();
        } while (emptyTape);
    } else {
        advWordM();
        if (emptyTape) {
            currentWord.length = 1;
            currentWord.contents[0] = '\0';
        }
    }
}

char* readLine() {
    // KAMUS LOKAL
    // ALGORITMA
    do {
        eot = false;
        ignoreBlankWordM();
        if (eot) {
            endWord = true;
            emptyTape = true;
            currentWord.length = 1;
            currentWord.contents[0] = '\0';
        } else {
            emptyTape = false;
            currentWord.length = 0;
            while ((!isBlank(currentChar) || currentChar == ' ') && !eot) {
                if (currentWord.length < CHAR_CAP) { // jika lebih akan terpotong
                    currentWord.contents[currentWord.length++] = currentChar;
                }
                advCharM();
            }
            currentWord.contents[currentWord.length++] = '\0';
            ignoreBlankWordM();
            endWord = eot;
        }
    } while (emptyTape);
    return currentWord.contents;
}

char* readWord() {
    // KAMUS LOKAL
    // ALGORITMA
    _advUntilWord();
    return currentWord.contents;
}

char readChar() {
    // KAMUS LOKAL
    // ALGORITMA
    _advUntilWord();
    return currentWord.contents[0];
}

/* Membaca integer dari stream.
   Prekondisi: endWord = false dan fileMode = READ */
int readInt() {
    // KAMUS LOKAL
    int res;
    // ALGORITMA
    _advUntilWord();
    sscanf(currentWord.contents, "%d", &res);
    return res;
}

/* Membaca boolean (unsigned char) dari stream. Prekondisi: endWord = false dan fileMode = READ */
boolean readBoolean() {
    // KAMUS LOKAL
    boolean res;
    // ALGORITMA
    _advUntilWord();
    if (currentWord.contents[0] == 'Y') {
        res = true;
    } else if (currentWord.contents[0] == 'N') {
        res = false;
    } else {
        res = 2;
    }
    return res;
}

/* Menuliskan character array ke stream.
   I.S. : endWord = false dan fileMode = WRITE
   F.S. : Menuliskan karakter BLANK dan character array value ke stream */
void writeWord(char* value) {
    // KAMUS LOKAL
    // ALGORITMA
    writeWordM(value);
}

/* Menuliskan karakter ke stream.
   I.S. : endWord = false dan fileMode = WRITE
   F.S. : Menuliskan karakter BLANK dan karakter value ke stream */
void writeChar(char value) {
    // KAMUS LOKAL
    // ALGORITMA
    _inp[0] = value;
    _inp[1] = '\0';
    writeWordM(_inp);
}

/* Menuliskan MARK ke stream.
   I.S. : endWord = false dan fileMode = WRITE
   F.S. : Menuliskan karakter MARK ke stream */
void writeMark() {
    writeCharM(MARK);
}

/* Menuliskan integer ke stream.
   I.S. : endWord = false dan fileMode = WRITE
   F.S. : Menuliskan karakter BLANK dan integer value ke stream */
void writeInt(int value) {
    // KAMUS LOKAL
    // ALGORITMA
    sprintf(_inp, "%d", value);
    writeWordM(_inp);
}

/* Menuliskan boolean (unsigned char) ke stream.
   I.S. : endWord = false dan fileMode = WRITE
   F.S. : Menuliskan karakter BLANK dan boolean (unsigned char) value ke stream */
void writeBoolean(boolean value) {
    // KAMUS LOKAL
    // ALGORITMA
    writeWordM(value ? "Y" : "N");
}
