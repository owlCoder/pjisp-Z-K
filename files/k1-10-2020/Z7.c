/**
 * Author:    Danijel Jovanovic (@owlCoder)
 * Created:   30.10.2020
 *
 * (c) PJISP K1 2020/10
 **/

#include <stdio.h>
#include <math.h>

int unesiPrirodniBroj(char string[])
{
    int x;
    do {
        printf("\nUnesi prirodni broj %s\n>> ", string);
        scanf("%d", &x);
    } while(x < 1);

    return x;
}

void unesiNiz(int n, double niz[], char naziv[])
{
    int i;

    printf("\nUnos niza %s\n", naziv);
    for(i = 0; i < n; i++)
    {
        printf("\t%s[%d] = ", naziv, i);
        scanf("%lf", niz + i);
    }
}

int main(void)
{
    int n = unesiPrirodniBroj("n");
    int i, suma = 0;
    double A[n], B[n], C[n];

    unesiNiz(n, A, "A");
    unesiNiz(n, B, "B");

    for(i = 0; i < n; i++)
        C[i] = fabs((A[i] - B[i]));

    printf("\nRezultantni niz C\n");
    for(i = 0; i < n; i++)
        printf("\tC[%d] = %.3lf\n", i, C[i]);

    return 0;
}
