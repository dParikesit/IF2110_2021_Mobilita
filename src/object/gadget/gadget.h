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

boolean isInventoryFull(); // Check if inventory is full
void addGadget(GadgetType gadget); // Add gadget to inventory
void getGadgetName(GadgetType gadget);
void getGadgetPrice(GadgetType gadget);
void useGadget(); // Show command logic for using gadget, also call applyEffect
void applyGadget(GadgetType gadget); // Apply effect of the selected gadget
void buyGadget();
void listGadget();

#endif