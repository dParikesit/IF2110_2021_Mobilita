#include "../../include/wrapper.h"
#include "../../core/gameplay/gameplay.h"
#include "time.h"

void advanceTime()
//advance currentTime by addedTime
{
    if (GTIME.isHalt) {
        GTIME.isHalt = false;
    } else {
        if (GSTATS.speedBoostDuration > 0) {
            GTIME.isHalt = true;
            GSTATS.speedBoostDuration -= GTIME.deltaTime;
        }
        GTIME.deltaTime = countTimeAddition();
        GTIME.currentTime += GTIME.deltaTime;
    }
}

boolean isTimeRunning()
/*
mengembalikan true jika Time tidak dipause dan dihalt
*/
{
    return (!GTIME.isHalt);
}

void initTime()
/* 
I.S. Sembarang
F.S Terinisialisasi sebuah Time t dengan kondisi sbb:
-currentTime = 0
-GTIME.isHalted = false
*/
{
    GTIME.currentTime = 0;
    GTIME.isHalt = false;
    GTIME.deltaTime = 0;
}

void SerializeTime() {
    writeInt(GTIME.currentTime);
    writeInt(GTIME.deltaTime);
    writeBoolean(GTIME.isHalt);
    writeMark();
}

void DeserializeTime() {
    GTIME.currentTime = readInt();
    GTIME.deltaTime = readInt();
    GTIME.isHalt = readBoolean();
}
