/**
 * Author:    Danijel Jovanovic (@owlCoder)
 * Created:   30.10.2020
 *
 * (c) PJISP K1 2020/10
 **/

#include <stdio.h>

int main(void)
{
    int n = 0, m = 0, i = 0, j = 0, brojDel = 1;

    //verify input
    do {
        printf("\nUnesi prirodni broj m\n>> ");
        scanf("%d", &m);
    } while(m < 1);

    do {
        printf("\nUnesi prirodni broj n (m > n)\n>> ");
        scanf("%d", &n);

        if(n > m)
            printf("\nBroj n mora biti manji od broja m!\n");

    } while(n < 1 || n >= m);

    printf("\nProsti brojevi su\n>> "); // samo novi red radi preglednosti

    // calculate sigma n
    for(i = n + 1; i < m; i++)
    {
        for(j = 2; j <= i; j++)
            if(i % j == 0)
                brojDel++;

        if(brojDel <= 2)
            printf("%d  ", i);

        brojDel = 1;
    }

    puts("");
    return 0;
}
