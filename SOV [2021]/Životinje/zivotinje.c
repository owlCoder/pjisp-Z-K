#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct zivotinja_st
{
    char naziv[8 + 1];
    double prosecnaStarost;
    unsigned brojJedinki;
    char zasticena[11 + 1];
    struct zivotinja_st *sledeci;
} ZIVOTINJA;

void init(ZIVOTINJA **glava) { *glava = NULL; }
ZIVOTINJA *novi(char *naziv, double prosecnaStarost, unsigned brojJedinki)
{
    ZIVOTINJA *novi = malloc(sizeof(ZIVOTINJA));
    if(novi == NULL)
        exit(1);
    strcpy(novi -> naziv, naziv);
    novi -> prosecnaStarost = prosecnaStarost;
    novi -> brojJedinki = brojJedinki;
    if(brojJedinki < 300)
        strcpy(novi -> zasticena, "zasticena");
    else
        strcpy(novi -> zasticena, "nezasticena");
    novi -> sledeci = NULL;

    return novi;
}
void dodaj(ZIVOTINJA **glava, ZIVOTINJA *n)
{
    if(*glava == NULL)
        *glava = n;
    else
        dodaj(&(*glava) -> sledeci, n);
}
void stampaj(ZIVOTINJA *glava)
{
    if(glava != NULL)
        while(glava != NULL) {
            printf("%s %.1lf %s\n", glava -> naziv, glava -> prosecnaStarost, glava -> zasticena);
            glava = glava -> sledeci;
        }
}
void obrisi(ZIVOTINJA **glava) 
{
    if(*glava != NULL)
    {
        obrisi(&(*glava) -> sledeci);
        free(*glava);
        *glava = NULL;
    }
}
void pronadji(ZIVOTINJA *glava)
{
    ZIVOTINJA *min = NULL;
    while(glava != NULL)
    {
        if(min == NULL)
            min = glava;
        else if(glava -> brojJedinki < min -> brojJedinki)
            min = glava;
        glava = glava -> sledeci;
    }

    if(min == NULL)
        printf("\nNo animal!\n");
    else
        printf("\nNajugrozenija je:\n%s %.1lf %s\n", min -> naziv, min -> prosecnaStarost, min -> zasticena);
}

FILE *otvori(char *name, char *mode)
{
    FILE *f = fopen(name, mode);
    if(f == NULL)
        exit(45);
    return f;
}

void iz_datoteke(FILE *in, ZIVOTINJA **glava)
{
    ZIVOTINJA t;
    while(fscanf(in, "%s %lf %u", t.naziv, &t.prosecnaStarost, &t.brojJedinki) != EOF)
    {
        ZIVOTINJA *nov = novi(t.naziv, t.prosecnaStarost, t.brojJedinki);
        dodaj(glava, nov);
    }
}

int main(int argn, char **args)
{
    if(argn != 2)
        exit(15);
    ZIVOTINJA *glava;
    FILE *in = otvori(args[1], "r");

    init(&glava);
    iz_datoteke(in, &glava);
    stampaj(glava);
    pronadji(glava);

    fclose(in);
}