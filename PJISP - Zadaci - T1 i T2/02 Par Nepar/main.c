/*
Unosom sa tastature je zadat niz X od
maksimalno 50 celobrojnih elemenata.
Ucitati n elemenata u niz X i formirati nizove A i B,
 pri cemu su elementi niza A parni elementi niza X,
 a elementi niza B su elementi niza X sa neparnim indeksom (1,3,5,…).
Izracunati SRVA srednju vrednost niza A.
 Na izlazu stampati elemente nizova A, B i SRVA
 srednju vrednost niza A.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

int main()
{
     int X[MAX_SIZE], i = 0, n;
     int A[MAX_SIZE] = {0}, B[MAX_SIZE] = {0};
     int i1 = 0, i2 = 0;
     float suma = 0.0;

    do {
        printf("Broj elemenata niza\n>> ");
        scanf("%d", &n);
    } while(n < 1 || n > MAX_SIZE);

    printf("\nUnos elemenata niza\n>> ");
    while(i < n) {
        scanf("%d", X + i);
        i++;
    }

    i = 0;
    do {
        if(X[i] % 2 == 0) {
            A[i1] = X[i]; // parni elementi
            i1++;
        }

        if(i % 2 == 1) {
            B[i2] = X[i]; // neparni indeksi
            i2++;
        }
        i++; // sledeci element
     } while(i < n);

    printf("\n\nElementi niza A\n>> ");
    for(i = 0; i < i1; i++) {
        printf("%d ", A[i]);
        suma += A[i];
    }

    printf("\n\nElementi niza B\n>> ");
    for(i = 0; i < i2; i++)
        printf("%d ", B[i]);

    printf("\n\nSRVA = %.2f\n\n", suma / i1);

    return 0;
}
