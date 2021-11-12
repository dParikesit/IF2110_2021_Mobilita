#ifndef TIME_H
#define TIME_H

#include "../../include/boolean.h"

typedef struct Time
{
    int currentTime;
    int deltaTime;
    boolean isHalt;
} Time;

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
void SerializeTime();
void DeserializeTime();

#endif