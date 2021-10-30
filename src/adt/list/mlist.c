#include <stdio.h>
#include "listpos.h"

int median(ListPos l){
    //prekondisi: list sudah terurut
    int N = length(l);
    if (N % 2 == 1)
    {
        return(ELMT(l,(((N/2) + 1) - 1))); //Dikurang 1 karena ini index
    }
    else if (N % 2 == 0)
    {
        return(ELMT(l,((N/2) - 1)));
    }
    
}

int main()
{
    ListPos l;
    int X, idx, max, min, med;
    boolean asc;
    readList(&l);
    displayList(l);
    printf("\n");
    scanf("%d", &X);
    idx = indexOf(l, X);
    if (idx == IDX_UNDEF)
    {
        printf("%d tidak ada\n", X);
    }
    else{
        printf("%d\n", idx);
        extremes(l, &max, &min);
        asc = true;
        sort(&l, asc);
        med = median(l);
        if (X == max)
        {
            printf("maksimum\n");
        }
        if (X == min)
        {
            printf("minimum\n");
        }
        if (X == med)
        {
            printf("median\n");
        }
    }
    return 0;
}
