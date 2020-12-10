#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME 20 + 1
#define MAX_ARRAY 25

typedef struct tim_st
{
    char drzava[MAX_NAME];
    char tipHrane[MAX_NAME];
    double ocenaZirija;
    double ocenaPublike;
} tim;

FILE *fopen_safe(char *, char *);
unsigned load_data(FILE *, tim *);
void process_data(const tim *, const unsigned, const double);

int main(int argc, char **argn)
{
    if(argc != 3)
    {
        printf("\nUsage: ./program timovi.txt 13.5\n\n");
        exit(45);
    }
    FILE *ulazna = fopen_safe(argn[1], "r");
    tim timovi[MAX_ARRAY];

    unsigned n = load_data(ulazna, timovi);
    process_data(timovi, n, atof(argn[2]));
    
    fclose(ulazna);
    
    return 0;
}

FILE *fopen_safe(char *name, char *mode)
{
    FILE *f = fopen(name, mode);
    if(f == NULL)
    {
        printf("\n\nFILE %s doesn't exist!\n\n", name);
        exit(35);
    }
    return f;
}

unsigned load_data(FILE *in, tim *timovi) 
{
    unsigned i = 0;
    while( fscanf(in, "%s %s %lf %lf", timovi[i].drzava, timovi[i].tipHrane, 
                                      &timovi[i].ocenaZirija, &timovi[i].ocenaPublike) != EOF)
    { i++; }
    return i;
}
void process_data(const tim *timovi, const unsigned n, const double prolaznost)
{
    unsigned i = 0, p = 0;
    double suma = 0.0;
    for(; i < n; i++)
    {
        double ukupnaOcena = timovi[i].ocenaPublike + timovi[i].ocenaZirija;
        if(ukupnaOcena > prolaznost)
        {
            printf("%s %s %.1lf %.1lf\n", timovi[i].drzava,       timovi[i].tipHrane, 
                                          timovi[i].ocenaZirija,  timovi[i].ocenaPublike);
            suma += ukupnaOcena;
            p++;
        }
    }
    printf("Prosecna ocena timova koji su prosli je: %.2lf\n", (suma / p));
}
