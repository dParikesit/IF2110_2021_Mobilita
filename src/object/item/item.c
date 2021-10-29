#include "item.h"
#include "../../helper/stream/stream.h"

// Mengembalikan nama dari ItemType type.
// N = Normal Item, H = Heavy Item, P = Perishable Item, V = VIP Item
char* getItemTypeName(ItemType type) {
    switch (type) {
        case NORMAL: return "Normal Item";
        case HEAVY: return "Heavy Item";
        case PERISHABLE: return "Perishable Item";
        case VIP: return "VIP Item";
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

void DeserializeItem(Item* b, boolean extended) {
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
