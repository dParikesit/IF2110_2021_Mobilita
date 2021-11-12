#include <stdio.h>
#include "main.h"
#include "../command/command.h"
#include "../../system/gamemanager/gamemanager.h"

GameManager _gm;

int main() {
  CommandType cmd;
  initGame();
  printf("Hello, welcome to Mobita Journey through Alstrokendeath!\n");
  do {
    cmd = parseCommand();
    if (isCommandAvailable(cmd)) {
      runCommand(cmd);
    }
    if (GAME.isPlaying) {
      displayStatus();
    }
  } while(true);
  return 0;
}
