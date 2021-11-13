#include "command.h"
#include "../../system/gamemanager/gamemanager.h"

int main() {
  CommandType cmd;
  initGame();
  printf("Hello, welcome to Mobita Journey through Alstrokendeath!\n");
  
  showMainMenu();
  showListCommand();
  invalidCommandMsg();

  for (int i=0;i<15;i++) {
    CommandType type = parseCommand();
    printf("COMMAND TYPE: %d", type);
  }

  printf("\n\n");
  // TESTING command
  // HELP AND EXIT selalu bisa dijalankan
  if (isCommandAvailable(HELP) && isCommandAvailable(EXIT))
    printf("EXIT AND HELP SUCCESS\n");
  if (!isCommandAvailable(INVALID))
    printf("INVALID selalu invalid\n");

  // NEW GAME LOAD GAME hanya bisa ketika permainan belum dimulai
  GAME.isPlaying = false;
  if (isCommandAvailable(NEW_GAME) && isCommandAvailable(LOAD_GAME))
    printf("NEW GAME AND LOAD GAME SUCCESS\n");
  
  // BUY hanya bisa ketika mobita ada di HQ
  GAME.isPlaying = true;
  MOBITAPOS = &HQ;
  if (isCommandAvailable(BUY))
    printf("BUY SUCCESS\n");
  
  // RETURN hanya bisa ketika returnToSender > 0
  GSTATS.returnToSender = 1;
  if (isCommandAvailable(RETURN))
    printf("RETURN SUCCESS\n");

  // command yang hanya bisa dijalankan ketika GAME.isPlaying
  GAME.isPlaying = true;
  if (isCommandAvailable(MOVE) && isCommandAvailable(PICK_UP) && isCommandAvailable(DROP_OFF) && isCommandAvailable(MAP) && isCommandAvailable(TO_DO) && isCommandAvailable(IN_PROGRESS) && isCommandAvailable(INVENTORY) && isCommandAvailable(SAVE_GAME))
    printf("MOVE PICK UP DROP OFF MAP TO DO IN PROGRESS BUY INVENTORY SAVE GAME SUCCESS\n");

  return 0;
}