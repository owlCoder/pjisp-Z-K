#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KUHINJA  20 + 1
#define MAX_RESTORAN 10 + 1

typedef struct restoran_st {
    char naziv[MAX_RESTORAN];
    char vrsta[MAX_KUHINJA];
    double ocena;
    struct restoran_st *sledeci;
} RESTORAN;

void init_list(RESTORAN **);
void add_to_list(RESTORAN **, RESTORAN *);
RESTORAN *create_item(const char *, const char *, const double);
void print_list(FILE *, RESTORAN *);
void destroy_list(RESTORAN **);

FILE *otvori_datoteku(char *, char *);
void load_data(FILE *, RESTORAN **);
void best_restoran(FILE *, RESTORAN *, char *);

int main(int argc, char **args)
{
    if(argc != 4)
    {
        printf("\nUsage: %s tip RESTORAN in.txt out.txt\n\n", args[1]);
        exit(35);
    }
    RESTORAN *glava;
    FILE *ulazna = otvori_datoteku(args[2], "r");
    FILE *izlazna = otvori_datoteku(args[3], "w");

    init_list(&glava);
    load_data(ulazna, &glava);
    print_list(izlazna, glava);
    best_restoran(izlazna, glava, args[1]);
    destroy_list(&glava);

    fclose(ulazna);
    fclose(izlazna);

    return 0;
}

void init_list(RESTORAN **glava)
{
    *glava = NULL;
}

void add_to_list(RESTORAN **glava, RESTORAN *novi)
{
   if(*glava == NULL) {
       *glava = novi;
       return;
   }
   add_to_list(&(*glava) -> sledeci, novi);
}

RESTORAN *create_item(const char *naziv, const char *vrsta, const double ocena)
{
    RESTORAN *tmp = malloc(sizeof(RESTORAN));
    if(tmp == NULL)
    {
        printf("\nNo memory for new item in list!\n\n");
        exit(42);
    }
    strcpy(tmp -> naziv, naziv); 
    strcpy(tmp -> vrsta, vrsta);
    tmp -> ocena = ocena;
    tmp -> sledeci = NULL;

    return tmp;
}

void print_list(FILE *out, RESTORAN *glava)
{   
    if(glava == NULL)
    {
        printf("\nLISTA JE PRAZNA!\n");
        exit(33);
    }
    while(glava != NULL)
    {
        fprintf(out, "%3.1lf %-10s %s\n", glava -> ocena, glava -> naziv, glava -> vrsta);
        glava = glava -> sledeci;
    }
}

void destroy_list(RESTORAN **glava)
{
    if(*glava != NULL)
    {
        destroy_list(&((*glava) -> sledeci));
        free(*glava);
        *glava = NULL;
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

void load_data(FILE *in, RESTORAN **glava)
{
    RESTORAN *tmp = malloc(sizeof(RESTORAN));
    while(fscanf(in, "%s %s %lf", tmp -> naziv, tmp -> vrsta, &tmp -> ocena) != EOF)
    {
        RESTORAN *novi = create_item(tmp -> naziv, tmp -> vrsta, tmp -> ocena);
        add_to_list(glava, novi);
    }
}

void best_restoran(FILE *out, RESTORAN *g, char *criteria)
{
    RESTORAN *r = NULL;
    while(g != NULL) {
        if(strcmp(g -> vrsta, criteria) == 0) {
            if(r == NULL)
                r = g;
            if(g -> ocena > r -> ocena)
                r = g;
        }
        g = g -> sledeci;
    }
    if(r == NULL) {
        fprintf(out, "\nU gradu ne postoji %s restoran!", criteria);
        return;
    }
    else {
        fprintf(out, "\nNajbolje ocenjen %s restoran u gradu je:\n%3.1lf %-10s %s", 
                criteria, r -> ocena, r -> naziv, r -> vrsta);
        return;
    }
}
