#include <stdio.h>
#include "matrix.h"

int main(){
    Matrix m1, m2, m3;
    int row1, col1, row2, col2;

    printf("Masukkan dimensi matrix 1:\n");
    scanf("%d", &row1);
    scanf("%d", &col1);
    printf("masukkan elemen matiks 1:\n");
    readMatrix(&m1, row1, col1);
    printf("MATRIX 1:\n");
    displayMatrix(m1);
    printf("\n");

    printf("Masukkan dimensi matrix 2:\n");
    scanf("%d", &row2);
    scanf("%d", &col2);
    printf("masukkan elemen matiks 2:\n");
    readMatrix(&m2, row1, col2);
    printf("MATRIX 2:\n");
    displayMatrix(m2);
    printf("\n");


    boolean ongoing = true;
    int option;
    while (ongoing){
        printf("pilih operasi matrix:\n1. Penjumlahan m1 dan m2\n2. Pengurangan m1 dengan m2\n3. Perkalian m1 dengan m2\n4. perkalian m1 dengan konstanta\n5. cek apakah sama m1 sama dengan m2\n6. cek apakah dimensi m1 sama dengan dimensi m2\n7. Mencari banyaknya elemen dalam m1\n8. mencek apakah m1 adalah matrix persegi\n9. mencek apakah m1 adalah matriks simetri\n10. mencek apakah m1 adalah matirks identitas\n11. mencek apakah m1 adalah matriks sparse\n12. mencari determinan m1\n12. mencari transpose m1\n13. mencari mean dari row dari m1\n14. mencari mean dari col dari m1\n15. mencari nilai ekstrim pada  row dari m1\n16. mencari nilai ekstrim pada col dari m1\n17. mencari banyaknya kemunculan elemen dalam row m1\n18. mencari banyaknya kemunculan elemen dalam col m1\n19. mengubah nilai m1\n20. mengubah nilai dari m2\n21. EXIT\n");
        printf(">>>>>");
        scanf("%d", &option);
        printf("\n");

        if (option == 1){
            if (isSizeEqual(m1, m2)){
                m3 = addMatrix(m1, m2);
                displayMatrix(m3);
                printf("\n");
            }
            else{
                printf("dimensi m1 dan m2 tidak sama\n");
            }
        }
        else if (option == 2) {
            if (isSizeEqual(m1, m2)){
                m3 = subtractMatrix(m1, m2);
                displayMatrix(m3);
                printf("\n");
            }
            else{
                printf("dimensi m1 dan m2 tidak sama\n");
            }
        }
        else if (option == 3){
            if (COLS(m1) == ROWS(m2)){
                m3 = multiplyMatrix(m1, m2);
                displayMatrix(m3);
                printf("\n");
            }
            else{
                printf("tidak bisa melakukan perkalian matirx\n");
            }
        }
        else if (option==4){
            int val;
            printf("masukkan konstanta pengali: ");
            scanf("%d", &val);
            printf("\n");
            m3 = multiplyConst(m1, val);
            printf("\n");

        }
        else if (option==5){
            if (isEqual(m1, m2)){
                printf("sama\n");
            }
            else{
                printf("beda\n");
            }
        }
        else if (option==6){
            if (isSizeEqual(m1, m2)){
                printf("sama\n");
            }
            else{
                printf("beda\n");
            }
        }
        else if (option == 7){
            printf("%d", count(m1));
            printf("\n");
        }
        else if (option==8){
            if (isSquare(m1)){
                printf("persegi\n");
            }
            else{
                printf("bukan\n");
            }
        }
        else if (option==9){
            if (isSymmetric(m1)){
                printf("simetris\n");
            }
            else{
                printf("tidak simetris\n");
            }
        }
        else if (option==21){
            ongoing = false;
        }

        
    }

}