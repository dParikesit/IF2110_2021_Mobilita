#ifndef TIME_H
#define TIME_H

#include "../../include/boolean.h"

typedef struct Time
{
    int currentTime;
    boolean isPaused;
    boolean isHalt;
} Time;

#define cTime(t) (t).currentTime
#define isPaused(t) (t).isPaused
#define isHalt(t) (t).isHalt;

void advanceTime(Time *t, int addedTime);
//advance currentTime by addedTime

boolean isTimeRunning(Time t);
/*
mengembalikan true jika Time tidak dipause dan dihalt
*/
void initTime(Time *t);
/* 
I.S. Sembarang
F.S Terinisialisasi sebuah Time t dengan kondisi sbb:
-currentTime = 0
-isPaused = false
*/
void SerializeTime(Time *t);
void DeserializeTime(Time *t);

#endif