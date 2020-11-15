/*
Dat je niz A od maksimalno 10 celobrojnih elemenata. Učitati n elemenata a zatim:

ispisati sadržaj celokupnog niza, od poslednjeg elementa ka početnom
odrediti i ispisati kvadratnu sredinu celokupnog niza (KS)
odrediti i ispisati aritmetičku sredinu elemenata niza koji su na neparnim indeksima (AS)

Ograničenja:
    sprovesti zaštitu unosa nad podatkom n
    sve realne promenljive trebaju biti tipa double
s   ve realne brojeve ispisivati zaokružene na 2 decimale
*/

#include <stdio.h>
#include <math.h>

#define MAX_ARRAY_SIZE 10

int main()
{
    int A[MAX_ARRAY_SIZE], i, n, brElemKaoSrvx = 0, j = 0;
    double KS = 0.0, AS = 0.0, tmp = 0.0, tmpAs = 0.0;

    do {
        printf("\nUnesite velicinu niza [0 > n <= %d]\n>> ", MAX_ARRAY_SIZE);
        scanf("%d", &n);
    } while(n < 1 || n > MAX_ARRAY_SIZE);

    printf("\n*************** UNOS ELEMENATA NIZA ***************\n");
    for(i = 0; i < n; i++) {
        printf("\tA[%d] = ", i);
        scanf("%d", A + i);

        tmp += pow(A[i], 2.0);

        if(i % 2 != 0) {
            tmpAs +=  A[i]; j++;
        }
    }

    printf("\n");
    for(i = n - 1; i >= 0; i--)
       printf("\n\tA[%d] = %d", i, *(A + i));

    KS = sqrt(1.0 / n) * sqrt(tmp);
    AS = (1.0 / j) * tmpAs;
    
    printf("\n\n\tKS = %.2lf\n\tAS %.2lf\n\n", KS, AS);

    return 0;
}
