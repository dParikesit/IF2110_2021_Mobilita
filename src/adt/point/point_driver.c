// File point_driver.c
// Berisi contoh penggunaan adt point

#include <stdio.h>

#include "point.h"

int main() {
  Point p1, p2;

  /* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */
  printf("Masukkan p1 ");
  BacaPOINT(&p1);
  TulisPOINT(p1);
  printf("\n");

  printf("Masukkan p2 ");
  BacaPOINT(&p2);
  TulisPOINT(p2);
  printf("\n \n");

  /* *** Kelompok operasi relasional terhadap POINT *** */
  if (EQ(p1, p2)) {
    printf("EQ true \n");
  } else {
    printf("EQ false \n");
  }

  if (NEQ(p1, p2)) {
    printf("NEQ true \n");
  } else {
    printf("NEQ false \n");
  }

  printf("\n");

  /* *** Kelompok menentukan di mana P berada *** */
  if (IsOrigin(p1)) {
    printf("IsOrigin true \n");
  } else {
    printf("IsOrigin false \n");
  }

  if (IsOnSbX(p2)) {
    printf("IsOnSbX true \n");
  } else {
    printf("IsOnSbX false \n");
  }

  if (IsOnSbY(p2)) {
    printf("IsOnSbY true \n");
  } else {
    printf("IsOnSbY false \n");
  }

  printf("\n");

  printf("p1 ada di kuadran %d \n", Kuadran(p1));
  printf("\n");

  /* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */
  Point ptemp;
  printf("Sebelum diubah");
  TulisPOINT(p1);
  printf("\n");

  ptemp = NextX(p1);
  printf("Setelah diubah nextX ");
  TulisPOINT(ptemp);
  printf("\n");

  ptemp = NextY(p1);
  printf("Setelah diubah nextY ");
  TulisPOINT(ptemp);
  printf("\n");

  ptemp = PlusDelta(p1, 3, 4);
  printf("Setelah diubah plusDelta 3 4 ");
  TulisPOINT(ptemp);
  printf("\n");

  float jarak;
  jarak = Jarak0(p1);
  printf("Jarak p1 ke origin %.2f \n", jarak);

  float panjangAntar;
  panjangAntar = Panjang(p1, p2);
  printf("Jarak antar p1 dan p2 %.2f \n", panjangAntar);
  printf("\n");

  printf("Sebelum diubah ");
  TulisPOINT(p1);
  printf("\n");

  Geser(&p1, 10.00, 20.00);
  printf("Setelah digeser 10 20 ");
  TulisPOINT(p1);
  printf("\n \n");

  printf("Tolong input 3 4 lagi buat reset \n");
  BacaPOINT(&p1);

  GeserKeSbX(&p1);
  printf("Setelah digeser ke sumbu X ");
  TulisPOINT(p1);
  printf("\n \n");

  printf("Tolong input 3 4 lagi buat reset \n");
  BacaPOINT(&p1);

  GeserKeSbY(&p1);
  printf("Setelah digeser ke sumbu Y ");
  TulisPOINT(p1);
  printf("\n \n");
}