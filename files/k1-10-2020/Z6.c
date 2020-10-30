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

int main(void)
{
    int n = unesiPrirodniBroj("n");
    int i, suma = 1;

    for(i = 2; i < n; i++)
        if(n % i == 0)
            suma += i;

    if(n == suma)
        printf("\nBroj je savrsen!\n");
    else
        printf("\nBroj nije savrsen!\n");

    return 0;
}
