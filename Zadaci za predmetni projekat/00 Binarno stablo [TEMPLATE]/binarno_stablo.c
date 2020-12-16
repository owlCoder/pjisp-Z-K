#include <stdio.h>
#include <stdlib.h>

typedef struct stablo_st
{
    int broj;
    struct stablo_st *levi;
    struct stablo_st *desni;
} STABLO;
    
void init_stablo(STABLO **);
STABLO *kreiraj_element(const int);
void dodaj_u_stablo(STABLO *, STABLO **);
void prikaz_podatka(STABLO *);
void prikaz_stabla(STABLO *);
void brisanje_stabla(STABLO **);

int main(int argc, char **argn)
{
    STABLO *koren;
    init_stablo(&koren);

    if(argc < 2)
    {
        printf("\nUSAGE: %s num1 ...\n", argn[0]);
        exit(42);
    }
    unsigned brarg = argc - 1, i = 1;
    while(i <= brarg)
        dodaj_u_stablo(kreiraj_element(atoi(argn[i++])), &koren);

    printf("\n"); prikaz_stabla(koren); printf("\n\n");

    return 0;
}

void init_stablo(STABLO **koren) { *koren = NULL; }

STABLO *kreiraj_element(const int broj)
{
    STABLO *novi = malloc(sizeof(STABLO));
    if(novi == NULL)
    {
        printf("\nNema memorije za novi element!\n");
        exit(40);
    }
    novi -> broj = broj;
    novi -> levi = NULL;
    novi -> desni = NULL;

    return novi;
}

void dodaj_u_stablo(STABLO *novi, STABLO **koren)
{
    if(*koren == NULL)
    {
        (*koren) = novi;
        return;
    }
    else if(novi -> broj < (*koren) -> broj)
    {
        dodaj_u_stablo(novi, &((*koren) -> levi));
        return;
    }
    else
    {
        dodaj_u_stablo(novi, &((*koren) -> desni));
        return;
    }   
}

void prikaz_podatka(STABLO *s)
{
    printf("% d   ", s -> broj);
}

void prikaz_stabla(STABLO *koren)
{
    if(koren == NULL)
    {
        return;
    }
    else
    {
        prikaz_stabla(koren -> levi);
        prikaz_podatka(koren);
        prikaz_stabla(koren -> desni);
        
    }
}

void brisanje_stabla(STABLO **koren)
{
    if(*koren == NULL)
        return;
    
    brisanje_stabla(&((*koren) -> levi));
    brisanje_stabla(&((*koren) -> desni));
    
    free((*koren));
    (*koren) = NULL;
}
