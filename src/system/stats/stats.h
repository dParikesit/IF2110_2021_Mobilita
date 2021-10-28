#ifndef STATS_h
#define STATS_h
#include "../../include/boolean.h"

/* Gameplay Status. */
typedef struct Stats {
	// Daftar gadget yang dipunyai oleh mobita.
   //List inventory; 
   // Daftar pesanan yang bisa di pick up mobita.
   //ListLinked toDoList;
   // Daftar pesanan yang sudah di pick up mobita.
	//Stack bag;
   // Daftar pesanan yang sudah di pick up mobita (seperti bag)
	//ListLinked inProgressList;
	// Uang mobita. Dimulai dengan 0.
   int money;
   // Banyaknya ability returnToSender yang dimiliki mobita.
   // Jika 0, maka mobita tak punya ability ini.
	int returnToSender;
   // Durasi ability speed boost yang dimiliki mobita
   // Jika 0, maka mobita tak punya ability ini.
	int speedBoostDuration;
   // Kapasitas efektif tas mobita. Dimulai dengan 3.
	int bagCapEff;
   // Apakah senter pengecil aktif?
   // Jika true, efek heavy item di top stack akan hilang hingga drop off/return.
	boolean senterPengecil;
} Stats;

// NOTE: Instance Stats yang dipakai akan selalu menggunakan _gm.stats

/* Update stats yang diperlukan.
   I.S. Stats terinisiasi.
   F.S. Update durasi perishable dan speed boost. */
void updateStats();

/* Tampilkan to do ke layar.
   I.S.  toDoList terdefinisi, mungkin kosong.
   F.S.  Menampilkan to do ke layar. */
void displayToDo();
/* Format:
   Header: "Pesanan pada To Do List:\n"
   Format: "<x=1...N>. <item[x].pickUp.letter> -> <item[x].dropOff.letter> (getItemTypeName(<item[x].type>))\n" */

/* Tampilkan in progress list ke layar.
   I.S. inProgressList terdefinisi, mungkin kosong.
   F.S. Menampilkan in progress list ke layar. */
void displayInProgress();
/* Format:
   Header: "Pesanan yang sedang diantarkan:\n"
   Format: "<x=1...N>. <item[x].type> (Tujuan: <item[x].dropOff.letter>)\n" */

/* Inisialisasi stats ke nilai awal.
   I.S. Stats sembarang.
   F.S. Inisialisasi stats menjadi nilai default. */
void initStats();
/* Properti yang diinisialisasi:
   money = 0
   returnToSender = 0
   speedBoostDuration = 0
   bagCapEff = 3
   Membuat inventory, bag, toDoList & inProgressList.
*/

// Serialization Guide
/* Format:
   1. Gadget Inventory.
   "<x=0..len(inventory)-1>\n"
   "<gadget[0]> ... <gadget[x]>\n" - Space delimited.
   NB: gadget[x] = (int)GadgetType. Could be -1.

   2. To Do List.
   "<x=0..len(toDoList)-1>\n"
   SerializeItem(item[x]) / DeserializeItem(item[x], true)

   3. In Progress List.
   "<x=0..len(inProgressList)-1>\n"
   SerializeItem(item[x]) / DeserializeItem(item[x], true)
   Deserialization Note: Also deserialize bag within this data.

   4. Leftover Properties.
   "<money> <senterPengecil> <returnToSender> <speedBoostDuration> <bagCapEff>\n"
*/

/* Menuliskan stats ke dalam stream.
   I.S. Stats terdefinisi, stream terdefinisi, fileMode = WRITE.
   F.S. Menuliskan stats ke dalam stream. */
void SerializeStats();

/* Membaca stream dan parse ke instance Stats.
   I.S. Stats sembarang, stream terdefinisi, fileMode = WRITE.
   F.S. Menginisialisasi Stats dengan data di stream. */
void DeserializeStats();

#endif