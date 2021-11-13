#include <stdio.h>
#include <stdlib.h>
#include "listdin.h"
#include "../point/point.h"
#include "../../object/building/building.h"

void displayBuilding(Building* elmt){
    printf("%c ", LETTER(*elmt));
    TulisPoint(POS(*elmt));
}

void TulisPoint(Point P) {
  /* I.S. P terdefinisi */
  /* F.S. P tertulis di layar dengan format "(X,Y)" */
  /* Nilai P ditulis ke layar dengan format "(X,Y)"
   tanpa spasi, enter, atau karakter lain di depan, belakang,
   atau di antaranya
*/

  printf("(%d,%d)", Absis(P), Ordinat(P));
}

void displayListDin(ListDin l) {
    for (int i=0;i<LISTDIN_NEFF(l); i++) {
        displayBuilding(LISTDIN_ELMT(l, i));
        printf("\n");
    }
}


int main(){
    ListDin list, l1, l2;
    Building* lastVal = (Building*) malloc(sizeof(Building));
    Building* lastVal1 = (Building*) malloc(sizeof(Building));
    Building* lastVal2 = (Building*) malloc(sizeof(Building));

    Building* arrBuilding[] = {lastVal, lastVal1, lastVal2};
    int COUNTBUILDING = sizeof(arrBuilding)/sizeof(Building*);

    lastVal->letter = 'C';
    lastVal->pos.X = 1;
    lastVal->pos.Y = 2;
    lastVal1->letter = 'B';
    lastVal1->pos.X = 6;
    lastVal1->pos.Y = 0;
    lastVal2->letter = 'Q';
    lastVal2->pos.X = 8;
    lastVal2->pos.Y = 9;

    CreateListDin(&list, 5);
    
    // cek kasus length = 0
    printf("panjang list sekarang : %d\n", lengthListDin(list));

    if (isEmptyListDin(list)) 
        printf("list kosong\n");
    else 
        printf("List tidak kosong\n");

    for (int i=0;i<COUNTBUILDING;i++) {
        insertLastListDin(&list, arrBuilding[i]);
    }

    if (isFullListDin(list)) 
        printf("list penuh\n");
    else 
        printf("list tidak penuh\n");

    printf("panjang listdin sekarang: %d\n", lengthListDin(list));
    printf("index terakhir dari list : %d\n", getLastIdxListDin(list));
    printf("listdin sekarang: \n");
    displayListDin(list);

    int arr[6] = {0, -1, LISTDIN_NEFF(list), LISTDIN_NEFF(list)-1, LISTDIN_CAPACITY(list), LISTDIN_CAPACITY(list)-1};

    printf("\n\n");
    for (int i=0;i<6;i++) {
        if (isIdxValidListDin(list, arr[i]))
            printf("%d. %d index valid\n",i, arr[i]);
        if (isIdxEffListDin(list, arr[i]))
            printf("%d. %d index effektif\n",i, arr[i]);
    }

    printf("\n\n");
    for (int i=0;i<COUNTBUILDING;i++) {
        displayBuilding(arrBuilding[i]);
        printf(" berada di index: %d\n", indexOfListDin(list, arrBuilding[i]));
    }

    printf("\n\n");
    deleteLastListDin(&list, &lastVal);
    printf("index terakhir list setelah dihapus elemen terakhir: %d\n", getLastIdxListDin(list));
    printf("listdin sekarang: \n");
    displayListDin(list);
    printf("\n");

    printf("\n\n");
    printf("Capacity sekarang: %d\n", LISTDIN_CAPACITY(list));
    growListDin(&list,4);
    printf("Capacity sekarang: %d\n", LISTDIN_CAPACITY(list));
    printf("Listdin sekarnag: \n");
    displayListDin(list);
    shrinkListDin(&list, 2);
    printf("Capacity sekarang: %d\n", LISTDIN_CAPACITY(list));
    printf("Listdin sekarnag: \n");
    displayListDin(list);
    compactListDin(&list);
    printf("Capacity sekarang: %d\n", LISTDIN_CAPACITY(list));
    printf("Listdin sekarnag: \n");
    displayListDin(list);

    return 0;
}