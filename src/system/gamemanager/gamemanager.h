#ifndef _GAMEMANAGER_h
#define _GAMEMANAGER_h

#include "../../include/boolean.h"
#include "../../helper/stream/stream.h"
#include "../../system/stats/stats.h"
#include "../../adt/queue/prioqueue.h"

typedef struct GameManager {
	struct Stats stats;
	struct PrioQueue task;
	boolean isPlaying;
	boolean isFinished;
} GameManager;

extern GameManager _gm;

void initGame();

#endif
