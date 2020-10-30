/**
 * Author:    Danijel Jovanovic (@owlCoder)
 * Created:   30.10.2020
 *
 * (c) PJISP K1 2020/10
 **/

 /// Postavka
 /// Ucitati broj clanova reda (n) a zatim odrediti pribliznu vrednost e
 /// primenom sledece matematicke formule:
 /// http://pjisp.petarmaric.com/zbirka-zadataka/zadaci/sa-kolokvijuma/2018/PSI/T12/S4/index.html

#include <stdio.h>
#include <math.h>

long long int fact(int n)
{
    int i;
    int long long faktorijel = 1;

    if (n < 0)
        return -1;
    else
        for (i = 1; i <= n; ++i)
            faktorijel *= i;

    return faktorijel;
}

int main(void)
{
    int n = 0, i = 0;
    double clan = 0., sum = 0.;

    //verify input
    do {
       printf("\nUneti broj n\n>> ");
       scanf("%d", &n);
    } while(n < 1);

    puts(""); // samo novi red radi preglednosti

    // calculate e
    for(i = 0; i < n; i++)
    {
       clan = ( pow(-1.0, i) / fact(i) );
       printf("clan[i=%d] = % lf\n", i, clan);
       sum += clan;
    }

    printf("\n\nsum = %lf\n", sum);
    printf("  e = %lf\n", 1 / sum);

    return 0;
}
