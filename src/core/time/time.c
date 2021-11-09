#include "time.h"

void advanceTime(Time *t, int addedTime)
//advance currentTime by addedTime
{
    cTime(*t) = cTime(*t) + addedTime;
}

boolean isTimeRunning(Time t)
/*
mengembalikan true jika Time tidak dipause dan dihalt
*/
{
    return (!isPaused(t) && !t.isHalt);
}
void initTime(Time *t)
/* 
I.S. Sembarang
F.S Terinisialisasi sebuah Time t dengan kondisi sbb:
-currentTime = 0
-isPaused = false
*/
{
    cTime(*t) = 0;
    isPaused(*t)  = false;
}