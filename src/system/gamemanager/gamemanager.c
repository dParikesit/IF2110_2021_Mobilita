#include <stdio.h>
#include "gamemanager.h"
void initGame() {
    printf("Initialize game!\n");
    _gm.isPlaying = true;
    _gm.isFinished = false;
}
