#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GRAD 2 + 1
#define MAX_MESO 20 + 1

typedef struct meso_st {
    char skrOznakaGrada[MAX_GRAD];
    char vrstaMesa[MAX_MESO];
    double cenaPoKg;
    struct meso_st *sledeci;
} meso;

void init_list(meso **);
void add_to_list(meso **, meso *);
meso *create_item(const char *, const char *, const double);
void print_list(FILE *, meso *);
void destroy_list(meso **);

void list_search_by_term(FILE *, meso *, char *);

FILE *otvori_datoteku(char *, char *);
void load_data(FILE *, meso **);

int main(int argc, char **argn)
{
    if(argc != 4)
    {
        printf("\nUsage: %s junetina cene_mesa.txt analiza.txt\n\n", argn[1]);
        exit(35);
    }
    meso *glava;
    FILE *ulazna = otvori_datoteku(argn[2], "r");
    FILE *izlazna = otvori_datoteku(argn[3], "w");

    init_list(&glava);
    load_data(ulazna, &glava);
    print_list(izlazna, glava);
    list_search_by_term(izlazna, glava, argn[1]);
    destroy_list(&glava);

    fclose(ulazna);
    fclose(izlazna);

    return 0;
}

void init_list(meso **glava)
{
    *glava = NULL;
}

void add_to_list(meso **glava, meso *novi)
{
    if((*glava) == NULL) {
        (*glava) = novi;
        return;
    }
    add_to_list(&((*glava) -> sledeci), novi);
}

meso *create_item(const char *grad, const char *tipMesa, const double cena)
{
    meso *tmp = malloc(sizeof(meso));
    if(tmp == NULL)
    {
        printf("\nNo memory for new item in list!\n\n");
        exit(42);
    }
    strcpy(tmp -> skrOznakaGrada, grad); 
    strcpy(tmp -> vrstaMesa, tipMesa);
    (*tmp).cenaPoKg = cena;
    tmp -> sledeci = NULL;

    return tmp;
}

void print_list(FILE *out, meso *glava)
{   
    if(glava == NULL)
    {
        printf("\nLISTA JE PRAZNA!\n");
        exit(33);
    }
    while(glava != NULL)
    {
        fprintf(out, "%6.2lf %s %s\n", glava -> cenaPoKg, glava -> skrOznakaGrada, glava -> vrstaMesa);
        glava = glava -> sledeci;
    }
}

void destroy_list(meso **glava)
{
    if(*glava != NULL)
    {
        destroy_list(&((*glava) -> sledeci));
        free(*glava);
        *glava = NULL;
    }
}

void list_search_by_term(FILE *out, meso *glava, char *term)
{   
    meso *jeftino = NULL;

    while(glava != NULL)
    {
        if(strcmp(glava -> vrstaMesa, term) == 0)
        {
            if(jeftino == NULL)
                jeftino = glava;

            if(glava -> cenaPoKg < jeftino -> cenaPoKg)
                jeftino = glava;
        }
        glava = glava -> sledeci;
    }
    if(jeftino != NULL)
        fprintf(out, "\nNajpovoljnija '%s' je:\n%.2lf %s %s\n", term, 
        jeftino -> cenaPoKg, jeftino -> skrOznakaGrada, jeftino -> vrstaMesa);
    else
        fprintf(out, "\nNigde nema '%s'\n", term);
   // free(jeftino); // izaziva grešku
   /***
        free(): double free detected in tcache 2
        Aborted
   **/
}

FILE *otvori_datoteku(char *name, char *mode)
{
    FILE *f = fopen(name, mode);
    if(f == NULL)
    {
        printf("\nFile %s doesn't exist!\n\n", name);
        exit(45);
    }
    return f;
}

void load_data(FILE *in, meso **glava)
{
    meso *tmp = malloc(sizeof(meso));
    while(fscanf(in, "%s %s %lf", tmp -> skrOznakaGrada, tmp -> vrstaMesa, &(*tmp).cenaPoKg) != EOF)
    {
        meso *novi = create_item(tmp -> skrOznakaGrada, tmp -> vrstaMesa, (*tmp).cenaPoKg);
        add_to_list(glava, novi);
    }
}