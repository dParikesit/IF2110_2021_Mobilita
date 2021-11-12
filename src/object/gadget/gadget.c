#include "gadget.h"

#include "../../include/wrapper.h"

boolean isInventoryFull() {
  // Mengecek apakah inventory full, yaitu ketika panjang list==capacity
  return lengthList(GSTATS.inventory) == INV_CAP;
}
void addGadget(GadgetType gadget) {
  // Add gadget to inventory
  // I.S. Inventory terdefinisi dan tidak penuh
  // F.S. gadget masuk ke inventory
  insertList(&GSTATS.inventory, gadget);
}
char *getGadgetName(GadgetType gadget) {
  // I.S. gadget terdefinisi tipe nya
  // F.S. print nama gadget tanpa diakhiri karakter apapun
  switch (gadget) {
    case KAIN_PEMBUNGKUS_WAKTU:
      return "Kain Pembungkus Waktu";
    case SENTER_PEMBESAR:
      return "Senter Pembesar";
    case PINTU_KEMANA_SAJA:
      return "Pintu Kemana Saja";
    case MESIN_WAKTU:
      return "Mesin Waktu";
    case SENTER_PENGECIL:
      return "Senter Pengecil";
    case NONE:
      return "-";
  }
}
int getGadgetPrice(GadgetType gadget) {
  // Return harga gadget
  switch (gadget) {
    case KAIN_PEMBUNGKUS_WAKTU:
      return 800;
    case SENTER_PEMBESAR:
      return 1200;
    case PINTU_KEMANA_SAJA:
      return 1500;
    case MESIN_WAKTU:
      return 3000;
    case SENTER_PENGECIL:
      return 800;
    case NONE:
      return 0;
  }
}
void showAndUseGadget() {
  // I.S. inventory terdefinisi
  // F.S. print daftar inventory, kemudian memanggil apply gadget yang dipilih
  int command;
  int len = lengthList(GSTATS.inventory);
  if (len == 0) {
    printf("Inventory mobita kosong.\n");
    return;
  }
  for (int i = 0; i < INV_CAP; i++) {
    printf("%d. %s\n", (i + 1), getGadgetName(LIST_ELMT(GSTATS.inventory, i)));
  }
  printf("Gadget mana yang ingin digunakan? (ketik 0 jika ingin kembali)\n\n");
  printf("ENTER COMMAND: ");
  command = readInt();

  if (command == 0)
    return;

  applyGadget(LIST_ELMT(GSTATS.inventory, command - 1));
  deleteAtList(&GSTATS.inventory, command - 1);
}
void applyGadget(GadgetType gadget) {
  int x, y;
  Item* item;
  // Apply effect of the selected gadget
  switch (gadget) {
    case KAIN_PEMBUNGKUS_WAKTU:
      if (inProgressListHas(PERISHABLE)) {
        Item *perishableItem = getItemInProgressList(PERISHABLE);
        perishableItem->currentDuration = perishableItem->maxDuration;
      }
      break;
    case SENTER_PEMBESAR:
      GSTATS.bagCapEff *= 2;
      if (GSTATS.bagCapEff > BAG_CAP) {
        GSTATS.bagCapEff = BAG_CAP;
      }
      printf(
        "Berhasil menggunakan senter pembesar! Tas kamu sekarang berukuran %d",
        GSTATS.bagCapEff
      );
      break;
    case PINTU_KEMANA_SAJA:
      printf("Menggunakan pintu kemana saja...\n");
      if (navigateAndMoveMobita(true)) {
        printf("Berhasil menggunakan pintu kemana saja\n");
      } else {
        printf("Gagal menggunakan pintu kemana saja\n");
        insertList(&GSTATS.inventory, PINTU_KEMANA_SAJA);
      }
      break;
    case MESIN_WAKTU:
      if (GTIME.currentTime < 50) {
        GTIME.currentTime = 0;
      } else {
        GTIME.currentTime -= 50;
      }
      printf("Berhasil menggunakan mesin waktu!\n");
      break;
    case SENTER_PENGECIL:
      item = getCurrentItem();
      if (item == NULL) {
        printf("Senter pengecil kamu sia-sia karena tidak ada barang di tas kamu\n");
      } else if (item->type != HEAVY) {
        printf("Senter pengecil kamu sia-sia karena item teratas tas bukan Heavy Item\n");
      } else {
        GSTATS.senterPengecil = true;
      }
      break;
    default:
      break;
  }
}
void buyGadget() {
  // I.S. Inventory terdefinisi, boleh penuh
  // F.S. Apabila uang cukup, uang akan berkurang dan gadget masuk ke inventory
  if (isFullList(GSTATS.inventory)) {
    printf("Inventory sudah penuh. Anda tidak dapat membeli gadget.\n");
  } else if (GSTATS.money < 800) {
    printf("Mobita tidak punya uang cukup untuk membeli gadget apapun (min. 800 Yen).\n");
  } else {
    printf("Uang anda sekarang: %d Yen\n", GSTATS.money);
    printf("Gadget yang tersedia:\n");
    printf("1. Kain Pembungkus Waktu (800 Yen)\n");
    printf("2. Senter Pembesar (1200 Yen)\n");
    printf("3. Pintu Kemana Saja (1500 Yen)\n");
    printf("4. Mesin Waktu (3000 Yen)\n");
    printf("5. Senter Pengecil (800 Yen)\n");
    printf("Gadget mana yang ingin kau beli? (ketik angka 1~5, 0 jika ingin kembali)\n");

    int command = readInt();
    if (command > 0 && command <= 5) {
      if (GSTATS.money < getGadgetPrice(command - 1)) {
        printf("Uang tidak cukup untuk membeli gadget!\n");
      } else {
        insertList(&GSTATS.inventory, command - 1);
        GSTATS.money -= getGadgetPrice(command - 1);
        printf("%s berhasil dibeli!\n", getGadgetName(command - 1));
        printf("Uang anda sekarang: %d Yen\n", GSTATS.money);
      }
    }
  }
}