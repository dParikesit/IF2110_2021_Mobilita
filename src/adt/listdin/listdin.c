#include "listdin.h"
#include <stdio.h>
#include <stdlib.h>

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void CreateListDin(ListDin *l, int capacity) {
  /* I.S. l sembarang, capacity > 0 */
  /* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */

  // ALGORITMA
  LISTDIN_CAPACITY(*l) = capacity;
  LISTDIN_BUFFER(*l) = malloc(capacity * sizeof(ElTypeListDin));
  LISTDIN_NEFF(*l) = 0;
}

void dealocateListDin(ListDin *l) {
  /* I.S. l terdefinisi; */
  /* F.S. (l) dikembalikan ke system, LISTDIN_CAPACITY(l)=0; LISTDIN_NEFF(l)=0 */

  // ALGORITMA
  LISTDIN_CAPACITY(*l) = 0;
  LISTDIN_NEFF(*l) = 0;
  free(LISTDIN_BUFFER(*l));
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int lengthListDin(ListDin l) {
  /* Mengirimkan banyaknya elemen efektif list */
  /* Mengirimkan nol jika list l kosong */
  /* *** Daya tampung container *** */

  // ALGORITMA
  return LISTDIN_NEFF(l);
}

/* *** Selektor INDEKS *** */
int getLastIdxListDin(ListDin l) {
  /* Prekondisi : List l tidak kosong */
  /* Mengirimkan indeks elemen l terakhir */

  // ALGORITMA
  return (LISTDIN_NEFF(l)-1);
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValidListDin(ListDin l, int i) {
  /* Mengirimkan true jika i adalah indeks yang valid utk kapasitas list l */
  /* yaitu antara indeks yang terdefinisi utk container*/

  // ALGORITMA
  return (i >= 0 && i < LISTDIN_CAPACITY(l));
}
boolean isIdxEffListDin(ListDin l, int i) {
  /* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
  /* yaitu antara 0..LISTDIN_NEFF(l) */

  // ALGORITMA
  return (i >= 0 && i < LISTDIN_NEFF(l));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isEmptyListDin(ListDin l) {
  /* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */

  // ALGORITMA
  return (LISTDIN_NEFF(l) == 0);
}

/* *** Test list penuh *** */
boolean isFullListDin(ListDin l){
  /* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */

  // ALGORITMA
  return (LISTDIN_NEFF(l) == LISTDIN_CAPACITY(l));
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : list boleh kosong!! *** */
int indexOfListDin(ListDin l, ElTypeListDin val){
  /* Search apakah ada elemen List l yang bernilai val */
  /* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = val */
  /* Jika tidak ada, mengirimkan IDX_UNDEF */
  /* Menghasilkan indeks tak terdefinisi (IDX_UNDEF) jika List l kosong */

  // KAMUS
  int i;
  
  // ALGORITMA
  if (LISTDIN_NEFF(l) == 0)
    i = IDX_UNDEF;
  else {
    i = 0;
    while (!(LISTDIN_ELMT(l, i) == val) && i < LISTDIN_NEFF(l))
      i++;
    if (i == LISTDIN_NEFF(l))
      i = IDX_UNDEF;
  }
  return i;
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLastListDin(ListDin *l, ElTypeListDin val) {
  /* Proses: Menambahkan val sebagai elemen terakhir list */
  /* I.S. List l boleh kosong, tetapi tidak penuh */
  /* F.S. val adalah elemen terakhir l yang baru */

  // ALGORITMA
  LISTDIN_ELMT(*l, LISTDIN_NEFF(*l)) = val;
  LISTDIN_NEFF(*l) += 1;
}

/* ********** MENGHAPUS ELEMEN ********** */
void deleteLastListDin(ListDin *l, ElTypeListDin* val) {
  /* Proses : Menghapus elemen terakhir list */
  /* I.S. List tidak kosong */
  /* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
  /*      Banyaknya elemen list berkurang satu */
  /*      List l mungkin menjadi kosong */

  // ALGORITMA
  LISTDIN_NEFF(*l)--;
  *val = LISTDIN_ELMT(*l, LISTDIN_NEFF(*l));
}

/* ********* MENGUBAH UKURAN ARRAY ********* */
void growListDin(ListDin *l, int num) {
  /* Proses : Menambahkan capacity l sebanyak num */
  /* I.S. List sudah terdefinisi */
  /* F.S. Ukuran list bertambah sebanyak num */

  // KAMUS
  int i;
  ListDin tempList;

  // ALGORITMA
  CreateListDin(&tempList, LISTDIN_CAPACITY(*l)+num);
  LISTDIN_NEFF(tempList) = LISTDIN_NEFF(*l);
  
  for(i=0;i<LISTDIN_NEFF(tempList);i++) {
    LISTDIN_ELMT(tempList,i) = LISTDIN_ELMT(*l,i);
  }
  dealocateListDin(l);
  LISTDIN_BUFFER(*l) = LISTDIN_BUFFER(tempList);
  LISTDIN_CAPACITY(*l) = LISTDIN_CAPACITY(tempList);
  LISTDIN_NEFF(*l) = LISTDIN_NEFF(tempList);
}

void shrinkListDin(ListDin *l, int num) {
  /* Proses : Mengurangi capacity sebanyak num */
  /* I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity - num. */
  /* F.S. Ukuran list berkurang sebanyak num. */

  // KAMUS
  int i;
  ListDin tempList;

  // ALGORITMA
  CreateListDin(&tempList, LISTDIN_CAPACITY(*l)-num);
  LISTDIN_NEFF(tempList) = LISTDIN_NEFF(*l);
  
  for(i=0;i<LISTDIN_NEFF(tempList);i++) {
    LISTDIN_ELMT(tempList,i) = LISTDIN_ELMT(*l,i);
  }
  dealocateListDin(l);
  LISTDIN_CAPACITY(*l) = LISTDIN_CAPACITY(tempList);
  LISTDIN_BUFFER(*l) = LISTDIN_BUFFER(tempList);
  LISTDIN_NEFF(*l) = LISTDIN_NEFF(tempList);
}

void compactListDin(ListDin *l) {
  /* Proses : Mengurangi capacity sehingga nEff = capacity */
  /* I.S. List lidak kosong */
  /* F.S. Ukuran nEff = capacity */

  // KAMUS
  int i;
  ListDin tempList;

  // ALGORITMA
  CreateListDin(&tempList, LISTDIN_NEFF(*l));
  LISTDIN_NEFF(tempList) = LISTDIN_NEFF(*l);
  
  for(i=0;i<LISTDIN_NEFF(tempList);i++) {
    LISTDIN_ELMT(tempList,i) = LISTDIN_ELMT(*l,i);
  }
  dealocateListDin(l);
  LISTDIN_BUFFER(*l) = LISTDIN_BUFFER(tempList);
  LISTDIN_CAPACITY(*l) = LISTDIN_CAPACITY(tempList);
  LISTDIN_NEFF(*l) = LISTDIN_NEFF(tempList);
}
