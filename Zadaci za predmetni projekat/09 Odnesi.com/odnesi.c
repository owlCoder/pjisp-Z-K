#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KUHINJA  20 + 1
#define MAX_RESTORAN 10 + 1

typedef struct restoran_st {
    char naziv[MAX_RESTORAN];
    char vrsta[MAX_KUHINJA];
    double ocena;
    struct restoran_st *levi, *desni;
} RESTORAN;

void init_tree(RESTORAN **);
void add_to_tree(RESTORAN **, RESTORAN *);
RESTORAN *create_item(const char *, const char *, const double);
void print_tree(FILE *, RESTORAN *);
void destroy_tree(RESTORAN **);

FILE *otvori_datoteku(char *, char *);
void load_data(FILE *, RESTORAN **);
void worst_restoran(FILE *, RESTORAN *);

int main(int argc, char **args)
{
    if(argc != 3)
    {
        printf("\nUsage: %s RESTORAN in.txt out.txt\n\n", args[1]);
        exit(35);
    }
    RESTORAN *koren;
    FILE *ulazna = otvori_datoteku(args[1], "r");
    FILE *izlazna = otvori_datoteku(args[2], "w");

    init_tree(&koren);
    load_data(ulazna, &koren);
    print_tree(izlazna, koren);
    worst_restoran(izlazna, koren);
    destroy_tree(&koren);

    fclose(ulazna);
    fclose(izlazna);

    return 0;
}

void init_tree(RESTORAN **koren)
{
    *koren = NULL;
}

void add_to_tree(RESTORAN **koren, RESTORAN *novi)
{
   if(*koren == NULL) {
       *koren = novi;
       return;
   }
   else if(novi -> ocena < (*koren) -> ocena)
        add_to_tree(&(*koren) -> levi, novi);
   else
        add_to_tree(&(*koren) -> desni, novi);
}

RESTORAN *create_item(const char *naziv, const char *vrsta, const double ocena)
{
    RESTORAN *tmp = malloc(sizeof(RESTORAN));
    if(tmp == NULL)
    {
        printf("\nNo memory for new item in tree!\n\n");
        exit(42);
    }
    strcpy(tmp -> naziv, naziv); 
    strcpy(tmp -> vrsta, vrsta);
    tmp -> ocena = ocena;
    tmp -> levi = NULL;
    tmp -> desni = NULL;

    return tmp;
}

void print_tree(FILE *out, RESTORAN *koren)
{   
    if(koren == NULL)
        return;

    print_tree(out, koren -> desni);
    fprintf(out, "%3.1lf %-10s %s\n", koren -> ocena, koren -> naziv, koren -> vrsta);
    print_tree(out, koren -> levi);
}

void destroy_tree(RESTORAN **koren)
{
    if(*koren != NULL)
    {
        destroy_tree(&((*koren) -> levi));
        destroy_tree(&((*koren) -> desni));
        free(*koren);
        *koren = NULL;
    }
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

void load_data(FILE *in, RESTORAN **koren)
{
    RESTORAN *tmp = malloc(sizeof(RESTORAN));
    while(fscanf(in, "%s %s %lf", tmp -> naziv, tmp -> vrsta, &tmp -> ocena) != EOF)
    {
        RESTORAN *novi = create_item(tmp -> naziv, tmp -> vrsta, tmp -> ocena);
        add_to_tree(koren, novi);
    }
}

void worst_restoran(FILE *out, RESTORAN *g)
{
    RESTORAN *r = NULL;
    while(g != NULL) {
        if(r == NULL)
            r = g;
        if(g -> ocena < r -> ocena)
            r = g;
        g = g -> levi;
    }

    fprintf(out, "\nNajgore ocenjen restoran u gradu je:\n%3.1lf %-10s %s", 
            r -> ocena, r -> naziv, r -> vrsta);
}
