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
    int a = unesiPrirodniBroj("a");
    int n = unesiPrirodniBroj("n");
    int k = unesiPrirodniBroj("k");

    int sumaArt = 0, sumaGeo = 0, i = 0, nizArt[n], nizGeo[n];

    for(i = 1; i <= n; i++)
        nizArt[i-1] = a + k * (i - 1);

    for(i = 1; i <= n; i++)
        nizGeo[i-1] = a * pow(k, i - 1);

    for(i = 0; i < n; i++)
    {
        if(i % 2 == 0) sumaArt += nizArt[i];
        else sumaGeo += nizGeo[i];
    }

    printf("\nSuma aritmeticke progresije: %d", sumaArt);
    printf("\nSuma geometrijske progresije: %d", sumaGeo);
    puts("");

    return 0;
}
