#include <stdio.h>
#include "list.h"

int main(int argc, char const *argv[])
{
    List l;
    int val, menu, idx, len;
    char masukkan;
    CreateList(&l);
    printf("Apakah anda ingin memproses list? (y/n): ");
    scanf("%c", &masukkan);
    while (masukkan != 'n')
    {
        printf("Menu:\n");
        printf("1. Insert List\n");
        printf("2. Delete List\n");
        printf("3. Index of List\n");
        printf("4. Length List\n");
        printf("5. Mengecek Empty List\n");
        printf("6. Mengecek Full List\n");
        scanf("%d", &menu);
        if (menu == 1)
        {
            if (isFullList(l))
            {
                printf("List penuh sehingga tidak bisa dimasukkan elemen baru\n");
            }
            else{
                printf("Silakan input val untuk dimasukkan ke List\n");
                scanf("%d", &val);
                insertList(&l, val);
            }
        }
        else if (menu == 2)
        {
            if (isEmptyList(l))
            {
                printf("List kosong sehingga tidak ada elemen yang dapat dihapus\n");
            }
            else{
                printf("Silakan masukkan index untuk dihapus di List\n");
                scanf("%d", &idx);
                deleteAtList(&l, idx);      
            }  
        }
        else if (menu == 3)
        {
            printf("Silakan masukkan val yang akan dicari index terkecilnya di List (jika val merupakan elemen List)\n");
            scanf("%d", &val);
            idx = indexOfList(l, val);
            if (idx != IDX_UNDEF)
            {
                printf("%d terdapat pada indeks ke-%d\n", val, idx);
            }
            else{
                printf("%d tidak terdapat di dalam list\n", val);
            }
        }
        else if (menu == 4)
        {
            len = lengthList(l);
            printf("Length list = %d\n", len);
        }
        else if (menu == 5)
        {
            if (isEmptyList(l))
            {
                printf("List kosong\n");
            }
            else{
                printf("List tidak kosong\n");
            }
        }
        else if (menu == 6)
        {
            if (isFullList(l))
            {
                printf("List penuh\n");
            }
            else{
                printf("List tidak penuh\n");
            }            
        }
        else{
            printf("Masukkan menu salah\n");
        }
        printf("Apakah anda masih ingin memproses list? (y/n): ");
        scanf(" %c", &masukkan);
    }
    return 0;
}
