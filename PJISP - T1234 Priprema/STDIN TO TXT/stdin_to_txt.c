#include <stdio.h>
#include <stdlib.h>

#define MAX_NIZ 25

typedef struct osoba_st
{
    char ime[MAX_NIZ];
    unsigned godine;
} osoba;

FILE *otv_dat(char *, char *);
unsigned ucitaj(osoba *);
void ispisi(FILE *, osoba *, const unsigned n);

int main(int argn, char **args) // ./a.out izlaz.txt
{
    if(argn != 2)
    {
        printf("Wrong program call!");
        exit(36);
    }
    FILE *out = otv_dat(args[1], "w");

    osoba osobe[MAX_NIZ];

    unsigned n = ucitaj(osobe);
    ispisi(out, osobe, n);
    
    fclose(out);

    return 0;
}

FILE *otv_dat(char *dat, char *rezim)
{
    FILE *datoteka = fopen(dat, rezim);
    if(datoteka == NULL)
    {
        printf("\nFile open error!\n");
        exit(55);
    }
    return datoteka;
}

unsigned ucitaj(osoba *osobe)
{
    unsigned i = 0, izbor = 1;
    while(izbor == 1)
    {
        printf("\nUnesite podatke za osobu %u\n", i + 1);
        
        printf("\tIme[%d] = ", i);
        scanf("%s", osobe[i].ime);

        printf("\tGodine[%d] = ", i);
        scanf("%u", &osobe[i].godine);

        i++;
        printf("\nUnositi jos?\n1 - Da, 2 - Ne\n>> ");
        scanf("%u", &izbor);
    }
    return i;
}

void ispisi(FILE *out, osoba *osobe, const unsigned n)
{
    unsigned i = 0;

    for(; i < n; i++)
        fprintf(out, "%s %u\n", osobe[i].ime, osobe[i].godine);
}
