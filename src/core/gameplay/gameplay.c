#include "gameplay.h"
#include "../../system/gamemanager/gamemanager.h"
#include "../../system/map/map.h"


void doMoveplayer()
{
    //check apakah mobita punya pintu kemana saja
    int checkPintu = indexOfList(GSTATS.inventory, PINTU_KEMANA_SAJA);
    //jika mobita tidak punya pintu kemana saja maka check pintu akan bernilai IDX_UNDEF 
    navigateAndMoveMobita(checkPintu!=IDX_UNDEF);
    advanceTime();
    updateGame();

}
void doPickUp()
// Put getPickUpItem into the bag
{
    //jika punya vip item maka harus pickup vip item dulu
    if (toDoListHas(VIP)){
        //cari item vip di todolist
        int idxVIP = indexOfTypeLinkedList(GSTATS.toDoList, VIP);
        Item* item = getElmtListLinked(GSTATS.toDoList, idxVIP);
        //cek apakah lokasi mobita == lokasi pickup vip item
        if (MOBITAPOS != item->pickUp){
            printf("Ambil item VIP dulu!\n");
        }
        else{
            //pickup vip item dan masukkan ke bag
            push(&GSTATS.bag, item);
            insertLastListLinked(&GSTATS.inProgressList, item);
            printf("Pesanan berupa VIP Item berhasil diambil!\nTujuan Pesanan: %c\n", item->dropOff->letter);
        }
        
    }
    else{
        Item* item = getPickUpItem();
        //cek apakah posisi mobita == posisi barang
        if(item->pickUp == MOBITAPOS){
            if (item->type==NORMAL){
                push(&GSTATS.bag, item);
                insertLastListLinked(&GSTATS.inProgressList, item);
                printf("Pesanan berupa Normal Item berhasil diambil!\nTujuan Pesanan: %c\n", item->dropOff->letter);
            }
            else if (item->type==HEAVY){
                push(&GSTATS.bag, item);
                insertLastListLinked(&GSTATS.inProgressList, item);
                printf("Pesanan berupa Heavy Item berhasil diambil!\nTujuan Pesanan: %c\n", item->dropOff->letter);
            }
            else if (item->type==PERISHABLE){
                push(&GSTATS.bag, item);
                insertLastListLinked(&GSTATS.inProgressList, item);
                printf("Pesanan berupa Perishable Item berhasil diambil!\nTujuan Pesanan: %c\n", item->dropOff->letter);
            }
        }
        else{
            printf("Pesanan tidak ditemukan!\n");
        }
    }
}
void doDropOff(boolean hasVIPItem) 
// Pop bag and remove currentItem in progress list
{
    //jika didalam bag ada vip item
    if (hasVIPItem){
        if(getCurrentItem()->type == VIP){
            ElTypeStack currentItem;
            ElTypeListLinked currentItemlist;
            //delete dari bag dan inProgressList
            int idxCurrentItem = indexOfListLinked(GSTATS.inProgressList, getCurrentItem());
            pop(&GSTATS.bag, &currentItem);
            deleteAt(&GSTATS.inProgressList, idxCurrentItem, &currentItemlist);
            //tambahkan uang dan beri output ke layar
            GSTATS.money += 600;
            printf("Pesanan VIP Item berhasil diantarkan\nUang yang didapatkan: 600 Yen\nMendapatkan ability RETURN TO SENDER!\n");

        }
        else {
            printf("Tidak dapat pesanan yang dapat diantarkan!\nAntar VIP item  terlebih dahulu!\n");
        }
    }
    else{
        if (getCurrentItem()->dropOff ==  MOBITAPOS){
            ElTypeStack currentItem;
            ElTypeListLinked currentItemlist;
            int idxCurrentItem = indexOfListLinked(GSTATS.inProgressList, getCurrentItem());
            pop(&GSTATS.bag, &currentItem);
            deleteAt(&GSTATS.inProgressList, idxCurrentItem, &currentItemlist);
            if (currentItem->type == NORMAL){
                GSTATS.money += 200;
                printf("Pesanan Normal Item berhasil diantarkan\nUang yang didapatkan: 200 Yen\n");
            }
            else if (currentItem->type == HEAVY){
                GSTATS.money += 400;
                printf("Pesanan Heavy Item berhasil diantarkan\nUang yang didapatkan: 400 Yen\nMendapatkan ability SPEED BOOST!\n");
            }
            else if (currentItem->type == PERISHABLE){
                GSTATS.money += 400;
                printf("Pesanan Perishable Item berhasil diantarkan\nUang yang didapatkan: 400 Yen\nMendapatkan Increase Capacity pada bag\n");
            } 
        } else{
            printf("Tidak dapat pesanan yang dapat diantarkan!\n");
        }
    }
}

int countTimeAddition(){
    if (!isTimeRunning()){
        return 0;
    }
    else{
        int count = 1;
        //check apakah mobita sedang membawa heavy item
        if (!isEmptyListLinked(GSTATS.inProgressList)){
            //mencari heavy item di inProgressList
            Address p = GSTATS.inProgressList;
            while (p->next != NULL){
                if (p->info->type == HEAVY ){
                    count++;
                }
                p = NEXT(p);
            }
        }
        return count;  
    }
} 