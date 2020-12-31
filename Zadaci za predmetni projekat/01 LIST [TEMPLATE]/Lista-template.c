#include <stdio.h>
#include <stdlib.h>

typedef struct LISTA_st
{
    int broj;
    struct LISTA_st *sledeci;
} LISTA;
    
void init_LISTA(LISTA **);
LISTA *kreiraj_element(const int);
void dodaj_u_listu(LISTA *, LISTA **);
void prikaz_podatka(LISTA *);
void prikaz_liste(LISTA *);
void brisanje_liste(LISTA **);

int main(int argc, char **argn)
{
    LISTA *glava;
    init_LISTA(&glava);

    if(argc < 2)
    {
        printf("\nUSAGE: %s num1 ...\n", argn[0]);
        exit(42);
    }
    unsigned brarg = argc - 1, i = 1;
    while(i <= brarg)
        dodaj_u_listu(kreiraj_element(atoi(argn[i++])), &glava);

    printf("\n"); prikaz_liste(glava); printf("\n\n");

    return 0;
}

void init_LISTA(LISTA **glava) { *glava = NULL; }

LISTA *kreiraj_element(const int broj)
{
    LISTA *novi = malloc(sizeof(LISTA));
    if(novi == NULL) {
        printf("\nNema memorije za novi element!\n");
        exit(40);
    }
    novi -> broj = broj;
    novi -> sledeci = NULL;

    return novi;
}

void dodaj_u_listu(LISTA *novi, LISTA **glava)
{
    if(*glava == NULL) {
        (*glava) = novi;
        return;
    }
    else {
        dodaj_u_listu(novi, &((*glava) -> sledeci));
        return;
    }
}

void prikaz_podatka(LISTA *s)
{
    printf("% d   ", s -> broj);
}

void prikaz_liste(LISTA *glava)
{
    if(glava == NULL)
        return;
    else {
        prikaz_podatka(glava);
        prikaz_liste(glava -> sledeci);
    }
}

void brisanje_liste(LISTA **glava)
{
    if(*glava == NULL)
        return;
    
    brisanje_liste(&((*glava) -> sledeci));
    
    free((*glava));
    (*glava) = NULL;
}
