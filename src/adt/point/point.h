/* File: point.h */
/* *** Definisi ABSTRACT DATA TYPE Point *** */

#ifndef POINT_H
#define POINT_H

#include "../../include/boolean.h"
typedef struct {
  int X; /* absis   */
  int Y; /* ordinat */
} Point;

/* *** Notasi Akses: Selektor Point *** */
#define Absis(P) (P).X
#define Ordinat(P) (P).Y

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk Point *** */
Point MakePoint(int X, int Y);
/* Membentuk sebuah Point dari komponen-komponennya */

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */
void BacaPoint(Point *P);
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk
   Point P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2
   akan membentuk Point <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
void TulisPoint(Point P);
/* Nilai P ditulis ke layar dengan format "(X,Y)"
   tanpa spasi, enter, atau karakter lain di depan, belakang,
   atau di antaranya
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di
   belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */

/* *** Kelompok operasi relasional terhadap Point *** */
boolean EQPoint(Point P1, Point P2);
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
boolean NEQPoint(Point P1, Point P2);
/* Mengirimkan true jika P1 tidak sama dengan P2 */

/* *** Kelompok menentukan di mana P berada *** */
boolean IsOrigin(Point P);
/* Menghasilkan true jika P adalah titik origin */
boolean IsOnSbX(Point P);
/* Menghasilkan true jika P terletak Pada sumbu X */
boolean IsOnSbY(Point P);
/* Menghasilkan true jika P terletak pada sumbu Y */

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */
Point NextX(Point P);
/* Mengirim salinan P dengan absis ditambah satu */
Point NextY(Point P);
/* Mengirim salinan P dengan ordinat ditambah satu */
Point PlusDelta(Point P, int deltaX, int deltaY);
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya
 * adalah Ordinat(P) + deltaY */

float Jarak0(Point P);
/* Menghitung jarak P ke (0,0) */
float Panjang(Point P1, Point P2);
/* Menghitung panjang garis yang dibentuk P1 dan P2 */
/* Perhatikanlah bahwa di sini spec fungsi kurang baik sebab menyangkut ADT
 * Garis. */
void Geser(Point *P, int deltaX, int deltaY);
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
void GeserKeSbX(Point *P);
/* I.S. P terdefinisi */
/* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
/* Proses : P digeser ke sumbu X. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */
void GeserKeSbY(Point *P);
/* I.S. P terdefinisi*/
/* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
/* Proses : P digeser ke sumbu Y. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */

#endif