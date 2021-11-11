#ifndef TIME_H
#define TIME_H

#include "../../include/boolean.h"

typedef struct Time
{
    int currentTime;
    int deltaTime;
    boolean isPaused;
    boolean isHalt;
} Time;

#define cTime(t) (t).currentTime
#define isPaused(t) (t).isPaused
#define isHalt(t) (t).isHalt
#define deltaTime(t) (t).deltaTime

void advanceTime();
//advance currentTime by addedTime

boolean isTimeRunning();
/*
mengembalikan true jika Time tidak dipause dan dihalt
*/
void initTime();
/* 
I.S. Sembarang
F.S Terinisialisasi sebuah Time t dengan kondisi sbb:
-currentTime = 0
-isPaused = false
*/
void SerializeTime(Time *t);
void DeserializeTime(Time *t);

#endif