#include "item.h"

#include "../../helper/stream/stream.h"
#include "../../include/wrapper.h"
#include "../../system/map/map.h"
#include "../../adt/listlinked/list_linked.h"

Item *getCurrentItem() {
  // Get a pointer Item on the top of the bag
  return TOP(_gm.stats.bag);
}

Item *getPickUpItem() {
  // Get a pointer to first item that can be picked up in current mobitaPos
  return getElmtListLinked(_gm.stats.inProgressList, indexOfPosLinkedList(_gm.stats.inProgressList, MOBITAPOS(_gm.map)));
}

boolean toDoListHas(ItemType type) {
  // Check if toDoList has given ItemType (for checking if there’s VIP Item or so)
  return indexOfTypeLinkedList(_gm.stats.toDoList, type) != IDX_UNDEF;
}

boolean inProgressListHas(ItemType type) {
  // Check if inProgressList has given ItemType (for checking if there’s Heavy Item or so)
  return indexOfTypeLinkedList(_gm.stats.inProgressList, type) != IDX_UNDEF;
}

ElTypeListLinked getItemInProgressList(ItemType type) {
  // Get first item in progress list that has ItemType == type
  // Guaranteed has it
  int idx = indexOfTypeLinkedList(_gm.stats.inProgressList, type);
  return getElmtListLinked(_gm.stats.inProgressList, idx);
}

void updateItem() {
  // I.S. inProgressList terdefinisi
  // F.S. Semua PERISHABLE di inProgressList akan berkurang current duration nya

  // TODO Edge case kalo habis sebelum di top
  Address p = FIRST(_gm.stats.inProgressList);
  while (NEXT(p) != NULL) {
    if (INFO(p)->type==PERISHABLE) {
      INFO(p)->currentDuration -= 1;
    }
    p = NEXT(p);
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

void SerializeItem(Item b) {
  writeInt(b.timePickUp);
  writeChar(b.pickUp->letter);
  writeChar(b.dropOff->letter);
  writeChar(b.type);
  if (b.type == PERISHABLE) {
    writeInt(b.maxDuration);
    writeInt(b.currentDuration);
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
