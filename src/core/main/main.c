#include <stdio.h>
#include "main.h"

GameManager _gm;

int main() {
  printf("Hello World!\n");
  initGame();
  if (isInventoryFull()) {
    printf("Working perfectly!\n");
  }
  return 0;
}
