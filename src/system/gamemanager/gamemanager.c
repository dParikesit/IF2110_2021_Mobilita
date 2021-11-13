#include <stdio.h>
#include "gamemanager.h"
#include "../../helper/pcolor/pcolor.h"

/*  Inisialisasi game manager
	I.S. _gm sembarang
	F.S. _gm terdefinisi kosong, siap untuk memulai permainan */
void initGame() {
	GAME.isFinished = false;
	GAME.isPlaying = false;
	GAME.totalTask = 0;
	initStats();
	CreatePrioQueue(&GTASK);
	initTime();
	initStdin();
}

/*  Tampilkan header berisi status permainan.
	I.S. _gm terdefinisi
	F.S. Menampilkan status permainan */
void displayStatus() {
	int ability = 0;
	printf("\nXXX===  Status\n");
	// Time and it's status
	printf("Waktu: %d (+%d)", GTIME.currentTime, GTIME.deltaTime);
	if (GTIME.isHalt) {
		printf(" %s[HALTED]%s", YELLOW, NEUTRAL);
	}
	// Money and it's status
	printf("\nUang: %d\n", GSTATS.money);
	if (GSTATS.money >= 800) {
		printf("%sINFO%s - Uang kamu cukup untuk membeli gadget.\n", GREEN, NEUTRAL);
	}
	// Pesanan Status
	printf("Pesanan: ");
	printf("%sBerhasil (%d)%s | ", GREEN, GSTATS.totalDeliveredItem, NEUTRAL);
	printf("%sGagal (%d)%s | ", RED, GSTATS.totalFailedItem, NEUTRAL);
	printf("%sSisa (%d)%s | ", YELLOW, GAME.totalTask - (GSTATS.totalDeliveredItem + GSTATS.totalFailedItem), NEUTRAL);
	printf("%sTotal (%d)%s\n", BLUE, GAME.totalTask, NEUTRAL);
	// Mobita position and HQ info
	printf("Mobita Pos: %c (%d, %d)\n", MOBITAPOS->letter, MOBITAPOS->pos.X, MOBITAPOS->pos.Y);
	if (MOBITAPOS == &HQ) {
		printf("%sINFO%s - Mobita di HQ\n", BLUE, NEUTRAL);
	}
	printf("\nXXX=== Items Info\n");
	printf("To Do: %d item(s)\n", lengthListLinked(GSTATS.toDoList));
	printf("In Progress: %d current / %d max item(s) [%d space left]\n",
		(GSTATS.bag.idxTop+1),
		GSTATS.bagCapEff,
		GSTATS.bagCapEff - (GSTATS.bag.idxTop+1)
	);
	// Special item warning
	Item* itemv = getItemInProgressList(VIP);
	if (itemv != NULL) {
		printf(
			"%sWARNING!%s - Ada pesanan VIP di tas kamu! (Dropoff: %s%c%s)\n",
			YELLOW, NEUTRAL,
			BLUE, itemv->dropOff->letter, NEUTRAL
		);
	}
	Item* itemvt = getItemInToDoList(VIP);
	if (itemvt != NULL) {
		printf(
			"%sWARNING!%s - Ada pesanan VIP di to do list! (Pickup: %s%c%s)\n",
			YELLOW, NEUTRAL,
			RED, itemvt->pickUp->letter, NEUTRAL
		);
	}
	Item* itemp = getItemInProgressList(PERISHABLE);
	if (itemp != NULL){
		printf("%sWARNING!%s - Ada pesanan PERISHABLE di tas kamu!\n", YELLOW, NEUTRAL);
	}
	Item* itemh = getItemInProgressList(HEAVY);
	if (itemh != NULL){
		printf("%sWARNING!%s - Ada pesanan HEAVY di tas kamu!\n", YELLOW, NEUTRAL);
	}
	// Dropoff/Pickup item urgent info
	Item* itemct = getCurrentItem();
	if (itemct != NULL && itemct->dropOff == MOBITAPOS) {
		printf("%sURGENT!%s - ", RED, NEUTRAL);
		printf("%s%s di atas bag bisa di drop off disini!%s\n", GREEN, getItemTypeName(itemct->type), NEUTRAL);
	}
	Item* itempk = getPickUpItem();
	if (itempk != NULL) {
		if (itempk->type != VIP && (itemvt != NULL || itemv != NULL)) {
			printf("%sURGENT!%s - ", RED, NEUTRAL);
			printf("%s%s ada disini namun kamu punya VIP item di ", YELLOW, getItemTypeName(itempk->type));
			if (itemvt != NULL) {
				printf("%sto do list%s", RED, YELLOW);
				if (itemv != NULL)
					printf(" dan ");
			}
			if (itemv != NULL)
				printf("%stas%s", BLUE, YELLOW);
			printf(" kamu.%s\n", NEUTRAL);
		} else {
			printf("%sURGENT!%s - ", RED, NEUTRAL);
			printf("%sAda %s yang bisa di pickup disini!%s\n", GREEN, getItemTypeName(itempk->type), NEUTRAL);
		}
	}
	printf("\nXXX=== Efek/Ability %sAktif%s/%sTersisa%s\n", GREEN, NEUTRAL, YELLOW, NEUTRAL);
	if (GSTATS.speedBoostDuration > 0) {
		printf("Speed Boost %s(%ds)%s\n", GREEN, GSTATS.speedBoostDuration, NEUTRAL);
		ability++;
	}
	if (GSTATS.returnToSender > 0) {
		printf("Return to Sender %s(%dx)%s\n", YELLOW, GSTATS.returnToSender, NEUTRAL);
		ability++;
	}
	if (GSTATS.senterPengecil) {
		printf("Senter Pengecil %s(Aktif)%s\n", GREEN, NEUTRAL);
		ability++;
	}
	if (ability == 0) {
		printf("Tidak ada efek/ability yang aktif/tersisa.\n");
	}
	printf("==================================\n");
}

