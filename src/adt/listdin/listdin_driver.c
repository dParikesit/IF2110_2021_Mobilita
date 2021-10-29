#include <stdio.h>
#include "listdin.h"

int main(){
    ListDin list, l1, l2;
    Building lastVal, input;

    CreateListDin(&list, 5);
    
    // cek kasus length = 0
    printf("panjang list sekarang : %d\n", lengthListDin(list));
    readListDin(&list);
    printf("List sekarang : ");
    displayListDin(list); printf("\n");
    printf("panjang list sekarang : %d\n", lengthListDin(list));

    if (isEmptyListDin(list)) 
        printf("list kosong\n");
    else 
        printf("List tidak kosong\n");

    if (isFullListDin(list)) 
        printf("list penuh\n");
    else 
        printf("list tidak penuh\n");

    printf("Anggota terakhir dari list : %d\n", getLastIdxListDin(list));
    
    deleteLastListDin(&list, &lastVal);
    printf("List setelah dihapus elemen terakhir : ");
    displayListDin(list);
    printf("\n");

    copyListDin(list, &l1);
    if (isListDinEqual(list, l1)) 
        printf("list copy sama\n");
    else 
        printf("list copy beda\n");

    printf("Masukkan building yang akan dicari: \n");
    inputBuilding(&input);
    printf("building yang akan dicari: ");
    displayBuilding(input);printf("\n");

    int idx = indexOfListDin(list, input);
    if (idx == IDX_UNDEF)
        printf("building tersebut tidak ditemukan\n");
    else
        printf("building tersebut berada di urutan ke-%d\n", idx);

    printf("kemunculan building tersebut ada sebanyak %d kali\n", countValListDin(list, input));

    printf("masukkan elemen building: \n");
    inputBuilding(&input);
    insertLastListDin(&list, input);
    printf("List setelah ditambahkan elemen terakhirnya : ");
    displayListDin(list);
    printf("\n");

    if (isFullListDin(list)) 
        printf("list penuh\n");
    else 
        printf("list tidak penuh\n");

    printf("kapasitas awal: %d\n", LISTDIN_CAPACITY(list));
    growListDin(&list, 5);
    printf("List setelah di grow 5 elemen : ");
    displayListDin(list);
    printf("\n");
    printf("kapasitasnya sekarang: %d\n", LISTDIN_CAPACITY(list));

    if (isEmptyListDin(list)) 
        printf("list kosong\n");
    else 
        printf("list tidak kosong\n");
    
    shrinkListDin(&list, 3);
    printf("List setelah di shrink 3 elemen: ");
    displayListDin(list);
    printf("\n");

    if (isFullListDin(list)) 
        printf("list penuh\n");
    else 
        printf("Masih ada tempat sisa\n");
    
    printf("kapasitas awal: %d, neff: %d\n", LISTDIN_CAPACITY(list), LISTDIN_NEFF(list));
    compactListDin(&list);
    printf("List setelah compact : ");
    displayListDin(list);
    printf("\n");
    printf("kapasitas sekarang: %d, neff: %d\n", LISTDIN_CAPACITY(list), LISTDIN_NEFF(list));

    if (isFullListDin(list)) 
        printf("list penuh\n");
    else 
        printf("list tidak penuh\n");

    return 0;
}