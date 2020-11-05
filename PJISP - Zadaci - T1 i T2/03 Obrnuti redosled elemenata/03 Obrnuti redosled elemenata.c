/*
Dat je celobrojni niz od maksimalno 30 elemenata.
Obrnuti redosled elemenata u nizu (bez upotrebe pomocnog niza)
i zatim odstampati rezultat.
*/

#include <stdio.h>

#define MAX_NIZ 30

int main(void)
{
    int i = 0, niz[MAX_NIZ], tmp = 0, n = 0;

    do {
        printf("\nKoliko elemenata zelite da ima vas niz?\n>> ");
        scanf("%d", &n);

        if(n < 1)
            printf("\nNiz ne moze da ima %d elemenata!\n\n", n);
    } while(n < 1);

    printf("\nUnos niza\n");
    for(i = 0; i < n; i++)
    {
        printf("\tniz[%d] = ", i);
        scanf("%d", niz + i);
    }

    printf("\n\nObrnuti niz izgleda\n>> ");
    for(i = 0; i < n / 2; i++)
    {
        tmp = niz[n - 1 - i];
        niz[n - 1 - i] = niz[i];
        niz[i] = tmp;
    }
    for(i = 0; i < n; i++)
        printf("\n\tniz[%d] = %d", i, niz[i]);
}
