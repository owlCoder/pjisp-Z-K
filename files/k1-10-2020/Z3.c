/**
 * Author:    Danijel Jovanovic (@owlCoder)
 * Created:   30.10.2020
 *
 * (c) PJISP K1 2020/10
 **/

#include<stdio.h>
#include <math.h>

int main(void)
{
    int n =0, i = 0;
    double x = 0., sum = 0.;

    //verify input
    do {
       printf("\nUneti broj n\n>> ");
       scanf("%d", &n);
    } while(n < 1);

    // enter x limits ±1
     do {
       printf("\nUneti x (-1, 1)\n>> ");
       scanf("%lf", &x);
    } while(x <= -1 || x >= 1);

    // calculate arctgx
    for(i = 1; i <= n; i++)
    {
       sum += ( ( pow(-1, i + 1) *
                 ( pow(x, 2*i-1) ) )
                 / ( (2*i)-1 ) );
    }
    // prema formuli zadatka dobija se pogresna vrednost arctanx!!!
    /// PRAVA FORMULA DATA JE KODOM IZNAD!

    printf("\n\narctg(%.3lf) = %.3lf\n",
                                x, sum);

    return 0;
}
