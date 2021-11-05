/* MODUL LIST INVENTORY */
/* Berisi definisi dan semua primitif pemrosesan list */
/* Penempatan elemen tidak rata kiri (menyebar) */
/* Banyaknya elemen didefinisikan secara implisit, memori array statik */

#ifndef LIST_H
#define LIST_H

#include "../../include/constants.h"
#include "../../include/boolean.h"
#include "../../object/gadget/gadget.h"

/*  Kamus Umum */
/* Kapasitas list */
#define LIST_CAPACITY INV_CAP
/* Nilai elemen tak terdefinisi */
#define LIST_VAL_UNDEF NONE
/* Tipe elemen list */
typedef GadgetType ElTypeList;

/* Definisi elemen dan koleksi objek */
typedef struct {
   ElTypeList contents[LIST_CAPACITY]; /* memori tempat penyimpan elemen (container) */
} List;
/* Indeks yang digunakan [0..LIST_CAPACITY-1] */
/* Jika l adalah List, cara deklarasi dan akses: */
/* Deklarasi : l : List */
/* Maka cara akses: 
   ELMT(l,i) untuk mengakses elemen ke-i */
/* Definisi : 
   List kosong: semua elemen bernilai VAL_UNDEF
   Definisi elemen pertama: ELMT(l,i) dengan i=0 */

/* ********** SELEKTOR ********** */
#define LIST_ELMT(l, i) (l).contents[(i)]

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
/* I.S. l sembarang */
/* F.S. Terbentuk List l kosong dengan kapasitas LIST_CAPACITY */
/* Proses: Inisialisasi semua elemen List l dengan VAL_UNDEF */
void CreateList(List *l);

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
/* Mengirimkan banyaknya elemen efektif List */
/* Mengirimkan nol jika List kosong */
int lengthList(List l);

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
/* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
/* *** Test List penuh *** */
boolean isEmptyList(List l);
/* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */
boolean isFullList(List l);

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan ELMT(l,i) = val */
/* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
/* Skema Searching yang digunakan bebas */
int indexOfList(List l, ElTypeList val);

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen *** */
/* Proses: Menambahkan val pada elemen yang masih kosong */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
void insertList(List *l, ElTypeList val);
/* *** Menghapus elemen *** */
/* Proses: Menghapus elemen pada indeks idx (0..LIST-CAPACITY-1) pada list */
/* I.S. List l tidak kosong, idx valid */
/* F.S. Elemen pada indeks idx akan diisi dengan nilai LIST_VAL_UNDEF */
void deleteAtList(List *l, int idx);

#endif