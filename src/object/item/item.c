#include "item.h"

#include "../../adt/listlinked/list_linked.h"
#include "../../helper/stream/stream.h"
#include "../../include/wrapper.h"

Item *getCurrentItem() {
  // Get a pointer Item on the top of the bag
  return TOP(GSTATS.bag);
}

Item *getPickUpItem() {
  // Get a pointer to first item that can be picked up in current mobitaPos
  return getElmtListLinked(GSTATS.toDoList, indexOfPosLinkedList(GSTATS.toDoList, (MOBITAPOS)->pos));
}

boolean toDoListHas(ItemType type) {
  // Check if toDoList has given ItemType (for checking if there’s VIP Item or so)
  return indexOfTypeLinkedList(GSTATS.toDoList, type) != IDX_UNDEF;
}

boolean inProgressListHas(ItemType type) {
  // Check if inProgressList has given ItemType (for checking if there’s Heavy Item or so)
  return indexOfTypeLinkedList(GSTATS.inProgressList, type) != IDX_UNDEF;
}

boolean isLetterInPickUpToDoList(char letter) {
  // Cek apakah letter/nama building ada pada todolist
  return indexOfLetterLinkedList(GSTATS.toDoList, letter) != IDX_UNDEF;
}

ElTypeListLinked getItemInProgressList(ItemType type) {
  // Get first item in progress list that has ItemType == type
  // Guaranteed has it
  int idx = indexOfTypeLinkedList(GSTATS.inProgressList, type);
  return getElmtListLinked(GSTATS.inProgressList, idx);
}

void updateItem() {
  // I.S. inProgressList terdefinisi
  // F.S. Semua PERISHABLE di inProgressList akan berkurang current duration nya
  boolean found = false;
  Address p = FIRST(GSTATS.inProgressList);
  int idx = -1;
  while (found == false) {
    while (NEXT(p) != NULL && found == false) {
      if (INFO(p)->type == PERISHABLE) {
        INFO(p)->currentDuration -= 1;
        found = true;
      }
      idx += 1;
      p = NEXT(p);
    }

    ElTypeListLinked tempListLinked;
    if (found == true) {
      deleteAtListLinked(&GSTATS.inProgressList, idx, &tempListLinked);

      Stack tempStack;
      CreateStack(&tempStack);

      ElTypeStack tempElStack;
      while (IDX_TOP(GSTATS.bag) > idx) {
        pop(&GSTATS.bag, &tempElStack);
        push(&tempStack, tempElStack);
      }

      pop(&GSTATS.bag, &tempElStack);

      while (!isEmpty(GSTATS.bag)) {
        pop(&tempStack, &tempElStack);
        push(&GSTATS.bag, tempElStack);
      }
    }

    if (NEXT(p) != NULL) {
      found = false;
    }
  }
}

boolean isEqualItem(Item item1, Item item2) {
  // Compare two items and return whether both items are
  return ((item1.timePickUp == item2.timePickUp) && (item1.pickUp == item2.pickUp) && (item1.dropOff == item2.dropOff) && (item1.type == item2.type) && (item1.maxDuration == item2.maxDuration) && (item1.currentDuration == item2.currentDuration));
}

// Mengembalikan nama dari ItemType type.
// N = Normal Item, H = Heavy Item, P = Perishable Item, V = VIP Item
char *getItemTypeName(ItemType type) {
  switch (type) {
    case NORMAL:
      return "Normal Item";
    case HEAVY:
      return "Heavy Item";
    case PERISHABLE:
      return "Perishable Item";
    case VIP:
      return "VIP Item";
  }
}

void SerializeItem(Item *b) {
  writeInt(b->timePickUp);
  writeChar(b->pickUp->letter);
  writeChar(b->dropOff->letter);
  writeChar(b->type);
  if (b->type == PERISHABLE) {
    writeInt(b->maxDuration);
    writeInt(b->currentDuration);
  }
  writeMark();
}

void DeserializeItem(Item *b, boolean extended) {
  b->timePickUp = readInt();
  b->pickUp = getLetterRefBuilding(readChar());
  b->dropOff = getLetterRefBuilding(readChar());
  b->type = readChar();
  if (b->type == PERISHABLE) {
    b->maxDuration = readInt();
    if (extended)
      b->currentDuration = readInt();
    else
      b->currentDuration = b->maxDuration;
  }
}
