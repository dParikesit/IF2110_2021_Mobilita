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
  LISTDIN_BUFFER(*l) = (Building*)malloc(capacity * sizeof(Building));
  LISTDIN_NEFF(*l) = 0;
}

void dealocate(ListDin *l) {
  /* I.S. l terdefinisi; */
  /* F.S. (l) dikembalikan ke system, LISTDIN_CAPACITY(l)=0; LISTDIN_NEFF(l)=0 */

  // ALGORITMA
  LISTDIN_CAPACITY(*l) = 0;
  LISTDIN_NEFF(*l) = 0;
  free(LISTDIN_BUFFER(*l));
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int length(ListDin l) {
  /* Mengirimkan banyaknya elemen efektif list */
  /* Mengirimkan nol jika list l kosong */
  /* *** Daya tampung container *** */

  // ALGORITMA
  return LISTDIN_NEFF(l);
}

/* *** Selektor INDEKS *** */
IdxType getLastIdx(ListDin l) {
  /* Prekondisi : List l tidak kosong */
  /* Mengirimkan indeks elemen l terakhir */

  // ALGORITMA
  return (LISTDIN_NEFF(l)-1);
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValid(ListDin l, int i) {
  /* Mengirimkan true jika i adalah indeks yang valid utk kapasitas list l */
  /* yaitu antara indeks yang terdefinisi utk container*/

  // ALGORITMA
  return (i >= 0 && i < LISTDIN_CAPACITY(l));
}
boolean isIdxEff(ListDin l, IdxType i) {
  /* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
  /* yaitu antara 0..LISTDIN_NEFF(l) */

  // ALGORITMA
  return (i >= 0 && i < LISTDIN_NEFF(l));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isEmpty(ListDin l) {
  /* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */

  // ALGORITMA
  return (LISTDIN_NEFF(l) == 0);
}

/* *** Test list penuh *** */
boolean isFull(ListDin l){
  /* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */

  // ALGORITMA
  return (LISTDIN_NEFF(l) == LISTDIN_CAPACITY(l));
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
void inputBuilding(Building * input) {
  // I.S. input sembarang
  // F.S. atribut input diisi sesuai dengan input user
  // Proses: membaca input character dan 2 integer dari user dan mengassignnya ke dalam input

  // ALGORITMA
  scanf(" %c", &(LETTER(*input))); //< INTENDED SPACE, SCANF IS DEPRECATED
  scanf("%d", &(ABSIS(POS(*input))));
  scanf("%d", &(ORDINAT(POS(*input))));
}

void readList(ListDin *l) {
  /* I.S. l sembarang dan sudah dialokasikan sebelumnya */
  /* F.S. List l terdefinisi */
  /* Proses : membaca banyaknya elemen l dan mengisi nilainya */
  /* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
  /*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= CAPACITY(l) */
  /*    Jika N tidak valid, tidak diberikan pesan kesalahan */
  /* 2. Jika 0 < N <= CAPACITY(l); Lakukan N kali: Baca elemen mulai dari indeks
        0 satu per satu diakhiri enter */
  /*    Jika N = 0; hanya terbentuk l kosong */

  // KAMUS
  int N;
  IdxType i;
  Building input;

  // ALGORITMA
  printf("masukkan neff dari list: \n");
  do {
    scanf("%d",&N);
  } while (N<0 || N>LISTDIN_CAPACITY(*l));

  LISTDIN_NEFF(*l) = N;
  if (N!=0) {
    for (i=0; i < N; i++) {
      inputBuilding(&input);  
      LISTDIN_ELMT(*l,i) = input;
    }
  }
}

void displayPoint(Point p) {
  // I.S. Point p terdefinisi
  // F.S. tertulis di layar Point p dalam format (p.absis,p.ordinat)
  
  // ALGORITMA
  printf("(%d,%d)", ABSIS(p), ORDINAT(p));
}

void displayBuilding(Building elmt){
  // I.S. Building elmt terdefinisi
  // F.S. tertulis di layar Building elmt dalam format elmt.letter (elmt.pos.absis,elmt.pos.ordinat)

  // ALGORITMA
  printf("%c ", LETTER(elmt));
  displayPoint(POS(elmt));
}

void displayList(ListDin l) {
  /* Proses : Menuliskan isi list dengan traversal, list ditulis di antara kurung siku;
    antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
    di tengah, atau di belakang, termasuk spasi dan enter */
  /* I.S. l boleh kosong */
  /* F.S. Jika l tidak kosong: [e1,e2,...,en] */
  /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
  /* Jika list kosong : menulis [] */

  // KAMUS
  IdxType i;
  
  // ALGORITMA
  printf("[");
  if (LISTDIN_NEFF(l) != 0) {
    printf("{");
    displayBuilding(LISTDIN_ELMT(l,0));
    printf("}");
    for (i=1;i<LISTDIN_NEFF(l);i++) {
      printf(",");
      printf("{");
      displayBuilding(LISTDIN_ELMT(l,i));
      printf("}");
    }
  }
  printf("]");
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan list : < =, > *** */
boolean isBuildingSame(Building i1, Building i2) { 
  return (LETTER(i1) == LETTER(i2) && ABSIS(POS(i1)) == ABSIS(POS(i2)) && ORDINAT(POS(i1)) == ORDINAT(POS(i2)));
}

boolean isListEqual(ListDin l1, ListDin l2) {
  /* Mengirimkan true jika l1 sama dengan l2 yaitu jika nEff l1 = l2 dan semua elemennya sama */

  // KAMUS
  boolean equal;
  IdxType i;

  // ALGORITMA
  equal = false;
  if (LISTDIN_NEFF(l1) == LISTDIN_NEFF(l2)) {
    i=0;
    equal = true;
    while (i<LISTDIN_NEFF(l1) && equal) {
      if (!isBuildingSame(LISTDIN_ELMT(l1,i), LISTDIN_ELMT(l2,i)))
        equal = false;
      else
        i++;
    }
  }
  return equal;
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : list boleh kosong!! *** */
IdxType indexOf(ListDin l, Building val){
  /* Search apakah ada elemen List l yang bernilai val */
  /* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = val */
  /* Jika tidak ada, mengirimkan IDX_UNDEF */
  /* Menghasilkan indeks tak terdefinisi (IDX_UNDEF) jika List l kosong */

  // KAMUS
  IdxType i;
  
  // ALGORITMA
  if (LISTDIN_NEFF(l) == 0)
    i = IDX_UNDEF;
  else {
    i=0;
    while (!isBuildingSame(LISTDIN_ELMT(l,i), val) && i < LISTDIN_NEFF(l))
      i++;
    if (i == LISTDIN_NEFF(l))
      i = IDX_UNDEF;
  }
  return i;
}

/* ********** OPERASI LAIN ********** */
void copyList(ListDin lIn, ListDin *lOut) {
  /* I.S. lIn terdefinisi tidak kosong, lOut sembarang */
  /* F.S. lOut berisi salinan dari lIn (identik, nEff dan capacity sama) */
  /* Proses : Menyalin isi lIn ke lOut */

  // KAMUS
  IdxType i;

  // ALGORITMA
  CreateListDin(lOut, LISTDIN_CAPACITY(lIn));
  LISTDIN_NEFF(*lOut) = LISTDIN_NEFF(lIn);

  for (i=0; i<LISTDIN_NEFF(lIn); i++){
    LISTDIN_ELMT(*lOut,i) = LISTDIN_ELMT(lIn,i);
  }
}

int countVal(ListDin l, Building val) {
  /* Menghasilkan berapa banyak kemunculan val di l */
  /* Jika l kosong menghasilkan 0 */

  // KAMUS
  int count;
  IdxType i;

  // ALGORITMA
  count = 0;
  for (i=0;i<LISTDIN_NEFF(l);i++) {
    if (isBuildingSame(LISTDIN_ELMT(l,i), val))
      count++;
  }
  return count;
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLast(ListDin *l, Building val) {
  /* Proses: Menambahkan val sebagai elemen terakhir list */
  /* I.S. List l boleh kosong, tetapi tidak penuh */
  /* F.S. val adalah elemen terakhir l yang baru */

  // ALGORITMA
  LISTDIN_ELMT(*l, LISTDIN_NEFF(*l)) = val;
  LISTDIN_NEFF(*l) += 1;
}

/* ********** MENGHAPUS ELEMEN ********** */
void deleteLast(ListDin *l, Building *val) {
  /* Proses : Menghapus elemen terakhir list */
  /* I.S. List tidak kosong */
  /* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
  /*      Banyaknya elemen list berkurang satu */
  /*      List l mungkin menjadi kosong */

  // ALGORITMA
  *val = LISTDIN_ELMT(*l,LISTDIN_NEFF(*l)-1);
  LISTDIN_NEFF(*l)--;
}

/* ********* MENGUBAH UKURAN ARRAY ********* */
void growList(ListDin *l, int num) {
  /* Proses : Menambahkan capacity l sebanyak num */
  /* I.S. List sudah terdefinisi */
  /* F.S. Ukuran list bertambah sebanyak num */

  // KAMUS
  IdxType i;
  ListDin tempList;

  // ALGORITMA
  CreateListDin(&tempList, LISTDIN_CAPACITY(*l)+num);
  LISTDIN_NEFF(tempList) = LISTDIN_NEFF(*l);
  
  for(i=0;i<LISTDIN_NEFF(tempList);i++) {
    LISTDIN_ELMT(tempList,i) = LISTDIN_ELMT(*l,i);
  }
  dealocate(l);
  LISTDIN_BUFFER(*l) = LISTDIN_BUFFER(tempList);
  LISTDIN_CAPACITY(*l) = LISTDIN_CAPACITY(tempList);
  LISTDIN_NEFF(*l) = LISTDIN_NEFF(tempList);
}

void shrinkList(ListDin *l, int num) {
  /* Proses : Mengurangi capacity sebanyak num */
  /* I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity - num. */
  /* F.S. Ukuran list berkurang sebanyak num. */

  // KAMUS
  IdxType i;
  ListDin tempList;

  // ALGORITMA
  CreateListDin(&tempList, LISTDIN_CAPACITY(*l)-num);
  LISTDIN_NEFF(tempList) = LISTDIN_NEFF(*l);
  
  for(i=0;i<LISTDIN_NEFF(tempList);i++) {
    LISTDIN_ELMT(tempList,i) = LISTDIN_ELMT(*l,i);
  }
  dealocate(l);
  LISTDIN_CAPACITY(*l) = LISTDIN_CAPACITY(tempList);
  LISTDIN_BUFFER(*l) = LISTDIN_BUFFER(tempList);
  LISTDIN_NEFF(*l) = LISTDIN_NEFF(tempList);
}

void compactList(ListDin *l) {
  /* Proses : Mengurangi capacity sehingga nEff = capacity */
  /* I.S. List lidak kosong */
  /* F.S. Ukuran nEff = capacity */

  // KAMUS
  IdxType i;
  ListDin tempList;

  // ALGORITMA
  CreateListDin(&tempList, LISTDIN_NEFF(*l));
  LISTDIN_NEFF(tempList) = LISTDIN_NEFF(*l);
  
  for(i=0;i<LISTDIN_NEFF(tempList);i++) {
    LISTDIN_ELMT(tempList,i) = LISTDIN_ELMT(*l,i);
  }
  dealocate(l);
  LISTDIN_BUFFER(*l) = LISTDIN_BUFFER(tempList);
  LISTDIN_CAPACITY(*l) = LISTDIN_CAPACITY(tempList);
  LISTDIN_NEFF(*l) = LISTDIN_NEFF(tempList);
}
