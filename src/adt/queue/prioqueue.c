#include <stdio.h>
#include "prioqueue.h"

/* *** Kreator *** */
void CreatePrioQueue(PrioQueue *pq) {
/* I.S. sembarang */
/* F.S. Sebuah pq kosong terbentuk dengan kondisi sbb: */
/* - Index head bernilai IDX_UNDEF */
/* - Index tail bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah pq kosong */
    QUEUE_IDX_HEAD(*pq) = QUEUE_IDX_TAIL(*pq) = IDX_UNDEF;
}

boolean isEmptyQueue(PrioQueue pq) {
/* Mengirim true jika pq kosong: lihat definisi di atas */
    return (QUEUE_IDX_HEAD(pq) == IDX_UNDEF && QUEUE_IDX_TAIL(pq) == IDX_UNDEF);
}

boolean isFullQueue(PrioQueue pq) {
/* Mengirim true jika tabel penampung elemen pq sudah penuh */
/* yaitu jika index head bernilai 0 dan index tail bernilai QUEUE_CAPACITY-1 */
    return (QUEUE_IDX_HEAD(pq) == 0 && QUEUE_IDX_TAIL(pq) == QUEUE_CAPACITY - 1);
}

int lengthQueue(PrioQueue pq) {
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika pq kosong. */
    if (isEmptyQueue(pq)) {
        return 0;
    } else {
        return (QUEUE_IDX_TAIL(pq) - QUEUE_IDX_HEAD(pq) + 1);
    }
}

/*** Primitif Add/Delete ***/
void enqueue(PrioQueue *pq, ElTypeQueue val) {
/* Proses: Menambahkan val pada pq dengan aturan FIFO */
/* I.S. pq mungkin kosong, tabel penampung elemen pq TIDAK penuh */
/* F.S. val menjadi QUEUE_TAIL yang baru, QUEUE_IDX_TAIL "mundur".
        Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen pq
        menjadi rata kiri untuk membuat ruang kosong bagi QUEUE_TAIL baru  */
    int i, j;
    ElTypeQueue t;
    boolean found;
    if (isEmptyQueue(*pq)) { // Add casually if empty
        QUEUE_IDX_HEAD(*pq) = QUEUE_IDX_TAIL(*pq) = 0;
        QUEUE_TAIL(*pq) = val;
    } else { // Do insertion sort based on score and time
        // Move everything to the left
        if (QUEUE_IDX_TAIL(*pq) == QUEUE_CAPACITY - 1) {
            for (i = QUEUE_IDX_HEAD(*pq); i <= QUEUE_IDX_TAIL(*pq); i++) {
                (*pq).buffer[i-QUEUE_IDX_HEAD(*pq)] = (*pq).buffer[i];
            }
            QUEUE_IDX_TAIL(*pq) -= QUEUE_IDX_HEAD(*pq);
            QUEUE_IDX_HEAD(*pq) = 0;
        }
        // Add tail to element addition
        QUEUE_IDX_TAIL(*pq)++;
        // Insertion sort, we only care about current val because
        // guaranteed element was sorted already (O(N))
        found = false;
        for (i = QUEUE_IDX_HEAD(*pq); i < QUEUE_IDX_TAIL(*pq); i++) {
            t = (*pq).buffer[i];
            if (val.timePickUp < t.timePickUp) { // If i score < current score
                for (j = QUEUE_IDX_TAIL(*pq) - 1; j >= i; j--) { // move everything to right
                    (*pq).buffer[j+1] = (*pq).buffer[j];
                }
                (*pq).buffer[i] = val; // Assign val
                found = true;
                break;
            }
        }
        if (!found) { // If not found, set Tail to val
            QUEUE_TAIL(*pq) = val;
        }
    }
}

void dequeue(PrioQueue * pq, ElTypeQueue *val) {
/* Proses: Menghapus val pada q dengan aturan FIFO */
/* I.S. pq tidak mungkin kosong */
/* F.S. val = nilai elemen QUEUE_HEAD pd
I.S., QUEUE_HEAD dan QUEUE_IDX_HEAD "mundur"; 
        pq mungkin kosong */
    *val = QUEUE_HEAD(*pq);
    if (QUEUE_IDX_HEAD(*pq) == QUEUE_IDX_TAIL(*pq)) {
        QUEUE_IDX_HEAD(*pq) = QUEUE_IDX_TAIL(*pq) = IDX_UNDEF; // Set empty
    } else {
        QUEUE_IDX_HEAD(*pq)++; // Move head
    }
}

void displayQueue(PrioQueue q) {
    if (!isEmptyQueue(q)) {
        int i;
        for (i = QUEUE_IDX_HEAD(q); i <= QUEUE_IDX_TAIL(q); i++) {
            printf("%d %c %c %c\n",
                q.buffer[i].timePickUp,
                q.buffer[i].pickUp->letter,
                q.buffer[i].dropOff->letter,
                q.buffer[i].type
            );
        }
    }
}