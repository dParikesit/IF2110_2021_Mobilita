// File: item.h
// Definisi object item dan fungsi yang berkaitan

#ifndef ITEM_h
#define ITEM_h

#include "../../include/boolean.h"
#include "../building/building.h"

typedef enum ItemType {
	NORMAL = 'N',
	HEAVY = 'H',
	PERISHABLE = 'P',
	VIP = 'V'
} ItemType;

// Mengembalikan nama dari ItemType type.
// N = Normal Item, H = Heavy Item, P = Perishable Item, V = VIP Item
char* getItemTypeName(ItemType type);

// Definisi tipe struct Item
typedef struct Item {
	// Waktu pick up item.
	int timePickUp;
	// Bangunan pick up item.
	Building* pickUp;
	// Bangunan drop off item.
	Building* dropOff;
	// Tipe item.
	ItemType type;
	// Durasi maksimum item (untuk perishable item).
	int maxDuration;
	// Durasi sisa item (untuk perishable item).
	int currentDuration;
} Item;

Item *getCurrentItem();
// Get a pointer Item on the top of the bag

Item *getPickUpItem();
// Get a pointer to first item that can be picked up in current mobitaPos

boolean toDoListHas(ItemType type);
// Check if toDoList has given ItemType (for checking if there’s VIP Item or so)

boolean inProgressListHas(ItemType type);
// Check if inProgressList has given ItemType (for checking if there’s Heavy Item or so)

Item* getItemInProgressList(ItemType type);
// Get first item in progress list that has ItemType == type
// Guaranteed has it

void updateItem();
// I.S. inProgressList terdefinisi
// F.S. Semua PERISHABLE di inProgressList akan berkurang current duration nya

boolean isEqualItem(Item item1, Item item2);
// Compare two items and return whether both items are equal

/********** Serialization Guide **********/
/* Format:
   "<timePickUp> <pickUp.letter> <dropOff.letter> <type> <maxDuration> <currentDuration>\n"
	NB:
	- In serialization, maxDuration and currentDuration will only be written if type = PERISHABLE
	- In deserialization, maxDuration will be read if type = PERISHABLE
	  -> if extended, currentDuration will be read too (if not, will set the same as maxDuration)
*/

void SerializeItem(Item* b);
/* Menuliskan item ke dalam stream.
   I.S. Item terdefinisi, stream terdefinisi, fileMode = WRITE.
   F.S. Menuliskan item ke dalam stream. */

void DeserializeItem(Item *b, boolean extended);
/* Membaca stream dan parse ke Item.
   I.S. Item sembarang, stream terdefinisi, fileMode = WRITE.
   F.S. Menginisialisasi Item dengan data di stream. */

#endif