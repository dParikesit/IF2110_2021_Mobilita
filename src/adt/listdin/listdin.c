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
  LISTDIN_BUFFER(*l) = (Item*)malloc(capacity * sizeof(Item));
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
Item inputItemListDin() {
  // Mengembalikan input Item dari user

  // KAMUS
  Item input;
  
  // ALGORITMA
  scanf("%d", &input);
  return input;
}

/* *** Mendefinisikan isi list dari pembacaan *** */
void readList(ListDin *l) {
  /* I.S. l sembarang dan sudah dialokasikan sebelumnya */
  /* F.S. List l terdefinisi */
  /* Proses : membaca banyaknya elemen l dan mengisi nilainya */
  /* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
  /*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= LISTDIN_CAPACITY(l) */
  /*    Jika N tidak valid, tidak diberikan pesan kesalahan */
  /* 2. Jika 0 < N <= LISTDIN_CAPACITY(l); Lakukan N kali: Baca elemen mulai dari indeks
        0 satu per satu diakhiri enter */
  /*    Jika N = 0; hanya terbentuk l kosong */

  // KAMUS
  int N;
  IdxType i;
  // Item input;

  // ALGORITMA
  do {
    scanf("%d",&N);
  } while (N<0 || N>LISTDIN_CAPACITY(*l));

  LISTDIN_NEFF(*l) = N;
  if (N!=0) {
    for (i=0;i<N;i++) {
      // scanf("%d",&input);
      // LISTDIN_ELMT(*l,i) = input;
      LISTDIN_ELMT(*l, i) = inputItemListDin();
    }
  }
}

void printItem(Item el) {
  // I.S. sembarang
  // F.S. tertuliskan di layar elemen input tanpa enter

  printf("%d", el);
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
    // printf("%d",LISTDIN_ELMT(l,0));
    printItem(LISTDIN_ELMT(l,0));
    for (i=1;i<LISTDIN_NEFF(l);i++) {
      printf(",");
      printItem(LISTDIN_ELMT(l,i));
    }
  }
  printf("]");
}

Item aritmeticOpsItem(Item i1, Item i2, boolean plus);

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika list : Penjumlahan, pengurangan, perkalian, ... *** */
ListDin plusMinusList(ListDin l1, ListDin l2, boolean plus) {
  /* Prekondisi : l1 dan l2 memiliki Neff sama dan tidak kosong */
  /* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada indeks yang sama dijumlahkan */
  /* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi elemen l2 pada indeks yang sama */

  // KAMUS
  IdxType i;
  ListDin l3;
  
  // ALGORITMA
  CreateListDin(&l3,LISTDIN_NEFF(l1));
  LISTDIN_NEFF(l3) = LISTDIN_NEFF(l1);

  if (plus) {
    for (i=0;i<LISTDIN_NEFF(l3);i++) {
      // LISTDIN_ELMT(l3,i) = LISTDIN_ELMT(l1,i) + LISTDIN_ELMT(l2,i);
      LISTDIN_ELMT(l3, i) = aritmeticOpsItem(LISTDIN_ELMT(l1,i), LISTDIN_ELMT(l2,i), true);
    }
  } else {
    for (i=0;i<LISTDIN_NEFF(l3);i++) {
      // LISTDIN_ELMT(l3,i) = LISTDIN_ELMT(l1,i) - LISTDIN_ELMT(l2,i);
      LISTDIN_ELMT(l3, i) = aritmeticOpsItem(LISTDIN_ELMT(l1,i), LISTDIN_ELMT(l2,i), false);
    }
  }
  return l3;
}

boolean isItemSame(Item i1, Item i2);

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan list : < =, > *** */
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
      // if (LISTDIN_ELMT(l1,i) != LISTDIN_ELMT(l2,i))
      if (isItemSame(LISTDIN_ELMT(l1,i), LISTDIN_ELMT(l2,i)))
        equal = false;
      else
        i++;
    }
  }
  return equal;
}

boolean isItemSame(Item it, Item val);

/* ********** SEARCHING ********** */
/* ***  Perhatian : list boleh kosong!! *** */
IdxType indexOf(ListDin l, Item val){
  /* Search apakah ada elemen List l yang bernilai val */
  /* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = val */
  /* Jika tidak ada, mengirimkan IDX_UNDEF */
  /* Menghasilkan indeks tak terdefinisi (IDX_UNDEF) jika List l kosong */
  /* Skema Searching yang digunakan bebas */

  // KAMUS
  IdxType i;
  
  // ALGORITMA
  if (LISTDIN_NEFF(l) == 0)
    i = IDX_UNDEF;
  else {
    i=0;
    while (!isItemSame(LISTDIN_ELMT(l,i), val) && i < LISTDIN_NEFF(l))
      i++;
    if (i == LISTDIN_NEFF(l))
      i = IDX_UNDEF;
  }
  return i;
}

boolean isItemGreater(Item i1, Item i2);

