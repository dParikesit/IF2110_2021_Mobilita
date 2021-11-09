#ifndef _GADGET_h
#define _GADGET_h

#include "../../include/boolean.h"

typedef enum GadgetType {
	NONE = -1,
	KAIN_PEMBUNGKUS_WAKTU = 0,
	SENTER_PEMBESAR = 1,
	PINTU_KEMANA_SAJA = 2,
	MESIN_WAKTU = 3,
	SENTER_PENGECIL = 4
} GadgetType;

boolean isInventoryFull();
// Mengecek apakah inventory full, yaitu ketika panjang list==capacity

void addGadget(GadgetType gadget);
// Add gadget to inventory
// I.S. Inventory terdefinisi dan tidak penuh
// F.S. gadget masuk ke inventory

char *getGadgetName(GadgetType gadget);
// I.S. gadget terdefinisi tipe nya
// F.S. print nama gadget tanpa diakhiri karakter apapun

int getGadgetPrice(GadgetType gadget);
// Return harga gadget

void showAndUseGadget();
// I.S. inventory terdefinisi
// F.S. print daftar inventory, kemudian memanggil apply gadget yang dipilih

void applyGadget(GadgetType gadget); // Apply effect of the selected gadget

void buyGadget();
// I.S. Inventory terdefinisi, boleh penuh
// F.S. Apabila uang cukup, uang akan berkurang dan gadget masuk ke inventory

#endif