// File list_linked_driver.c
// Berisi contoh penggunaan adt list_linked

#include <stdio.h>
#include "./list_linked.h"
#include "../point/point.h"
#include "../../object/item/item.h"
#include "../../object/building/building.h"

int main(){
  ListLinked l1,l2;
  CreateListLinked(&l1);
  CreateListLinked(&l2);

  printf("Seharusnya true empty");
  if(isEmptyListLinked(l1)){
    printf("True\n");
  } else{
    printf("False\n");
  }

  Item testItem;
  Building testBuild;
  CreateBuilding(&testBuild, 'A');
  testBuild.pos = MakePoint(3, 4);

  testItem.currentDuration = 50;
  testItem.pickUp = &testBuild;
  testItem.type = PERISHABLE;

  Item testItem2;
  Building testBuild2;
  CreateBuilding(&testBuild2, 'B');
  testBuild2.pos = MakePoint(3, 5);

  testItem2.currentDuration = 40;
  testItem2.pickUp = &testBuild2;
  testItem2.type = NORMAL;

  insertFirstListLinked(&l1, &testItem);
  printf("length harusnya 1: %d\n", lengthListLinked(l1));
  printf("idx type harusnya 0: %d\n", indexOfTypeLinkedList(l1, PERISHABLE));
  printf("idx pos harusnya 0: %d\n", indexOfPosLinkedList(l1, MakePoint(3,4)));

  setElmtListLinked(&l1, 0, &testItem2);
  printf("idx of val harusnya IDX_UNDEF: %d \n", indexOfListLinked(l1, &testItem));

  insertLastListLinked(&l1, &testItem);
  printf("length harusnya 2: %d\n");

  Item testret;
  deleteAt(&l1, 0, &testret);
  printf("harusnya 40: %d\n", testret.currentDuration);

  deleteLastListLinked(&l1, &testret);
  printf("harusnya 50: %d\n", testret.currentDuration);

  insertFirstListLinked(&l2, &testItem2);
  ListLinked lret = concatListLinked(l2,l1);
  printf("harusnya 1: %d\n", lengthListLinked(lret));
}