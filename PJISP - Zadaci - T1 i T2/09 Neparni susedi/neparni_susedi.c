#include <stdio.h>
#include <math.h>

#define MAX_ARRAY_SIZE 10

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
