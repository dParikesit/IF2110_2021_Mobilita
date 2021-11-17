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

  if (command > 5 || command < 0) {
    printf("Input tidak valid. Membatalkan...\n");
    return;
  }

  GadgetType gadget = LIST_ELMT(GSTATS.inventory, command - 1);

  if (gadget == NONE) {
    printf("Tidak ada gadget pada slot %d. Membatalkan...\n", command);
    return;
  } else {
    deleteAtList(&GSTATS.inventory, command - 1);
    applyGadget(gadget);
  }
}
void applyGadget(GadgetType gadget) {
  int x, y;
  Item *item;
  // Apply effect of the selected gadget
  switch (gadget) {
    case KAIN_PEMBUNGKUS_WAKTU:
      item = getCurrentItem();
      if (item != NULL && item->type == PERISHABLE && item->currentDuration != item->maxDuration) {
        item->currentDuration = item->maxDuration;
        printf("Berhasil mengubah durasi item perishable ke semula!\n");
      } else {
        printf("Selamat, Mobita menggunakan kain pembungkus waktunya dengan sia-sia :)\n");
      }
      break;
    case SENTER_PEMBESAR:
      if (GSTATS.bagCapEff == BAG_CAP) {
        printf("Tas sudah berukuran maksimal. Selamat, Mobita menggunakan senter pembesar dengan sia-sia :)\n");
      } else {
        GSTATS.bagCapEff *= 2;
        if (GSTATS.bagCapEff > BAG_CAP) {
          GSTATS.bagCapEff = BAG_CAP;
        }
        printf("Berhasil menggunakan senter pembesar! Tas kamu sekarang berukuran %d\n", GSTATS.bagCapEff);
      }
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
      if (GTIME.currentTime == 0) {
        printf("Selamat, Mobita menggunakan mesin waktu dengan sia-sia :)\n");
      } else {
        if (GTIME.currentTime < 50) {
          GTIME.currentTime = 0;
        } else {
          GTIME.currentTime -= 50;
        }
        printf("Berhasil menggunakan mesin waktu! Waktu sekarang: %d\n", GTIME.currentTime);
      }
      break;
    case SENTER_PENGECIL:
      item = getCurrentItem();
      if (item != NULL && item->type == HEAVY && GSTATS.senterPengecil == false) {
        printf("Berhasil mengaktifkan efek Senter Pengecil!\n");
        GSTATS.senterPengecil = true;
      } else {
        printf("Selamat, Mobita menggunakan senter pengecilnya dengan sia-sia :)\n");
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
    printf("Inventory sudah penuh. Mobita tidak dapat membeli gadget.\n");
  } else if (GSTATS.money < 800) {
    printf("Mobita tidak punya uang cukup untuk membeli gadget apapun (min. 800 Yen).\n");
  } else {
    printf("Uang Mobita sekarang: %d Yen\n", GSTATS.money);
    printf("Gadget yang tersedia:\n");
    printf("1. Kain Pembungkus Waktu (800 Yen)\n");
    printf("2. Senter Pembesar (1200 Yen)\n");
    printf("3. Pintu Kemana Saja (1500 Yen)\n");
    printf("4. Mesin Waktu (3000 Yen)\n");
    printf("5. Senter Pengecil (800 Yen)\n");
    printf("Gadget mana yang ingin Mobita beli? (ketik angka 1~5, 0 jika ingin kembali)\n");

    int command = readInt();
    if (command > 0 && command <= 5) {
      if (GSTATS.money < getGadgetPrice(command - 1)) {
        printf("Uang tidak cukup untuk membeli gadget tersebut! Membatalkan...\n");
      } else {
        insertList(&GSTATS.inventory, command - 1);
        GSTATS.money -= getGadgetPrice(command - 1);
        printf("%s berhasil dibeli!\n", getGadgetName(command - 1));
        printf("Uang Mobita sekarang: %d Yen\n", GSTATS.money);
      }
    } else if (command > 5) {
      printf("Tidak ada gadget dengan nomor tersebut! Membatalkan...\n");
    }
  }
}