#include <stdio.h>
#include "list.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateListPos(ListPos *l){
/* I.S. l sembarang */
/* F.S. Terbentuk List l kosong dengan kapasitas CAPACITY */
/* Proses: Inisialisasi semua elemen List l dengan VAL_UNDEF */
    int i;
    for (i = 0; i < CAPACITY; i++)
    {
        ELMT(*l, i) = VAL_UNDEF;
    }
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int length(ListPos l){
/* Mengirimkan banyaknya elemen efektif List */
/* Mengirimkan nol jika List kosong */
    int i = 0;
    int freq = 0;
    
    while ((i < CAPACITY) && (ELMT(l, i) != VAL_UNDEF))
    {
        freq += 1;
        i++;
    }
    return(freq);
    
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValid(ListPos l, int i){
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */
/* yaitu antara indeks yang terdefinisi utk container*/
    return((i >= 0) && (i <= CAPACITY-1));
}

boolean isIdxEff(ListPos l, int i){
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */
/* yaitu antara 0..length(l)-1 */
    return((i >= 0) && (i <= length(l)-1));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isEmpty(ListPos l){
/* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
    return(length(l) == 0);
}

/* *** Test List penuh *** */
boolean isFull(ListPos l){
/* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */
    return(length(l) == CAPACITY);
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi List dari pembacaan *** */
void readList(ListPos *l){
/* I.S. l sembarang */
/* F.S. List l terdefinisi */
/* Proses: membaca banyaknya elemen l dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya n */
/*    Pembacaan diulangi sampai didapat n yang benar yaitu 0 <= n <= CAPACITY */
/*    Jika n tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < n <= CAPACITY; Lakukan n kali: 
          Baca elemen mulai dari indeks 0 satu per satu diakhiri enter */
/*    Jika n = 0; hanya terbentuk List kosong */
    int n;
    int i = 0;
    scanf("%d", &n);
    while ((n < 0) || (n > CAPACITY))
    {
        scanf("%d", &n);
    }
    if (n == 0)
    {
        CreateListPos(&*l);;
    }
    
    else if ((n > 0) && (n <= CAPACITY))
    {
        CreateListPos(&*l);
        while (i < n)
        {
            scanf("%d", &ELMT(*l,i));
            i++;
        }
    }
}

void displayList(ListPos l){
/* Proses : Menuliskan isi List dengan traversal, List ditulis di antara kurung 
   siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan 
   karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. l boleh kosong */
/* F.S. Jika l tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika List kosong : menulis [] */
    int i;
    if(isEmpty(l)){
        printf("[]");
    }
    else{
        printf("[");
        printf("%d", ELMT(l, 0));
        for (i = 1; i < length(l); i++)
        {
            printf(",");
            printf("%d", ELMT(l, i));
        }
        printf("]");
    }
}

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika List : Penjumlahan, pengurangan, perkalian, ... *** */
ListPos plusMinusTab(ListPos l1, ListPos l2, boolean plus){
/* Prekondisi : l1 dan l2 berukuran sama dan tidak kosong */
/* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada 
       indeks yang sama dijumlahkan */
/* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi 
       elemen l2 pada indeks yang sama */
    int i;
    if (plus)
    {
        for (i = 0; i < length(l1); i++)
        {
            ELMT(l1,i) += ELMT(l2,i);
        }
    }
    else if (!plus)
    {
        for (i = 0; i < length(l1); i++)
        {
            ELMT(l1,i) -= ELMT(l2,i);
        }
    }
    return(l1);
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan List: *** */
boolean isListEqual(ListPos l1, ListPos l2){
/* Mengirimkan true jika l1 sama dengan l2 yaitu jika ukuran l1 = l2 dan semua 
   elemennya sama */
    int i = 0;
    boolean tmp = true;
    if (length(l1) != length(l2))
    {
        tmp = false;
    }
    else if (length(l1) == length(l2))
    {
        while ((i < length(l1)) && (tmp = true))
        {
            if (ELMT(l1,i) != ELMT(l2,i))
            {
                tmp = false;
            }
            i++;
        }
    }
    return(tmp);
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOf(ListPos l, ElType val){
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan ELMT(l,i) = val */
/* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
/* Skema Searching yang digunakan bebas */
    int i=0;
    int idx;
    boolean found = false;
    if (isEmpty(l))
    {
        return(IDX_UNDEF);
    }
    else{
        while ((i < length(l)) && (found == false))
        {
            if (ELMT(l, i) == val)
            {
                found = true;
                idx = i;
            }
            i++;
        }
        if (found == true)
        {
            return(idx);
        }
        else if (found == false)
        {
            return(IDX_UNDEF);
        }
    }
}

/* ********** NILAI EKSTREM ********** */
void extremes(ListPos l, ElType *max, ElType *min){
/* I.S. List l tidak kosong */
/* F.S. Max berisi nilai terbesar dalam l;
        Min berisi nilai terkecil dalam l */
    int i;
    *max = ELMT(l,0);
    *min = ELMT(l,0);
    for (i = 1; i < length(l); i++)
    {
        if (*max < ELMT(l,i))
        {
            *max = ELMT(l,i);
        }
        if (*min > ELMT(l,i))
        {
            *min = ELMT(l,i);
        }
    }
}

/* ********** OPERASI LAIN ********** */
boolean isAllEven(ListPos l){
/* Menghailkan true jika semua elemen l genap */
    int i = 0;
    boolean even = true;
    while ((i < length(l)) && (even == true))
    {
        if ((ELMT(l,i) % 2) != 0)
        {
            even = false;
        }
        i++;
    }
    return(even);
}

/* ********** SORTING ********** */
void sort(ListPos *l, boolean asc){
/* I.S. l boleh kosong */
/* F.S. Jika asc = true, l terurut membesar */
/*      Jika asc = false, l terurut mengecil */
/* Proses : Mengurutkan l dengan salah satu algoritma sorting,
   algoritma bebas */
    ElType min, max;
    int temp, i, j;
    extremes(*l, &max, &min);
    if (asc)
    {
        for (i = 0; i < length(*l); i++)
        {
            for (j = i+1; j < length(*l); j++)
            {
                if (ELMT(*l, i) > ELMT(*l, j))
                {
                    temp = ELMT(*l, i);
                    ELMT(*l, i) = ELMT(*l, j);
                    ELMT(*l, j) = temp;
                }   
            }   
        }
    }
    else if (!asc)
    {
        for (i = 0; i < length(*l); i++)
        {
            for (j = i+1; j < length(*l); j++)
            {
                if (ELMT(*l, i) < ELMT(*l, j))
                {
                    temp = ELMT(*l, i);
                    ELMT(*l, i) = ELMT(*l, j);
                    ELMT(*l, j) = temp;
                }   
            }   
        }
    }
    
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLast(ListPos *l, ElType val){
/* Proses: Menambahkan val sebagai elemen terakhir List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
    int p = length(*l);
    if (!isFull(*l))
    {
        ELMT(*l, p) = val;
    }
}

/* ********** MENGHAPUS ELEMEN ********** */
void deleteLast(ListPos *l, ElType *val){
/* Proses : Menghapus elemen terakhir List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
    int p = length(*l);
    if (!isEmpty(*l))
    {
        *val = ELMT(*l, p-1);
        ELMT(*l, p-1) = VAL_UNDEF;
    }
}