/*  Simpan status permainan ke file.
	I.S. _gm terdefinisi, isPlaying = false.
	F.S. Menuliskan file status permainan ke dalam file, mengembalikan stream ke STDIN. */
void saveGame() {
    FILE* file;
    char* name;
	int i, N;
    printf("Masukkan nama save file: ");
    name = readWord();
	file = fopen(name, "w");
	if (file == NULL) {
		printf("Tidak dapat membuat file. Gagal menyimpan state permainan.\n");
	} else {
		printf("Menyimpan state permainan dengan nama file '%s'\n", name);
		initStream(file, WRITE);

		// Section Map
		SerializeMap();
		// Section Task
		N = lengthQueue(GTASK);
		writeInt(N);
		writeMark();
		for (i = 0; i < N; i++) {
			SerializeItem(GTASK.buffer[i], false);
		}
		// Section Stats
		SerializeStats();
		// Section Time
		SerializeTime();
		// Section Game State
		writeBoolean(GAME.isPlaying);
		writeBoolean(GAME.isFinished);
		writeInt(GAME.totalTask);
		writeChar(MOBITAPOS->letter);
		// Change to STDIN
		initStdin();
		printf("Berhasil menyimpan state permainan!\n");
	}
}

/*  Memuat status permainan dari file untuk melanjutkan permainan.
	I.S. _gm terdefinisi, isPlaying = false
	F.S. Memuat semua status ke game manager untuk melanjutkan permainan. */
void loadGame() {
	FILE* file;
	printf("Masukkan nama file save game: ");
	char* filename = readLine();
	file = fopen(filename, "r");
	if (file == NULL) {
		printf("File save tak dapat diakses atau tak ditemukan. Gagal memuat permainan.\n");
	} else {
		printf("Memuat state permainan dari file '%s'...\n", filename);
		initStream(file, READ);
		// Section Map and Task
		loadLevel();
		// Section Stats
		DeserializeStats();
		// Section Time
		DeserializeTime();
		// Section Game State
		GAME.isPlaying = readBoolean();
		GAME.isFinished = readBoolean();
		GAME.totalTask = readInt();
		MOBITAPOS = getLetterRefBuilding(readChar());
		updateReachable();
		initStdin();
		printf("Berhasil memuat save game. Permainan dimulai!\n");
		displayStatus();
	}
}

/*  Membuat permainan baru dengan map yang ditentukan.
	I.S. _gm terdefinisi, isPlaying = false.
	F.S. Memuat level dari file ke game manager dan memulai permainan. Jika file tak dapat diakses, do nothing. */
void newGame() {
	FILE* file;
	printf("Masukkan nama file konfigurasi level permainan: ");
	char* filename = readWord();
	printf("Nama file: %s\n", filename);
	file = fopen(filename, "r");
	if (file == NULL) {
		printf("File tak dapat diakses atau ditemukan. Gagal memulai permainan baru.\n");
	} else {
		printf("Memuat level dari file %s...\n", filename);
		initStream(file, READ);
		loadLevel();
		initStdin();
		GAME.isPlaying = true;
		GAME.totalTask = lengthQueue(GTASK);
		printf("Berhasil memuat level. Permainan dimulai!\n");
		displayStatus();
	}
}

/*  Memuat konfigurasi level permainan untuk inisialisasi permainan baru.
	I.S. _gm terdefinisi, isPlaying = false, stream terinisialisasi, fileMode = READ
	F.S. Memuat konfigurasi level ke game manager. */
void loadLevel() {
	int i, N;
	// Section Map
    DeserializeMap();
	// Section Task
	N = readInt();
    for (i = 0; i < N; i++) {
        Item* item = malloc(sizeof(Item));
        DeserializeItem(item, false);
		enqueue(&GTASK, item);
    }
}

/*	Keluar dari permainan.
	I.S. _gm sembarang.
	F.S. Keluar dari permainan jika diinginkan user.
	Proses: Menampilkan prompt konfirmasi keluar permainan,
			kemudian keluar dari permainan jika pemain memilih ya. */
void exitGame() {
	printf("Kamu yakin ingin keluar dari permainan? (Y/N) ");
	if(readBoolean()) {
		printf("Terima kasih telah bermain!\n");
		exit(0);
	}
}

/*	Update semua status pada game yang sedang berjalan.
	I.S. _gm terdefinisi, isPlaying = true.
	F.S. Memperbarui status yang diperlukan pada game (core update loop). */
void updateGame() {
	// TODO: Update time
	// Update stats
	updateStats();
}
