#include "map.h"
#include "../gamemanager/gamemanager.h"

boolean isInHQ() {
  return (&HQ == MOBITAPOS);
}

boolean isMobitaThere(Building * elmt) {
  return elmt == MOBITAPOS;
}

int displayAllDestination() {
  int i, counter;

  dealocateListDin(&(TEMP));
  CreateListDin(&(TEMP), ROWS(PATH));

  counter = 1;
  for (i=0;i<LISTDIN_NEFF(BUILDINGLIST);i++) {
    if (!isMobitaThere(LISTDIN_ELMT(BUILDINGLIST, i))) {
      printf("%d. ", counter);
      displayBuilding(LISTDIN_ELMT(BUILDINGLIST, i));
      printf("\n");

      insertLastListDin(&TEMP, LISTDIN_ELMT(BUILDINGLIST, i));
      counter++;
    }
  }
  return LISTDIN_NEFF(BUILDINGLIST)-1;
}

boolean navigateAndMoveMobita(boolean fromPintuKemanaSaja) {
  int countReachableBuildings, input;

  printf("Posisi yang dapat dicapai: \n");
  if (!fromPintuKemanaSaja)
    countReachableBuildings = displayReachableDestination();
  else
    countReachableBuildings = displayAllDestination();
  printf("Posisi yang dipilih? (ketik 0 jika ingin kembali)\n\n");
  
  printf("ENTER COMMAND: ");
  input = readInt();
  if (input > countReachableBuildings || input <= 0) {
    if (input != 0)
      printf("Input tidak valid. Membatalkan...\n");
    updateReachable();
    return false;
  } else if (input <= countReachableBuildings && input > 0) {
    MOBITAPOS = LISTDIN_ELMT(TEMP, input-1);
    printf("Mobita sekarang berada di titik ");
    displayBuilding(LISTDIN_ELMT(TEMP, input-1));
    printf("\n");
    updateReachable();
    return true;
  }
}
// Show reachable destination from current position and move player to desired destination.
void displayMap() {
  displayMatrix(LOC);
} // Display map to stdin

void addAsteriskAndBlank() {
  int i, j;
  
  for (i=1;i<ROWS(LOC);i++) {
    for (j=1;j<COLS(LOC);j++) {
      ELMT(LOC, i,j) = ' ';
    }
  }
  for (j=0;j<COLS(LOC);j++) {
    ELMT(LOC, 0, j) = '*';
  }
  for (i=1;i<=ROWS(LOC);i++) {
    ELMT(LOC, i, 0) = '*';
    ELMT(LOC, i, COLS(LOC)-1) = '*';
  }
  for (j=0;j<COLS(LOC);j++) {
    ELMT(LOC, ROWS(LOC)-1, j) = '*';
  }
}

void initMap(int rowInput, int colInput) {
  int i;
  Building elmt;

  ROWS(LOC) = rowInput + 2;
  COLS(LOC) = colInput + 2;

  addAsteriskAndBlank();
  for (i=0; i<LISTDIN_NEFF(BUILDINGLIST);i++) {
    elmt = *LISTDIN_ELMT(BUILDINGLIST, i);
    ELMT(LOC, Absis(POS(elmt)), Ordinat(POS(elmt))) = LETTER(elmt);
  }
}

void SerializeMap() {
  int i, j;

  writeInt(ROWS(LOC)-2);
  writeInt(COLS(LOC)-2);
  writeMark();

  writeInt(Absis(POS(HQ)));
  writeInt(Ordinat(POS(HQ)));
  writeMark();

  writeInt(LISTDIN_NEFF(BUILDINGLIST) - 1);
  writeMark();

  Building write;
  for (i=1;i<LISTDIN_NEFF(BUILDINGLIST);i++) {

    SerializeBuilding(LISTDIN_ELMT(BUILDINGLIST, i));
  }
  for (i=0;i<ROWS(PATH);i++) {
    for (j=0;j<COLS(PATH);j++) {
      writeInt(ELMT(PATH, i, j));
    }
    writeMark();
  }
}
void DeserializeMap() {
  int rowsMap, colsMap;
  int hqAbsis, hqOrdinat;
  int adjacencyMatSize;
  int i, j;
  Building hq;

  rowsMap = readInt();
  colsMap = readInt();
  initMap(rowsMap, colsMap);

  hqAbsis = readInt();
  hqOrdinat = readInt();

  LETTER(HQ) = '8';
  Absis(POS(HQ)) = hqAbsis;
  Ordinat(POS(HQ)) = hqOrdinat;
  MOBITAPOS = &HQ;

  adjacencyMatSize = readInt();
  ROWS(PATH) = adjacencyMatSize+1;
  COLS(PATH) = adjacencyMatSize+1;

  CreateListDin(&(BUILDINGLIST), adjacencyMatSize+1);
  insertLastListDin(&BUILDINGLIST, &HQ);
  addBuildingToLoc(&HQ);
  for (i = 1; i <= adjacencyMatSize; i++) {
    Building* newb = (Building*) malloc(sizeof(Building));
    DeserializeBuilding(newb);
    insertLastListDin(&BUILDINGLIST, newb);
    addBuildingToLoc(newb);
  }
  LISTDIN_NEFF(BUILDINGLIST) = adjacencyMatSize+1;

  for (i=0; i <= adjacencyMatSize; i++) {
    for (j = 0; j <= adjacencyMatSize; j++) {
      ELMT(PATH, i, j) = readInt();
    }
  }
  updateReachable();
}
// loc should be computed 

void addBuildingToLoc(Building* elmt) {
  ELMT(LOC, Absis(POS(*elmt)), Ordinat(POS(*elmt))) = LETTER(*elmt);
}

void updateReachable() {
  int i, j, counter;
  boolean found;
  
  // CreateListDin(&(TEMP), ROWS(PATH));
  found = false;
  i=0;
  while (!found && i < LISTDIN_NEFF(BUILDINGLIST)) {
    if (isMobitaThere(LISTDIN_ELMT(BUILDINGLIST, i))) {
      found = true;
    } else {
      i++;
    }
  }
  dealocateListDin(&(TEMP));
  CreateListDin(&(TEMP), ROWS(PATH));
  counter = 0;
  for (j=0; j < LISTDIN_NEFF(BUILDINGLIST); j++) {
    if (ELMT(PATH, i, j)) {
      insertLastListDin(&(TEMP), LISTDIN_ELMT(BUILDINGLIST, j));
    }
  }
}

int displayReachableDestination() {
  for (int i=0; i< LISTDIN_NEFF(TEMP); i++) {
    printf("%d. ", i+1);
    displayBuilding(LISTDIN_ELMT(TEMP, i));
    printf("\n");
  }

  return LISTDIN_NEFF(TEMP);
}

boolean isLetterInReachable(char letter) {
  boolean found;
  int i;

  found = false;
  i=0;
  while (!found && i < LISTDIN_NEFF(TEMP)) {
    // displayBuilding(LISTDIN_ELMT(TEMP, i));
    if (letter == LETTER(*LISTDIN_ELMT(TEMP, i))) {
      found = true;
    } else {
      i++;
    }
  }
  // printf("%d", found);
  return found;
}
