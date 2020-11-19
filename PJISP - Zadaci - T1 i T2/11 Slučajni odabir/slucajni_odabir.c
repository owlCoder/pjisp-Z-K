#include <stdio.h>

#define MAX_ARRAY_SIZE 10

void found(const int *A, const int n, int *count, const int x)
{
    int i;
    for(i = 0; i < n; i++)
        if(A[i] == x) {  
            printf("\n\tfound(A[%d]) == % d", i, A[i]);
            (*count)++;
        }
}

int main(void)
{
    int A[MAX_ARRAY_SIZE], i, count = 0, n, suma = 0, x;

    do {
        printf("\nUnesite velicinu niza [2 >= n <= %d]\n>> ", MAX_ARRAY_SIZE);
        scanf("%d", &n);
    } while(n < 2 || n > MAX_ARRAY_SIZE);

    printf("\nUnesite trazenu celobrojnu vrednost\n>> ", 1);
    scanf("%d", &x);

    printf("\n*************** UNOS ELEMENATA NIZA ***************\n");
    for(i = 0; i < n; i++) {
        printf("\tA[%d] = ", i);
        scanf("%d", A + i);
    }
    for(i = 0; i < n; i++)
        printf("\n\tA[%d] = % d", i, A[i]);

    puts("");

    found(A, n, &count, x);

    printf("\n\n\tchance = %.3lf\n\n", count / (n * 1.0));

    return 0;
}
