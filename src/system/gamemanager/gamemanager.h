#ifndef _GAMEMANAGER_h
#define _GAMEMANAGER_h

#include "../../include/boolean.h"

typedef struct {
	boolean isPlaying;
	boolean isFinished;
} GameManager;

extern GameManager _gm;

void initGame();

#endif
