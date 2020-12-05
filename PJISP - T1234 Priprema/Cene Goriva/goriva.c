#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OZNAKA 2 + 1
#define MAX_REC 10 + 1
#define MAX_NIZ 25

typedef struct gorivo_st
{
    char oznGrada[MAX_OZNAKA];
    char tipGoriva[MAX_REC];
    double cenaGoriva;
} gorivo;

FILE *otv_dat(char *, char *);
unsigned ucitaj(FILE *, gorivo *);
void obrada(FILE *, gorivo *, char *, const unsigned);
void cena_goriva(gorivo *, const unsigned, char *);

int main(int argn, char **args)
{
    if(argn != 4)
    {
        printf("\nWrong program call!\n");
        exit(36);
    }

    FILE *in = otv_dat(args[2], "r");
    FILE *out = otv_dat(args[3], "w");

    gorivo goriva[MAX_NIZ];

    unsigned n = ucitaj(in, goriva);
    obrada(out, goriva, args[1], n);

    cena_goriva(goriva, n, "min");
    cena_goriva(goriva, n, "max");
    
    fclose(in);
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

unsigned ucitaj(FILE *in, gorivo *goriva)
{
    unsigned i = 0;

    while (fscanf(in, "%s %s %lf", goriva[i].oznGrada, goriva[i].tipGoriva, &goriva[i].cenaGoriva) != EOF)
    {
        i++;
    }
    return i;
}

void obrada(FILE *out, gorivo *goriva, char *tipGoriva, const unsigned n)
{
    unsigned i = 0, p = 0;
    double suma = 0.0;
    for(; i < n; i++)
        if( strcmp(goriva[i].tipGoriva, tipGoriva) == 0) {
            fprintf(out, "%6.2lf %s %s\n", goriva[i].cenaGoriva, goriva[i].oznGrada, goriva[i].tipGoriva);
            suma += goriva[i].cenaGoriva;
            p++;
        }
    char tmp[MAX_NIZ];
    strcpy(tmp, tipGoriva);
    strcat(tmp, ".txt");

    FILE *fp = otv_dat(tmp, "w");
    suma /= p;

    fprintf(fp, "Prosečna cena %sa iznosi: %5.2lf\n", tipGoriva,  suma);
    fclose(fp);
}

void cena_goriva(gorivo *goriva, const unsigned n, char *criteria)
{
    unsigned min = 0, max = 0, i, refrenti = 0;

    min = strcmp(criteria, "min") == 0 ? 1 : 0;
    max = strcmp(criteria, "max") == 0 ? 1 : 0;

    for(i = 1; i < n; i++) 
    {
        if(min && goriva[i].cenaGoriva < goriva[refrenti].cenaGoriva)
            refrenti = i;
        if(max && goriva[i].cenaGoriva > goriva[refrenti].cenaGoriva)
            refrenti = i;
    }
    printf("Gorivo sa %s cenom je: %.2lf\n", (min == 1 ? "najnižom" : "najvišom"), goriva[refrenti].cenaGoriva);
}
