/*
Dat je niz A od maksimalno 15 celobrojnih elemenata. 
Učitati n elemenata a zatim naći 2 elementa čiji je zbir najveći. 
Sprovesti zaštitu unosa nad podatkom n. Ako se vrši sortiranje, svejedno je koji će se algoritam koristiti.

Za sledeće ulazne podatke:
n = 5
A = {4, 2, 6, -7, 1}

očekivani izlaz je u sledećem formatu:
A[0] = 4
A[1] = 2
A[2] = 6
A[3] = -7
A[4] = 1

max = 6 + 4 = 10
*/

#include <stdio.h>
#include <math.h>

#define MAX_ARRAY_SIZE 15

int main()
{
    int A[MAX_ARRAY_SIZE], i, n;
    int x, y, z = 0;

    do {
        printf("\nUnesite velicinu niza [2 >= n <= %d]\n>> ", MAX_ARRAY_SIZE);
        scanf("%d", &n);
    } while(n < 2 || n > MAX_ARRAY_SIZE);

    printf("\n*************** UNOS ELEMENATA NIZA ***************\n");
    for(i = 0; i < n; i++) {
        printf("\tA[%d] = ", i);
        scanf("%d", A + i);
    }
    for(i = 0; i < n; i++)
        printf("\n\tA[%d] = %d", i, A[i]);
    for(i = 0; i < n; i++)
        for(x = 0; x < n; x++)
        {
            if(A[i] > A[x]) 
            {
                y = A[x];
                A[x] = A[i];
                A[i] = y;
            }
        }

    printf("\n\n\tMAX = %d + %d = %d\n\n", A[0], A[1], A[0] + A[1]);

    return 0;
}
