#ifndef _GAMEMANAGER_h
#define _GAMEMANAGER_h

#include "../../include/boolean.h"
#include "../../helper/stream/stream.h"
#include "../../system/stats/stats.h"
#include "../../system/map/map.h"
#include "../../system/time/time.h"
#include "../../adt/queue/prioqueue.h"

// Singleton Game Manager
typedef struct GameManager {
	// Menyimpan map
	Map map;
	// Menyimpan status dari game saat ini.
	Stats stats;
	// Menyimpan daftar pesanan yang belum masuk waktunya.
	PrioQueue task;
	// Menyimpan waktu dan status waktu permainan.
	Time time;
	// Apakah game sedang berjalan?
	boolean isPlaying;
	// Apakah game sudah selesai?
	boolean isFinished;
	// Total pesanan yang dapat diambil Mobita
	int totalTask;
} GameManager;

// Instansi utama GameManager yang bisa diakses secara global
extern GameManager _gm;

// Definisi instansi global sistem

#define GAME _gm
#define GTIME GAME.time
#define GMAP GAME.map
#define GSTATS GAME.stats
#define GTASK GAME.task

/*  Inisialisasi game manager
	I.S. _gm sembarang
	F.S. _gm terdefinisi kosong, siap untuk memulai permainan */
void initGame(); 
/*  Tampilkan header berisi status permainan.
	I.S. _gm terdefinisi
	F.S. Menampilkan waktu. */
void displayStatus();

/*	SAVE GAME FORMAT: <filename>.strkdat
	
	loadLevel Layout:
	<map>
	<task_length>
	<task item not extended>
	
	loadGame/saveGame Layout:
	<map>
	<task_length>
	<task item not extended>
	<stats>
	<time>
	<isPlaying> <isFinished>
*/

/*  Simpan status permainan ke file.
	I.S. _gm terdefinisi, isPlaying = false.
	F.S. Menuliskan file status permainan ke dalam file. */
void saveGame();
/*  Memuat status permainan dari file untuk melanjutkan permainan.
	I.S. _gm terdefinisi, isPlaying = false
	F.S. Memuat semua status ke game manager untuk melanjutkan permainan. */
void loadGame();
/*  Membuat permainan baru dengan map yang ditentukan.
	I.S. _gm terdefinisi, isPlaying = false.
	F.S. Memuat level dari file ke game manager dan memulai permainan */
void newGame();
/*  Memuat konfigurasi level permainan untuk inisialisasi permainan baru.
	I.S. _gm terdefinisi, isPlaying = false.
	F.S. Memuat konfigurasi level ke game manager. */
void loadLevel(boolean isLoadGame);
/*	Keluar dari permainan.
	I.S. _gm sembarang.
	F.S. Keluar dari permainan. */
void exitGame();
/*	Update semua status pada game yang sedang berjalan.
	I.S. _gm terdefinisi, isPlaying = true.
	F.S. Memperbarui status yang diperlukan pada game (core update loop). */
void updateGame();

#endif
