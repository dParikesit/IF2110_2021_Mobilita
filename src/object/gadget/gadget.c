#include "gadget.h"

#include "../../include/wrapper.h"
// TODO Careful import
#include "../../system/map/map.h"
#include "../../system/time/time.h"

boolean isInventoryFull() {
  // Mengecek apakah inventory full, yaitu ketika panjang list==capacity
  return length(_gm.stats.inventory) == INV_CAP;
}
void addGadget(GadgetType gadget) {
  // Add gadget to inventory
  // I.S. Inventory terdefinisi dan tidak penuh
  // F.S. gadget masuk ke inventory
  insertList(&_gm.stats.inventory, gadget);
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
  for (int i = 0; i < INV_CAP; i++) {
    printf("%d. %s\n", (i + 1), getGadgetName(LIST_ELMT(_gm.stats.inventory, i)));
  }
  printf("Gadget mana yang ingin digunakan? (ketik 0 jika ingin kembali)\n\n");
  printf("ENTER COMMAND: ");  //Fungsi buat enter command apa ya?
  scanf("%d", &command);

  applyGadget(LIST_ELMT(_gm.stats.inventory, command - 1));
  deleteAtList(&_gm.stats.inventory, command-1);
}
void applyGadget(GadgetType gadget) {
  // Apply effect of the selected gadget
  switch (gadget) {
    case KAIN_PEMBUNGKUS_WAKTU:
      if(inProgressListHas(PERISHABLE)){
        Item *perishableItem = getItemInProgressList(PERISHABLE);
        perishableItem->currentDuration = perishableItem->maxDuration;
      }
    case SENTER_PEMBESAR:
      _gm.stats.bagCapEff *= 2;
      if(_gm.stats.bagCapEff > BAG_CAP){
        _gm.stats.bagCapEff = BAG_CAP;
      }
    case PINTU_KEMANA_SAJA:
      int x,y;
      printf("Masukkan koordinat x: ");
      scanf("%d", &x);
      printf("Masukkan koordinat y: ");
      scanf("%d", &y);

      // TODO gimana cara pake fungsi ini???
      navigateAndMoveMobita();
    case MESIN_WAKTU:
      if(time.currentTime < 50 ){
        time.currentTime = 0;
      } else{
        time.currentTime -= 50;
      }
    case SENTER_PENGECIL:
      if (inProgressListHas(HEAVY)==true){
        _gm.stats.senterPengecil = true;
      }
    default:
      break;
  }
}
void buyGadget() {
  // I.S. Inventory terdefinisi, boleh penuh
  // F.S. Apabila uang cukup, uang akan berkurang dan gadget masuk ke inventory
  if (isFullList(_gm.stats.inventory)) {
    printf("Inventory sudah penuh. Anda tidak dapat membeli gadget.\n");
  } else {
    printf("Uang anda sekarang: %d Yen", _gm.stats.money);
    printf("Gadget yang tersedia:\n");
    printf("1. Kain Pembungkus Waktu (800 Yen)\n");
    printf("2. Senter Pembesar (1200 Yen)\n");
    printf("3. Pintu Kemana Saja (1500 Yen)\n");
    printf("4. Mesin Waktu (3000 Yen)\n");
    printf("5. Senter Pengecil (800 Yen)\n");
    printf("Gadget mana yang ingin kau beli? (ketik 0 jika ingin kembali)\n\n");

    int command;
    scanf("%d", &command);
    if (command != 0) {
      if (_gm.stats.money < getGadgetPrice(command - 1)) {
        printf("Uang tidak cukup untuk membeli gadget!\n");
      } else {
        insertList(&_gm.stats.inventory, command - 1);
        _gm.stats.money -= getGadgetPrice(command - 1);
        printf("%s berhasil dibeli!\n", getGadgetName(command - 1););
        printf("Uang anda sekarang: %d Yen\n", _gm.stats.money);
      }
    }
  }
}