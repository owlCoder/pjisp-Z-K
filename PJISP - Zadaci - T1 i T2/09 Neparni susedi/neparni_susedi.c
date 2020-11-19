#include <stdio.h>

#define MAX_ARRAY_SIZE 10

unsigned is_neparni_sused(int *, int, int);

int main()
{
    int A[MAX_ARRAY_SIZE], i, j, count = 0, n;
    unsigned jes = 0;

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

    for(i = 0; i < n - 1; i++){
        if( jes = is_neparni_sused(A, i, i + 1)) { 
            printf("\n\todd(A[%d]) == odd(A[%d]) == %d", i, i + 1, jes);
             count++;
        }
    }

    printf("\n\n\tcount = %d\n\n", count);

    return 0;
}

unsigned is_neparni_sused(int *A, int i, int j)
{
    unsigned nep1 = A[i] % 2 != 0 ? 1 : 0;
    unsigned nep2 = A[j] % 2 != 0 ? 1 : 0;
    
    if(nep1 == 1 && nep2 == 1)
        return 1;
    else 
        return 0;
}
