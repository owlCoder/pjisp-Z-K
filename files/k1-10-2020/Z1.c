/**
 * Author:    Danijel Jovanovic (@owlCoder)
 * Created:   30.10.2020
 *
 * (c) PJISP K1 2020/10
 **/

#include <stdio.h>

int main(void)
{
    int n = 0, i = 0, suma = 0;

    //verify input
    do {
       printf("\nUnesi broj n\n>> ");
       scanf("%d", &n);
    } while(n < 1);

    puts(""); // samo novi red radi preglednosti

    // calculate sigma n
    for(i = 1; i <= n; i++)
    {
       suma += i;
    }

    printf("Suma prvih %d brojeva iznosi = %d\n", n, suma);

    return 0;
}
