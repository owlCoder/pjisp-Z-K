/*
Unosom sa tastature je zadat niz A, neoznacenih celih brojeva od
maksimalno 30 elemenata. Transformisati niz (bez pomocnog)
tako da se svaki element niza pojavi samo jednom.
Na izlazu stampati broj elemenata zadatog niza, elemente
zadatog niza, broj elemenata transformisanog niza i elemente niza.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 30

void pomerajUdesno(unsigned niz[], unsigned y) {
    unsigned i = y;
    for(; i < MAX_SIZE; i++)
        niz[i] = niz[i+1];

    return;
}

int main(void)
{
    unsigned niz[MAX_SIZE], i = 0, n;

    do {
        printf_s("Broj elemenata niza\n>> ");
        scanf("%u", &n);
    } while(n < 1 || n > MAX_SIZE);

    printf_s("\nUnos elemenata niza\n>> ");
    while(i < n) {
        scanf("%u", niz + i);
        i++;
    }

    // ispis
    printf("\n\n-------------------- PRE OBRADE -------------------------\n");
    printf("\nBroj elemenata niza\n>> %u\n\nElementi niza\n>> ", n);
    for(i = 0; i < n; i++)
        printf("%u ", niz[i]);

    // brisanje duplikata iz niza
    unsigned x = 0, y = 1;
    do {
        if(niz[x] == niz[y]) {
            pomerajUdesno(niz, y);
            x++; n--;
        }
        else
            y++;
    } while(y < n);

    // ispis posle obrade
    printf("\n\n------------------- POSLE OBRADE ------------------------\n");
    printf("\nBroj elemenata niza\n>> %u\n\nElementi niza\n>> ", n);
    for(i = 0; i < n; i++)
        printf("%u ", niz[i]);

    printf("\n\n");

    return 0;
}
