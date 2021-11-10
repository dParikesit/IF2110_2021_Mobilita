#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void CreateMatrix(int nRow, int nCol, Matrix *m)
/* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
/* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks m sesuai dengan definisi di atas terbentuk */
{
    ROWS(*m) = nRow;
    COLS(*m) = nCol;
}
/* *** Selektor "DUNIA Matrix" *** */
boolean isIdxValid(int i, int j)
/* Mengirimkan true jika i, j adalah Index yang valid untuk matriks apa pun */
{
   return ((i>=0 && i<ROW_CAP) && (j>=0 && j<COL_CAP));
}
/* *** Selektor: Untuk sebuah matriks m yang terdefinisi: *** */
Index getLastIdxRow(Matrix m)
/* Mengirimkan Index baris terbesar m */
{
    return (ROWS(m)-1);
}
Index getLastIdxCol(Matrix m)
/* Mengirimkan Index kolom terbesar m */
{
    return (COLS(m)-1);
}
boolean isIdxEff(Matrix m, Index i, Index j)
/* Mengirimkan true jika i, j adalah Index efektif bagi m */
{
    return (i>=0 && i<ROWS(m) && j>=0 && j<COLS(m));
}
int getElmtDiagonal(Matrix m, Index i)
/* Mengirimkan elemen m(i,i) */
{
    return  ELMT(m, i, i);
}
/* ********** Assignment  Matrix ********** */
void copyMatrix(Matrix mIn, Matrix *mRes)
/* Melakukan assignment MRes = MIn */
{
    Index i,j;

    COLS(*mRes) = COLS(mIn);
    ROWS(*mRes) = ROWS(mIn);

    for(i=0 ; i<ROWS(mIn) ; i++){
        for(j=0 ; j<COLS(mIn) ; j++){
            ELMT(*mRes,i,j) = ELMT(mIn,i,j);
        }
    }
}
/* ********** KELOMPOK BACA/TULIS ********** */
void readMatrix(Matrix *m, int nRow, int nCol)
/* I.S. isIdxValid(nRow,nCol) */
/* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
/* Proses: Melakukan CreateMatrix(m,nRow,nCol) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika nRow = 3 dan nCol = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10 
*/
{
    Index i,j;
    
    ROWS(*m) = nRow;
    COLS(*m) = nCol;
	for (i = 0; i < nRow; i++){
		for (j = 0; j < nCol; j++){
			if (j==0) {
                scanf("%d", &ELMT(*m,i,j));
            }
            else {
                scanf(" %d", &ELMT(*m,i,j));
            }
		}
	}
}
void displayMatrix(Matrix m)
/* I.S. m terdefinisi */
/* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */
/* Contoh: Menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
{
    Index i,j;
    for (i=0 ; i<ROWS(m); i++){
        for (j=0 ; j<COLS(m); j++){
            printf("%c", ELMT(m,i,j));
            
        }
        if(i!= getLastIdxRow(m)) printf("\n"); 
    }
}
/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */
Matrix addMatrix(Matrix m1, Matrix m2)
/* Prekondisi : m1 berukuran sama dengan m2 */
/* Mengirim hasil penjumlahan matriks: m1 + m2 */
{
    Matrix m3;
    CreateMatrix(ROWS(m1), COLS(m1), &m3);

    for (int i = 0; i<ROWS(m3); i++){
        for (int j = 0; j<COLS(m3); j++){
            ELMT(m3, i, j) = ELMT(m1, i, j) + ELMT(m2, i, j);
        }
    }
    return m3;
}

