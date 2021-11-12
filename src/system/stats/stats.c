#include "stats.h"
#include "../../include/wrapper.h"
#include "../../helper/stream/stream.h"
#include "../../core/gameplay/gameplay.h"

/* Update stats yang diperlukan.
   I.S. Stats terinisiasi.
   F.S. Update durasi perishable dan speed boost. Periksa end game. */
void updateStats() {
    updateItem();
    if (GSTATS.speedBoostDuration > 0) {
        GSTATS.speedBoostDuration -= GTIME.deltaTime;
    }
    if (MOBITAPOS == &HQ) {
        checkEndGame();
    }
}

/* Tampilkan to do ke layar.
   I.S.  toDoList terdefinisi, mungkin kosong.
   F.S.  Menampilkan to do ke layar. */
void displayToDo() {
    int i = 0;
    ListLinked l = GSTATS.toDoList;
    ElTypeListLinked item;
    Address p = FIRST(l);
/* Format:
   Header: "Pesanan pada To Do List:\n"
   Format: "<x=1...N>. <item[x].pickUp.letter> -> <item[x].dropOff.letter> (getItemTypeName(<item[x].type>))\n" */
    if (p == NULL) {
        printf("Tidak ada pesanan yang bisa di pick up.\n");
    } else {
        printf("Pesanan pada To Do List:\n");
        do {
            item = INFO(p);
            printf(
                "%d. %c -> %c (%s)\n",
                ++i,
                item->pickUp->letter,
                item->dropOff->letter,
                getItemTypeName(item->type)
            );
            p = NEXT(p);
        } while (p != NULL);
    }
}

/* Tampilkan in progress list ke layar.
   I.S. inProgressList terdefinisi, mungkin kosong.
   F.S. Menampilkan in progress list ke layar. */
void displayInProgress() {
    int i = 0;
    ListLinked l = GSTATS.inProgressList;
    ElTypeListLinked item;
    Address p = FIRST(l);
/* Format:
   Header: "Pesanan yang sedang diantarkan:\n"
   Format: "<x=1...N>. <item[x].type> (Tujuan: <item[x].dropOff.letter>)\n" */
    if (p == NULL) {
        printf("Tidak ada pesanan yang sedang dikerjakan.\n");
    } else {
        printf("Pesanan yang sedang dikerjakan:\n");
        do {
            item = INFO(p);
            printf(
                "%d. %s (Tujuan: %c)\n",
                ++i,
                getItemTypeName(item->type),
                item->dropOff->letter
            );
            p = NEXT(p);
        } while (p != NULL);
    }
}

/* Inisialisasi stats ke nilai awal.
   I.S. Stats sembarang.
   F.S. Inisialisasi stats menjadi nilai default. */
void initStats() {
    CreateList(&GSTATS.inventory);
    CreateListLinked(&GSTATS.toDoList);
    CreateListLinked(&GSTATS.inProgressList);
    CreateStack(&GSTATS.bag);
    GSTATS.bagCapEff = 3;
    GSTATS.money = 0;
    GSTATS.returnToSender = 0;
    GSTATS.senterPengecil = false;
    GSTATS.speedBoostDuration = 0;
    GSTATS.totalDeliveredItem = 0;
    GSTATS.totalFailedItem = 0;
}

void SerializeStats() {
    int i, len;
    // 1. Gadget Inventory.
    GadgetType g;
    for (i = 0; i < INV_CAP; i++) {
        g = GSTATS.inventory.contents[i];
        writeInt((int)g);
    }
    writeMark();
    // 2. To Do List.
    ListLinked list = GSTATS.toDoList;
    writeInt(lengthListLinked(list));
    writeMark();
    ElTypeListLinked item;
    Address p = FIRST(list);
    while (p != NULL) {
        item = INFO(p);
        SerializeItem(item);
        p = NEXT(p);
    }
    // 3. In Progress List.
    list = GSTATS.inProgressList;
    writeInt(lengthListLinked(list));
    writeMark();
    p = FIRST(list);
    while (p != NULL) {
        item = INFO(p);
        SerializeItem(item);
        p = NEXT(p);
    }
    // 4. Leftover Properties.
    // "<money> <senterPengecil> <returnToSender> <speedBoostDuration> <bagCapEff>\n"
    writeInt(GSTATS.money);
    writeBoolean(GSTATS.senterPengecil);
    writeInt(GSTATS.returnToSender);
    writeInt(GSTATS.speedBoostDuration);
    writeInt(GSTATS.bagCapEff);
    writeInt(GSTATS.totalDeliveredItem);
    writeInt(GSTATS.totalFailedItem);
    writeMark();
}

void DeserializeStats() {
    // 1. Gadget Inventory.
    int i, N;
    GadgetType g;
    for (i = 0; i < INV_CAP; i++) {
        g = (GadgetType) readInt();
        insertList(&GSTATS.inventory, g);
    }
    // 2. To Do List.
    N = readInt();
    for (i = 0; i < N; i++) {
        Item* item = malloc(sizeof(Item));
        DeserializeItem(item, true);
        insertLastListLinked(&GSTATS.toDoList, item);
    }
    // 3. In Progress List.
    N = readInt();
    for (i = 0; i < N; i++) {
        Item* item = malloc(sizeof(Item));
        DeserializeItem(item, true);
        insertLastListLinked(&GSTATS.inProgressList, item);
        // Also deserialize bag
        push(&GSTATS.bag, item);
    }
    // 4. Leftover Properties.
    GSTATS.money = readInt();
    GSTATS.senterPengecil = readBoolean();
    GSTATS.returnToSender = readInt();
    GSTATS.speedBoostDuration = readInt();
    GSTATS.bagCapEff = readInt();
    GSTATS.totalDeliveredItem = readInt();
    GSTATS.totalFailedItem = readInt();
}
