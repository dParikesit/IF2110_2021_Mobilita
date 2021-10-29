#include <stdio.h>
#include "listdin.h"

int main(){
    ListDin list, l1, l2;
    Building lastVal, input;

    CreateListDin(&list, 5);
    
    // cek kasus length = 0
    printf("panjang list sekarang : %d\n", length(list));
    readList(&list);
    printf("List sekarang : ");
    displayList(list); printf("\n");
    printf("panjang list sekarang : %d\n", length(list));

    if (isEmpty(list)) 
        printf("list kosong\n");
    else 
        printf("List tidak kosong\n");

    if (isFull(list)) 
        printf("list penuh\n");
    else 
        printf("list tidak penuh\n");

    printf("Anggota terakhir dari list : %d\n", getLastIdx(list));
    
    deleteLast(&list, &lastVal);
    printf("List setelah dihapus elemen terakhir : ");
    displayList(list);
    printf("\n");

    copyList(list, &l1);
    if (isListEqual(list, l1)) 
        printf("list copy sama\n");
    else 
        printf("list copy beda\n");

    printf("Masukkan building yang akan dicari: \n");
    inputBuilding(&input);
    printf("building yang akan dicari: ");
    displayBuilding(input);printf("\n");

    int idx = indexOf(list, input);
    if (idx == IDX_UNDEF)
        printf("building tersebut tidak ditemukan\n");
    else
        printf("building tersebut berada di urutan ke-%d\n", idx);

    printf("kemunculan building tersebut ada sebanyak %d kali\n", countVal(list, input));

    printf("masukkan elemen building: \n");
    inputBuilding(&input);
    insertLast(&list, input);
    printf("List setelah ditambahkan elemen terakhirnya : ");
    displayList(list);
    printf("\n");

    if (isFull(list)) 
        printf("list penuh\n");
    else 
        printf("list tidak penuh\n");

    printf("kapasitas awal: %d\n", LISTDIN_CAPACITY(list));
    growList(&list, 5);
    printf("List setelah di grow 5 elemen : ");
    displayList(list);
    printf("\n");
    printf("kapasitasnya sekarang: %d\n", LISTDIN_CAPACITY(list));

    if (isEmpty(list)) 
        printf("list kosong\n");
    else 
        printf("list tidak kosong\n");
    
    shrinkList(&list, 3);
    printf("List setelah di shrink 3 elemen: ");
    displayList(list);
    printf("\n");

    if (isFull(list)) 
        printf("list penuh\n");
    else 
        printf("Masih ada tempat sisa\n");
    
    printf("kapasitas awal: %d, neff: %d\n", LISTDIN_CAPACITY(list), LISTDIN_NEFF(list));
    compactList(&list);
    printf("List setelah compact : ");
    displayList(list);
    printf("\n");
    printf("kapasitas sekarang: %d, neff: %d\n", LISTDIN_CAPACITY(list), LISTDIN_NEFF(list));

    if (isFull(list)) 
        printf("list penuh\n");
    else 
        printf("list tidak penuh\n");

    return 0;
}