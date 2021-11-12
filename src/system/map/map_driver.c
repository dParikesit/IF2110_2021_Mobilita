#include "map.h"
#include "../gamemanager/gamemanager.h"

int main() {
  printf("Hello World!\n");

  FILE* fin;
  FILE* fout;
  fin = fopen("../test/config.txt", "r");
  fout = fopen("../test/output.txt", "w");
  if (fin == NULL) {
    printf("file not found\n");
  } else {
    initStream(fin, READ);
    DeserializeMap();
    displayMap();printf("\n");
    printf("reachable: \n");
    displayReachableDestination();

    if (fout == NULL) {
      printf("file OUTPUT not found\n");
    } else {
      printf("writing\n");
      initStream(fout, WRITE);
      SerializeMap();
    }
  }

  return 0;
}