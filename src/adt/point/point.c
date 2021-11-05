/* File: point.c */
/* *** Implementasi ABSTRACT DATA TYPE Point *** */

#include "point.h"

#include <math.h>
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

/* *** Kelompok menentukan di mana P berada *** */
boolean IsOrigin(Point P) {
  /* Menghasilkan true jika P adalah titik origin */
  return ((Absis(P) == 0) && (Ordinat(P) == 0));
}
boolean IsOnSbX(Point P) {
  /* Menghasilkan true jika P terletak Pada sumbu X */
  return (Ordinat(P) == 0);
}
boolean IsOnSbY(Point P) {
  /* Menghasilkan true jika P terletak pada sumbu Y */
  return (Absis(P) == 0);
}

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */
Point NextX(Point P) {
  /* Mengirim salinan P dengan absis ditambah satu */
  Point Pnew;
  Pnew = MakePoint(Absis(P) + 1, Ordinat(P));

  return Pnew;
}
Point NextY(Point P) {
  /* Mengirim salinan P dengan ordinat ditambah satu */
  Point Pnew;
  Pnew = MakePoint(Absis(P), Ordinat(P) + 1);

  return Pnew;
}
Point PlusDelta(Point P, int deltaX, int deltaY) {
  /* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya
 * adalah Ordinat(P) + deltaY */
  Point Pnew;
  Pnew = MakePoint(Absis(P) + deltaX, Ordinat(P) + deltaY);

  return Pnew;
}
float Jarak0(Point P) {
  /* Menghitung jarak P ke (0,0) */
  return sqrtf(pow(Absis(P), 2) + pow(Ordinat(P), 2));
}
float Panjang(Point P1, Point P2) {
  /* Menghitung panjang garis yang dibentuk P1 dan P2 */
  /* Perhatikanlah bahwa di sini spec fungsi kurang baik sebab menyangkut ADT
   * Garis. */
  double x, y;
  x = fabs(Absis(P1) - Absis(P2));
  y = fabs(Ordinat(P1) - Ordinat(P2));

  return sqrt(pow(x, 2) + pow(y, 2));
}
void Geser(Point *P, int deltaX, int deltaY) {
  /* I.S. P terdefinisi */
  /* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
  Absis(*P) += deltaX;
  Ordinat(*P) += deltaY;
}
void GeserKeSbX(Point *P) {
  /* I.S. P terdefinisi */
  /* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
  /* Proses : P digeser ke sumbu X. */

  Ordinat(*P) = 0;
}
void GeserKeSbY(Point *P) {
  /* I.S. P terdefinisi*/
  /* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
  /* Proses : P digeser ke sumbu Y. */

  Absis(*P) = 0;
}