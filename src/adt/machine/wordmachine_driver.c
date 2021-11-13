// Build with
// gcc *.c -o wordmachine
#include "wordmachine.h"

int main() {
    printf("Please say something, i will get the first word and echo it back.\n");
    startWordM(stdin, STDIN);
    advWordM();
    printf("Fantastic, here's the word echo: %s", currentWord.contents);
    printf("\nEnd of STDIN (newline).\nBEGIN FILE WRITE\n");
    FILE *f = fopen("test.txt", "w");
    startWordM(f, WRITE);
    printf("Menuliskan 'aku suk4 dia. meski begitu, dia !suka aku'\n");
    writeWordM("aku");writeWordM("suk4");writeWordM("dia.");
    writeWordM("meski");writeWordM("begitu,");writeWordM("dia");
    writeWordM("!suka");writeWordM("aku");
    printf("Mengakhiri file dengan baris baru.\n");
    printf("File berhasil ditulis: test.txt\n");
    printf("BEGIN FILE READ\n");
    printf("Ini hasil dari test.txt: ");
    closeCharM();
    f = fopen("test.txt", "r");
    startWordM(f, READ);
    copyWordM();
    while (!endWord) {
        printf("%s ", currentWord.contents);
        advWordM();
    }
    printf("\nFIN. ========");
    return 0;
}