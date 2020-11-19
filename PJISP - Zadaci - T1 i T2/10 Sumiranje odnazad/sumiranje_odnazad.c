#include <stdio.h>
#include <math.h>

#define MAX_ARRAY_SIZE 10

int main()
{
    int A[MAX_ARRAY_SIZE], i, count = 0, n, suma = 0;
    unsigned x;

    do {
        printf("\nUnesite velicinu niza [2 >= n <= %d]\n>> ", MAX_ARRAY_SIZE);
        scanf("%d", &n);
    } while(n < 2 || n > MAX_ARRAY_SIZE);

    do {
        printf("\nUnesite jecnu celobrojnu vrednost [x >= %d]\n>> ", 1);
        scanf("%d", &x);
    } while(x < 1);

    printf("\n*************** UNOS ELEMENATA NIZA ***************\n");
    for(i = 0; i < n; i++) {
        printf("\tA[%d] = ", i);
        scanf("%d", A + i);
    }
    for(i = 0; i < n; i++)
        printf("\n\tA[%d] = % d", i, A[i]);

    puts("");

    for(i = n - 1; i >= 0; i--) {
        if(suma <= x) { 
            suma += A[i];
            count++;
            printf("\n\tsum(A[%d]) == % d", i, suma);
        }
        else
            break;
    }

    printf("\n\n\tcount = %d\n\n", count);

    return 0;
}
