#include "time.h"
#include "../gamemanager/gamemanager.h"
#include "../../include/boolean.h"
#include "../../core/gameplay/gameplay.h"

void advanceTime()
//advance currentTime by addedTime
{
    cTime(GTIME) += countTimeAddition();
}

boolean isTimeRunning()
/*
mengembalikan true jika Time tidak dipause dan dihalt
*/
{
    return (!isPaused(GTIME) && !isHalt(GTIME));
}
void initTime()
/* 
I.S. Sembarang
F.S Terinisialisasi sebuah Time t dengan kondisi sbb:
-currentTime = 0
-isHalted = false
*/
{
    cTime(GTIME) = 0;
    isHalt(GTIME) = false;
}