/* ********** NILAI EKSTREM ********** */
void extremes(ListDin l, Item *max, Item *min) {
  /* I.S. List l tidak kosong */
  /* F.S. max berisi nilai maksimum l;
          min berisi nilai minimum l */

  // KAMUS
  IdxType i;

  // ALGORITMA
  *max = LISTDIN_ELMT(l,0);
  *min = LISTDIN_ELMT(l,0);
  for (i=1;i<LISTDIN_NEFF(l);i++) {
    // if (LISTDIN_ELMT(l,i) > *max)
    if (isItemGreater(LISTDIN_ELMT(l,i), *max))
      *max = LISTDIN_ELMT(l,i);
    // if (LISTDIN_ELMT(l,i) < *min)
    if (isItemGreater(*min, LISTDIN_ELMT(l,i)))
      *min = LISTDIN_ELMT(l,i);
  }
}

/* ********** OPERASI LAIN ********** */
void copyList(ListDin lIn, ListDin *lOut) {
  /* I.S. lIn terdefinisi tidak kosong, lOut sembarang */
  /* F.S. lOut berisi salinan dari lIn (identik, nEff dan capacity sama) */
  /* Proses : Menyalin isi lIn ke lOut */

  // KAMUS
  IdxType i;

  // ALGORITMA
  CreateListDin(lOut,LISTDIN_CAPACITY(lIn));
  LISTDIN_NEFF(*lOut) = LISTDIN_NEFF(lIn);

  for (i=0;i<LISTDIN_NEFF(lIn);i++){
    LISTDIN_ELMT(*lOut,i) = LISTDIN_ELMT(lIn,i);
  }
}

void resetItem(Item * it);

Item sumList(ListDin l) {
  /* Menghasilkan hasil penjumlahan semua elemen l */
  /* Jika l kosong menghasilkan 0 */

  // KAMUS
  IdxType i;
  Item sum;

  // ALGORITMA
  // sum = 0;
  resetItem(&sum);
  for (i=0;i<LISTDIN_NEFF(l);i++) {
    // sum += LISTDIN_ELMT(l,i);
    sum = aritmeticOpsItem(sum, LISTDIN_ELMT(l,i), true);
  }
  return sum;
}

int countVal(ListDin l, Item val) {
  /* Menghasilkan berapa banyak kemunculan val di l */
  /* Jika l kosong menghasilkan 0 */

  // KAMUS
  int count;
  IdxType i;

  // ALGORITMA
  count = 0;
  for (i=0;i<LISTDIN_NEFF(l);i++) {
    // if (LISTDIN_ELMT(l,i) == val)
    if (isItemSame(LISTDIN_ELMT(l,i), val))
      count++;
  }
  return count;
}

boolean isEven(Item it);

boolean isAllEven(ListDin l) {
  /* Menghailkan true jika semua elemen l genap. l boleh kosong */

  // KAMUS
  boolean allEven;
  IdxType i;

  // ALGORITMA
  allEven = true;
  i=0;

  while (allEven && i<LISTDIN_NEFF(l)) {
    if (!isEven(LISTDIN_ELMT(l,i)))
      allEven = false;
    else
      i++;
  }
  return allEven;
}

/* ********** SORTING ********** */
void sort(ListDin *l, boolean asc) {
  /* I.S. l boleh kosong */
  /* F.S. Jika asc = true, l terurut membesar */
  /*      Jika asc = false, l terurut mengecil */
  /* Proses : Mengurutkan l dengan salah satu algoritma sorting,
    algoritma bebas */

  // KAMUS
  int len;
  IdxType i,j,swapIdx;
  Item temp;
  
  // ALGORITMA
  len = length(*l);
  if (LISTDIN_NEFF(*l) != 0) {
    if (asc) {
      for (i=0;i<len-1;i++) {
        swapIdx = i;
        for (j=i+1;j<len;j++) {
          // if (LISTDIN_ELMT(*l,j) < LISTDIN_ELMT(*l,swapIdx))
          if (isItemGreater(LISTDIN_ELMT(*l,swapIdx), LISTDIN_ELMT(*l,j)))
            swapIdx = j;
        }
        temp = LISTDIN_ELMT(*l,swapIdx);
        LISTDIN_ELMT(*l,swapIdx) = LISTDIN_ELMT(*l,i);
        LISTDIN_ELMT(*l,i) = temp;
      }
    } else {
      for (i=0;i<len-1;i++) {
        swapIdx = i;
        for (j=i+1;j<len;j++) {
          // if (LISTDIN_ELMT(*l,j) > LISTDIN_ELMT(*l,swapIdx))
          if (isItemGreater(LISTDIN_ELMT(*l,j), LISTDIN_ELMT(*l,swapIdx)))
            swapIdx = j;
        }
        temp = LISTDIN_ELMT(*l,swapIdx);
        LISTDIN_ELMT(*l,swapIdx) = LISTDIN_ELMT(*l,i);
        LISTDIN_ELMT(*l,i) = temp;
      }
    }
  }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLast(ListDin *l, Item val) {
  /* Proses: Menambahkan val sebagai elemen terakhir list */
  /* I.S. List l boleh kosong, tetapi tidak penuh */
  /* F.S. val adalah elemen terakhir l yang baru */

  // ALGORITMA
  LISTDIN_ELMT(*l,LISTDIN_NEFF(*l)) = val;
  LISTDIN_NEFF(*l) += 1;
}

/* ********** MENGHAPUS ELEMEN ********** */
void deleteLast(ListDin *l, Item *val) {
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
