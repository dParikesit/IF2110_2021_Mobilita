#include <stdio.h>
#include "list.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateList(List *l){
/* I.S. l sembarang */
/* F.S. Terbentuk List l kosong dengan kapasitas LIST_CAPACITY */
/* Proses: Inisialisasi semua elemen List l dengan LIST_VAL_UNDEF */
    int i;
    for (i = 0; i < LIST_CAPACITY; i++)
    {
        LIST_ELMT(*l, i) = LIST_VAL_UNDEF;
    }
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int lengthList(List l){
/* Mengirimkan banyaknya elemen efektif List */
/* Mengirimkan nol jika List kosong */
    int i, freq = 0;
    for (i = 0; i < LIST_CAPACITY; i++) {
        if (LIST_ELMT(l, i) != LIST_VAL_UNDEF) {
            freq++;
        }
    }
    return freq;
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isEmptyList(List l){
/* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
    return (lengthList(l) == 0);
}

/* *** Test List penuh *** */
boolean isFullList(List l){
/* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */
    return (lengthList(l) == LIST_CAPACITY);
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOfList(List l, ElTypeList val){
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan LIST_ELMT(l,i) = val */
/* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
/* Skema Searching yang digunakan bebas */
    int i=0;
    int len = lengthList(l);
    boolean found = false;
    if (isEmptyList(l))
    {
        return IDX_UNDEF;
    } else {
        while (i < len && !found) {
            if (LIST_ELMT(l, i) == val) {
                found = true;
            } else {
                i++;
            }
        }
        if (found) {
            return i;
        } else {
            return IDX_UNDEF;
        }
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen *** */
/* Proses: Menambahkan val pada elemen yang masih kosong */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
void insertList(List *l, ElTypeList val) {
    int i;
    for (i = 0; i < LIST_CAPACITY; i++) {
        if (LIST_ELMT(*l, i) == LIST_VAL_UNDEF) {
            LIST_ELMT(*l, i) = val;
            break;
        }
    }
}

void deleteAtList(List *l, int idx) {
    LIST_ELMT(*l, idx) = LIST_VAL_UNDEF;
}
