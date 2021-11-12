#include <stdio.h>
#include "gamemanager.h"

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
	F.S. Menampilkan waktu. */
void displayStatus() {
	printf("\nWaktu: %d\nUang: %d\n", GTIME.currentTime, GSTATS.money);
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
			SerializeItem(GTASK.buffer[i]);
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
		loadLevel(true);
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
		loadLevel(false);
		initStdin();
		printf("Berhasil memuat level. Permainan dimulai!\n");
		GAME.isPlaying = true;
		GAME.totalTask = lengthQueue(GTASK);
	}
}

/*  Memuat konfigurasi level permainan untuk inisialisasi permainan baru.
	I.S. _gm terdefinisi, isPlaying = false, stream terinisialisasi, fileMode = READ
	F.S. Memuat konfigurasi level ke game manager. */
void loadLevel(boolean isLoadGame) {
	int i, N;
	// Section Map
    DeserializeMap();
	// Section Task
	N = readInt();
    for (i = 0; i < N; i++) {
        Item* item = malloc(sizeof(Item));
        DeserializeItem(item, isLoadGame);
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
