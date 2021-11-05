/* File : prioqueue.h */
/* Representasi priority queue dengan array eksplisit dan alokasi stastik */
/* Queue terurut mengecil berdasarkan waktu masuk pesanan (timePickUp). */
#ifndef PRIOQUEUE_H
#define PRIOQUEUE_H

#include "../../include/constants.h"
#include "../../include/boolean.h"
#include "../../object/item/item.h"
#include <stdlib.h>

/* Konstanta */
#define QUEUE_CAPACITY TASK_CAP

/* Deklarasi ElTypeQueue */
typedef Item ElTypeQueue;

/* Definisi PrioQueue */
typedef struct PrioQueue {
	ElTypeQueue buffer[QUEUE_CAPACITY];
	int idxHead;
	int idxTail;
} PrioQueue;

/* ********* AKSES (Selektor) ********* */
/* Jika pq adalah PrioQueue, maka akses elemen : */
#define QUEUE_IDX_HEAD(pq) (pq).idxHead
#define QUEUE_IDX_TAIL(pq) (pq).idxTail
#define     QUEUE_HEAD(pq) (pq).buffer[(pq).idxHead]
#define     QUEUE_TAIL(pq) (pq).buffer[(pq).idxTail]

/* *** Kreator *** */
void CreatePrioQueue(PrioQueue *pq);
/* I.S. sembarang */
/* F.S. Sebuah pq kosong terbentuk dengan kondisi sbb: */
/* - Index head bernilai IDX_UNDEF */
/* - Index tail bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah pq kosong */

boolean isEmptyQueue(PrioQueue pq);
/* Mengirim true jika pq kosong: lihat definisi di atas */

boolean isFullQueue(PrioQueue pq);
/* Mengirim true jika tabel penampung elemen pq sudah penuh */
/* yaitu jika index head bernilai 0 dan index tail bernilai QUEUE_CAPACITY-1 */

int lengthQueue(PrioQueue pq);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika pq kosong. */

/*** Primitif Add/Delete ***/
void enqueue(PrioQueue *pq, ElTypeQueue val);
/* Proses: Menambahkan val pada pq dengan aturan FIFO */
/* I.S. pq mungkin kosong, tabel penampung elemen pq TIDAK penuh */
/* F.S. val menjadi QUEUE_TAIL yang baru, QUEUE_IDX_TAIL "mundur".
        Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen pq
        menjadi rata kiri untuk membuat ruang kosong bagi QUEUE_TAIL baru  */

void dequeue(PrioQueue * pq, ElTypeQueue *val);
/* Proses: Menghapus val pada q dengan aturan FIFO */
/* I.S. pq tidak mungkin kosong */
/* F.S. val = nilai elemen QUEUE_HEAD pd
I.S., QUEUE_HEAD dan QUEUE_IDX_HEAD "mundur"; 
        pq mungkin kosong */

void displayQueue(PrioQueue q);

#endif