Matrix subtractMatrix(Matrix m1, Matrix m2)
/* Prekondisi : m1 berukuran sama dengan m2 */
/* Mengirim hasil pengurangan matriks: salinan m1 – m2 */
{
    Matrix m3;
    CreateMatrix(ROWS(m1), COLS(m1), &m3);
    for (int i = 0; i<ROWS(m3); i++){
        for (int j = 0; j<COLS(m3); j++){
            ELMT(m3, i, j) = ELMT(m1, i, j) - ELMT(m2, i, j);
        }
    }
    return m3;
}
Matrix multiplyMatrix(Matrix m1, Matrix m2)
/* Prekondisi : Ukuran kolom efektif m1 = ukuran baris efektif m2 */
{
    Matrix m3;
    CreateMatrix(ROWS(m1), COLS(m2), &m3);

    for (int i = 0; i<=getLastIdxRow(m1); i++){
        for (int j = 0; j<=getLastIdxCol(m2); j++){
            for (int k = 0; k<=getLastIdxCol(m1); k++){
                ELMT(m3, i, j) += ELMT(m1, i, k) *  ELMT(m2, k, j);
            }
        }
    }
    return m3;
}
Matrix multiplyConst(Matrix m, int x)
/* Mengirim hasil perkalian setiap elemen m dengan x */
{
    Matrix result;
    CreateMatrix(ROWS(m),COLS(m), &result);
    Index i,j;

    for (i=0 ; i<ROWS(m); i++){
        for (j=0 ; j<COLS(m); j++){
            ELMT(result,i,j) = x * ELMT(m,i,j);
        }
    }   
    return result;
}
void pMultiplyConst(Matrix *m, int k)
/* I.S. m terdefinisi, k terdefinisi */
/* F.S. Mengalikan setiap elemen m dengan k */
{
    Index i,j;
    for (i=0 ; i<ROWS(*m); i++){
        for (j=0 ; j<COLS(*m); j++){
            ELMT(*m,i,j) = k * ELMT(*m,i,j);
        }
    }   
}
/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP Matrix ********** */
boolean isEqual(Matrix m1, Matrix m2)
/* Mengirimkan true jika m1 = m2, yaitu count(m1) = count(m2) dan */
/* untuk setiap i,j yang merupakan Index baris dan kolom m1(i,j) = m2(i,j) */
/* Juga merupakan strong eq karena getLastIdxCol(m1) = getLastIdxCol(m2) */
{
    boolean result = (count(m1) == count(m2));
    if (result){
        int i,j;
        for (i = 0; i <= getLastIdxRow(m1); i++){
            for (j = 0; j <= getLastIdxCol(m1); j++){
                result = result && (ELMT(m1, i, j) == ELMT(m2, i ,j));
            }
        }
    }
    return result;
}
boolean isNotEqual(Matrix m1, Matrix m2)
/* Mengirimkan true jika m1 tidak sama dengan m2 */
{
    return !isEqual(m1, m2);
}
boolean isSizeEqual(Matrix m1, Matrix m2)
/* Mengirimkan true jika ukuran efektif matriks m1 sama dengan ukuran efektif m2 */
{
    return ((ROWS(m1) == ROWS(m2)) && (COLS(m1)==COLS(m2)));
}
/* ********** Operasi lain ********** */
int count(Matrix m)
/* Mengirimkan banyaknya elemen m */
{
    return (ROWS(m) * COLS(m));
}
/* ********** KELOMPOK TEST TERHADAP Matrix ********** */
boolean isSquare(Matrix m)
/* Mengirimkan true jika m adalah matriks dg ukuran baris dan kolom sama */
{
    return (ROWS(m)==COLS(m));
}
boolean isSymmetric(Matrix m)
/* Mengirimkan true jika m adalah matriks simetri : isSquare(m) dan untuk setiap elemen m, m(i,j)=m(j,i) */
{
    if (!isSquare){
        return false;
    }
    else {
        int i =0, j = 0;
        boolean same = true;
        while (same  && i<ROWS(m)){
            while (same && j<COLS(m)){
                if (ELMT(m, i, j) != ELMT(m, i, j)){
                    same = false;
                }
                else {
                    j++;
                }
            }
            i++;
        }
        return same;
    }
}
boolean isIdentity(Matrix m)
/* Mengirimkan true jika m adalah matriks satuan: isSquare(m) dan 
   setiap elemen diagonal m bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
{
    if (!isSquare(m)){
        return false;
    }
    else{
        int i =0, j = 0;
        boolean same = true;
        while (same  && i<ROWS(m)){
            while (same && j<COLS(m)){
                if (i==j){
                    if (ELMT(m, i, j) != 1){
                        same = false;
                    }
                }
                else{
                    if (ELMT(m, i, j)!=0){
                        same = false;
                    }
                }
                j++;
            }
            i++;
        }
        return same;
    }
}
boolean isSparse(Matrix m)
/* Mengirimkan true jika m adalah matriks sparse: matriks “jarang” dengan definisi: 
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */
{
    Index i,j;
    int countEff = 0;
    for (i=0 ; i<ROWS(m); i++){
        for (j=0 ; j<COLS(m); j++){
            if (ELMT(m,i,j) != 0) countEff++;
        }
    }
    return (countEff<= count(m)*0.05);
}
Matrix inverse1(Matrix m)
/* Menghasilkan salinan m dengan setiap elemen "di-invers", yaitu dinegasikan (dikalikan -1) */
{
    return (multiplyConst(m, -1));
}
void pInverse1(Matrix *m)
/* I.S. m terdefinisi */
/* F.S. m di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
{
    pMultiplyConst(m,-1);
}
float determinant(Matrix m)
/* Prekondisi: isSquare(m) */
/* Menghitung nilai determinan m */
{
   Index i,j,k,x,y;

    Matrix temp;
    CreateMatrix(ROWS(m)-1, COLS(m)-1, &temp);


    if (count(m) == 4 ){
        return (ELMT(m,0,0)*ELMT(m,1,1)- ELMT(m,0,1)*ELMT(m,1,0));
    }
    else{
        float result=0;
        for(i=0; i<ROWS(m); i++){
            
            x=0;
            for (j=1; j<COLS(m);j++){
                y=0;
                for (k=0; k<ROWS(m); k++){
                    
                        if (k!=i)   {
                        ELMT(temp,x,y) = ELMT(m,j,k);
                        y++;
                                }    
                   }
                x++; 
                    }
            if (i%2==1)result -= ELMT(m,0,i)*determinant(temp);
            else result += ELMT(m,0,i)*determinant(temp);
            
            
        }
        return result;
        } 
}
void transpose(Matrix *m)
/* I.S. m terdefinisi dan isSquare(m) */
/* F.S. m "di-transpose", yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
{
   int i, j, temp;
   for (i=0 ; i<ROWS(*m); i++){
        for (j=0; j<=i; j++){
            temp = ELMT(*m,i,j);
            ELMT(*m,i,j) = ELMT(*m,j,i);
            ELMT(*m,j,i) = temp;
        }
    } 
}
float rowMean (Matrix m, Index i)
{
    int j, n, count;
    count = 0;
    n = 0;
    for (j=0; j<=getLastIdxCol(m); j++){
        count += ELMT(m, i, j);
        n++;
    }
    return count/(n*1.0f);
}
float colMean (Matrix m, Index j){
    int i, count, n;
    n = 0;
    count = 0;
    for (i=0; i<=getLastIdxRow(m); i++){
        count += ELMT(m, i, j);
        n++;
    }
    return count/(n*1.0f);
}
void rowExtremes (Matrix m, Index i, int *max, int *min){
    *max = ELMT(m, i, 0);
    *min = ELMT(m, i, 0);
    for (int j=0; j<=getLastIdxCol(m); j++){
        if (ELMT(m, i, j)>*max){
            *max = ELMT(m, i, j);
        }
        if (ELMT(m, i, j)<*min){
            *min = ELMT(m, i, j);
        }
    }
}
void colExtremes (Matrix m, Index j, int *max, int *min){
    *max = ELMT(m, 0, j);
    *min = ELMT(m, 0, j);
    for (int i=0; i<=getLastIdxRow(m); i++){
        if (ELMT(m, i, j)>*max){
            *max = ELMT(m, i, j);
        }
        if (ELMT(m, i, j)<*min){
            *min = ELMT(m, i, j);
        }
    }
}
int countValOnRow (Matrix m, Index i, int val){
    int count = 0;
    for (int j=0; j<=getLastIdxCol(m); j++){
        if (ELMT(m, i, j)==val){
            count++;
        }
    }
    return count;
}
int countValOnCol (Matrix m, Index j, int val){
    int count = 0;
    for (int i=0; i<=getLastIdxCol(m); i++){
        if (ELMT(m, i, j)==val){
            count++;
        }
    }
    return count;
}