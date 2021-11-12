// Run with:
// gcc stream_driver.c stream.c ../../adt/machine/charmachine.c ../../adt/machine/wordmachine.c ../../adt/point/point.c -o main
#include "stream.h"
#include "../../adt/point/point.h"

int main() {
    // KAMUS LOKAL
    char* s;
    char c;
    FILE* f;
    Point p;
    // ALGORITMA
    printf("BEGIN FILE READ 1\n");
    f = fopen("test.txt", "r");
    if (f == NULL) {
        printf("File 1 not found!\n");
    } else {
        initStream(f, READ);
        while(!endWord) {
            printf("%s ", readWord());
        }
        printf("\n");
    }
    printf("%s", currentWord.contents);
    printf("BEGIN STDIN\n");
    initStdin();
    printf("Masukkan titik X: ");
    int x = readInt();
    printf("Masukkan titik Y: ");
    int y = readInt();
    p = MakePoint(x, y);
    printf("Titik: "); TulisPoint(p);
    printf("\nSiapa nama kamu? "); s = readLine();
    printf("Namamu: %s\n", s);
    printf("Compare 'c bad js good' dengan: "); s = readLine();
    printf("Masukan kamu %s dengan 'c bad js good'\n", (isEqualString(s, "c bad js good") ? "SAMA" : "BEDA"));
    printf("BEGIN STDIN\n");
    initStdin();
    printf("Insert kata: "); s = readWord();
    printf("Kata kamu: %s\n", s);
    printf("Insert karakter: "); c = readChar();
    printf("Karakter kamu: %c\n", c);
    printf("BEGIN FILE READ 2\n");
    f = fopen("bool.txt", "r");
    if (f == NULL) {
        printf("File not found!\n");
    } else {
        initStream(f, READ);
        while(!endWord) {
            printf("%s ", readWord());
        }
        printf("\n");
    }
    printf("BEGIN FILE WRITE 1\n");
    f = fopen("bruh.txt", "w");
    initStream(f, WRITE);
    writeBoolean(true);
    writeMark();
    writeWord("kenapah");
    writeChar('!');
    writeMark();
    writeInt(41);
    writeWord("why?");
    writeMark();
    writeInt(55);
    printf("BEGIN FILE READ 3\n");
    f = fopen("bruh.txt", "r");
    initStream(f, READ);
    printf("%d", readBoolean());
    printf(" - %s", readWord());
    printf(" - %c", readChar());
    printf(" - %d", readInt());
    printf(" - %s", readWord());
    printf(" - %d\n", readInt());
    printf("BEGIN STDIN\n");
    initStdin();
    printf("Masukkan bilangan: ");
    printf("Bilanganmu: %d\n", readInt());
    boolean b;
    do {
        printf("Masukkan boolean (Y/N): ");
        b = readBoolean();
        if (b == 2)
            printf("Masukan tidak valid.\n");
    } while(b == 2);
    printf("Booleanmu: %u\n", b);
    return 0;
}