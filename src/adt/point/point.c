/* File: point.c */
/* *** Implementasi ABSTRACT DATA TYPE Point *** */

#include "point.h"

#include <stdio.h>

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk Point *** */
Point MakePoint(int X, int Y) {
  /* Membentuk sebuah Point dari komponen-komponennya */
  Point p;
  Absis(p) = X;
  Ordinat(p) = Y;

  return p;
}

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */
void BacaPoint(Point *P) {
  /* I.S. Sembarang */
  /* F.S. P terdefinisi */
  /* Membaca nilai absis dan ordinat dari keyboard dan membentuk
   Point P berdasarkan dari nilai absis dan ordinat tersebut */
  /* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */

  int x, y;
  scanf("%d %d", &x, &y);
  *P = MakePoint(x, y);
}
void TulisPoint(Point P) {
  /* I.S. P terdefinisi */
  /* F.S. P tertulis di layar dengan format "(X,Y)" */
  /* Nilai P ditulis ke layar dengan format "(X,Y)"
   tanpa spasi, enter, atau karakter lain di depan, belakang,
   atau di antaranya
*/

  printf("(%d,%d)", Absis(P), Ordinat(P));
}

/* *** Kelompok operasi relasional terhadap Point *** */
boolean EQPoint(Point P1, Point P2) {
  /* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
  return ((Absis(P1) == Absis(P2)) && (Ordinat(P1) == Ordinat(P2)));
}
