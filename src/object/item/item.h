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
	struct Building* pickUp;
	// Bangunan drop off item.
	struct Building* dropOff;
	// Tipe item.
	ItemType type;
	// Durasi maksimum item (untuk perishable item).
	int maxDuration;
	// Durasi sisa item (untuk perishable item).
	int currentDuration;
} Item;

// Serialization Guide
/* Format:
   "<timePickUp> <pickUp.letter> <dropOff.letter> <type> <maxDuration> <currentDuration>\n"
	NB:
	- In serialization, maxDuration and currentDuration will only be written if type = PERISHABLE
	- In deserialization, maxDuration will be read if type = PERISHABLE
	  -> if extended, currentDuration will be read too (if not, will set the same as maxDuration)
*/

/* Menuliskan item ke dalam stream.
   I.S. Item terdefinisi, stream terdefinisi, fileMode = WRITE.
   F.S. Menuliskan item ke dalam stream. */
void SerializeItem(Item b);

/* Membaca stream dan parse ke Item.
   I.S. Item sembarang, stream terdefinisi, fileMode = WRITE.
   F.S. Menginisialisasi Item dengan data di stream. */
void DeserializeItem(Item* b, boolean extended);

#endif