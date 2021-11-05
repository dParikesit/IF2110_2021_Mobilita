/* File : list_linked.c */
// Implementasi listlinked

#include "list_linked.h"

#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPE */
/****************** PEMBUATAN ListLinked KOSONG ******************/
void CreateListLinked(ListLinked *l) {
  /* I.S. sembarang             */
  /* F.S. Terbentuk ListLinked kosong */

  FIRST(*l) = NULL;
}

/****************** TEST ListLinked KOSONG ******************/
boolean isEmptyListLinked(ListLinked l) {
  /* Mengirim true jika ListLinked kosong */
  return FIRST(l) == NULL;
}

/****************** GETTER SETTER ******************/
ElTypeListLinked getElmtListLinked(ListLinked l, int idx) {
  /* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..lengthListLinked(l) */
  /* F.S. Mengembalikan nilai elemen l pada indeks idx */
  int i = 0;
  Address p = FIRST(l);
  while (i < idx) {
    i++;
    p = NEXT(p);
  }
  return INFO(p);
}

void setElmtListLinked(ListLinked *l, int idx, ElTypeListLinked val) {
  /* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..lengthListLinked(l) */
  /* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
  int i = 0;
  Address p = FIRST(*l);
  while (i < idx) {
    i++;
    p = NEXT(p);
  }
  INFO(p) = val;
}

int indexOfListLinked(ListLinked l, ElTypeListLinked val) {
  /* I.S. l, val terdefinisi */
  /* F.S. Mencari apakah ada elemen ListLinked l yang bernilai val (menunjuk pada val yang sama) */
  /* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
  /* Mengembalikan IDX_UNDEF jika tidak dElTypeListLinkedukan */
  int idx = IDX_UNDEF;
  boolean found = false;
  int i = 0;
  Address p = FIRST(l);
  while (NEXT(p) != NULL && found == false) {
    if (INFO(p) == val) {
      idx = i;
      found = true;
    }
    i++;
    p = NEXT(p);
  }
  return idx;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirstListLinked(ListLinked *l, ElTypeListLinked val) {
  /* I.S. l mungkin kosong */
  /* F.S. Melakukan alokasi sebuah elemen dan */
  /* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
  /* Jika alokasi gagal: I.S.= F.S. */
  Address p = newNode(val);
  if (p != NULL) {
    NEXT(p) = FIRST(*l);
    FIRST(*l) = p;
  }
}

void insertLastListLinked(ListLinked *l, ElTypeListLinked val) {
  /* I.S. l mungkin kosong */
  /* F.S. Melakukan alokasi sebuah elemen dan */
  /* menambahkan elemen ListLinked di akhir: elemen terakhir yang baru */
  /* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
  if (isEmptyListLinked(*l)) {
    insertFirstListLinked(l, val);
  } else {
    Address p = newNode(val);
    if (p != NULL) {
      Address prev = FIRST(*l);
      while (NEXT(prev) != NULL) {
        prev = NEXT(prev);
      }
      NEXT(prev) = p;
    }
  }
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteLastListLinked(ListLinked *l, ElTypeListLinked *val) {
  /* I.S. ListLinked tidak kosong */
  /* F.S. Elemen terakhir ListLinked dihapus: nilai info disimpan pada x */
  /*      dan alamat elemen terakhir di-dealokasi */
  Address prev = NULL;
  Address p = FIRST(*l);
  while (NEXT(p) != NULL) {
    prev = p;
    p = NEXT(p);
  }
  if (prev == NULL) {
    FIRST(*l) = NULL;
  } else {
    NEXT(prev) = NULL;
  }
  *val = INFO(p);
}

/****************** PROSES SEMUA ELEMEN ListLinked ******************/
void displayListLinked(ListLinked l) {
  /* I.S. ListLinked mungkin kosong */
  /* F.S. Jika ListLinked tidak kosong, iai ListLinked dicetak ke kanan: [e1,e2,...,en] */
  /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
  /* Jika ListLinked kosong : menulis [] */
  /* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
  printf("[");
  Address p = FIRST(l);
  while (p != NULL) {
    printf("%d", INFO(p));
    p = NEXT(p);
    if (p != NULL) {
      printf(",");
    }
  }
  printf("]");
}

int lengthListLinked(ListLinked l) {
  /* Mengirimkan banyaknya elemen ListLinked; mengirimkan 0 jika ListLinked kosong */
  Address p = FIRST(l);
  int count = 0;
  while (p != NULL) {
    count++;
    p = NEXT(p);
  }
  return count;
}

/****************** PROSES TERHADAP ListLinked ******************/
ListLinked concatListLinked(ListLinked l1, ListLinked l2) {
  /* Mencari apakah ada elemen ListLinked yang beralamat P */
  /* Mengirimkan true jika ada, false jika tidak ada */
  ListLinked lnew;
  CreateListLinked(&lnew);

  Address p = FIRST(l1);
  while (p != NULL) {
    insertLastListLinked(&lnew, INFO(p));
    p = NEXT(p);
  }

  p = FIRST(l2);
  while (p != NULL) {
    insertLastListLinked(&lnew, INFO(p));
    p = NEXT(p);
  }
  return lnew;
}
