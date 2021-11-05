#include "stats.h"
#include "../../include/wrapper.h"
#include "../../helper/stream/stream.h"

/* Inisialisasi stats ke nilai awal.
   I.S. Stats sembarang.
   F.S. Inisialisasi stats menjadi nilai default. */
void initStats() {
    _gm.stats.bagCapEff = 3;
    _gm.stats.money = 0;
    _gm.stats.returnToSender = 0;
    _gm.stats.senterPengecil = false;
    _gm.stats.speedBoostDuration = 0;
}

void SerializeStats() {
    // TODO: 1. Gadget Inventory.
    // TODO: 2. To Do List.
    // TODO: 3. In Progress List.
    // 4. Leftover Properties.
    // "<money> <senterPengecil> <returnToSender> <speedBoostDuration> <bagCapEff>\n"
    writeInt(_gm.stats.money);
    writeBoolean(_gm.stats.senterPengecil);
    writeInt(_gm.stats.returnToSender);
    writeInt(_gm.stats.speedBoostDuration);
    writeInt(_gm.stats.bagCapEff);
    writeMark();
}

void DeserializeStats() {
    // TODO: 1. Gadget Inventory.
    // TODO: 2. To Do List.
    // TODO: 3. In Progress List.
    // 4. Leftover Properties.
    // "<money> <senterPengecil> <returnToSender> <speedBoostDuration> <bagCapEff>\n"
    _gm.stats.money = readInt();
    _gm.stats.senterPengecil = readBoolean();
    _gm.stats.returnToSender = readInt();
    _gm.stats.speedBoostDuration = readInt();
    _gm.stats.bagCapEff = readInt();
}
