/*
Dat je niz A od maksimalno 15 dvocifrenih prirodnih brojeva. 
Učitati n elemenata a zatim proveriti da li postoje parovi elemenata za 
koje važi da je zbir kvadrata njihovih cifara jednak. 
Sprovesti zaštitu unosa nad podatkom n.

Za sledeće podatke:
n = 7
A = {42, 67, 12, 36, 76, 29, 21}

očekivani izlaz je u sledećem formatu:
A[0] = 42
A[1] = 67
A[2] = 12
A[3] = 36
A[4] = 76
A[5] = 29
A[6] = 21

zbir(A[0]) = 20
zbir(A[1]) = 85
zbir(A[2]) = 5
zbir(A[3]) = 45
zbir(A[4]) = 85
zbir(A[5]) = 85
zbir(A[6]) = 5

zbir(A[1]) == zbir(A[4]) == 85
zbir(A[1]) == zbir(A[5]) == 85
zbir(A[2]) == zbir(A[6]) == 5
zbir(A[4]) == zbir(A[5]) == 85

count = 4
*/

#include <stdio.h>
#include <math.h>

#define MAX_ARRAY_SIZE 15

int zbir(int);

int main()
{
    int A[MAX_ARRAY_SIZE], zbirC[MAX_ARRAY_SIZE], i, j, count = 0, n;

    do {
        printf("\nUnesite velicinu niza [2 >= n <= %d]\n>> ", MAX_ARRAY_SIZE);
        scanf("%d", &n);
    } while(n < 2 || n > MAX_ARRAY_SIZE);

    printf("\n*************** UNOS ELEMENATA NIZA ***************\n");
    for(i = 0; i < n; i++) {
        printf("\tA[%d] = ", i);
        scanf("%d", A + i);

        zbirC[i] = zbir(A[i]); // racunaj zbir kvadrata cifara dvocifrenog broja
    }
    for(i = 0; i < n; i++)
        printf("\n\tA[%d] = %d", i, A[i]);
    
    puts("");

    for(i = 0; i < n; i++)
        printf("\n\tzbir(A[%d]) = %d", i, zbirC[i]);
        
    puts("");

    for(i = 0; i < n - 1; i++)
        for(j = i + 1; j < n; j++) {
            if(zbirC[i] == zbirC[j]) { 
                printf("\n\tzbir(A[%d]) == zbir(A[%d]) == % d", i, j, zbirC[i]);
                count++;
            }
    }

    printf("\n\n\tcount = %d\n\n", count);

    return 0;
}

int zbir(int broj)
{
    int tmp = 0, zbirCifara = 0;
    
    tmp = broj % 10; // dobijanje poslednje cifre
    zbirCifara += tmp * tmp;

    tmp = broj / 10;
    zbirCifara += tmp * tmp;

    return zbirCifara;
}
