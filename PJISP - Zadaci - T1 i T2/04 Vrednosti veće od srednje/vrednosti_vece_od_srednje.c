/*
Unosom sa tastature je zadat niz X od maksimalno 30 celobrojnih elemenata. 
Naci broj elemenata niza cija je vrednost veca od srednje vrednosti niza. 
Na izlazu štampati niz X, srednju vrednost niza (SRVX) i broj elemenata niza cija 
je vrednost veca od srednje vrednosti niza.
*/

#include <stdio.h>

#define MAX_ARRAY_SIZE 30

int main()
{
    int X[MAX_ARRAY_SIZE], i, n, brElemKaoSrvx = 0;
    double SRVX = 0.0;

    do {
        printf("\nUnesite velicinu niza [0 > n <= %d]\n>> ", MAX_ARRAY_SIZE);
        scanf("%d", &n);
    } while(n < 1 || n > MAX_ARRAY_SIZE);

    printf("\n*************** UNOS ELEMENATA NIZA ***************\n");
    for(i = 0; i < n; i++) {
        printf("\tX[%d] = ", i);
        scanf("%d", X + i);

        SRVX += *(X + i);
    }

    SRVX /= (n * 1.0);

    for(i = 0; i < n; i++)
        if(*(X + i) > SRVX)
            brElemKaoSrvx++;

    printf("\nNiz X");
    for(i = 0; i < n; i++)
        printf("\n\tX[%d] = %d", *(X + i));
    
    printf("\n\n\tSRVX = %.2lf\n\tBroj elemenata kao SRVX je: %d\n\n", SRVX, brElemKaoSrvx);

    return 0;
}
