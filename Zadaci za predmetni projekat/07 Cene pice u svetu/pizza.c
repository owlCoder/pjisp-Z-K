#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GRAD     2 + 1
#define MAX_DRZAVA   3 + 1
#define MAX_PIZZA   20 + 1

typedef struct pizza_st {
    char drzava[MAX_DRZAVA], grad[MAX_GRAD], naziv[MAX_PIZZA];
    unsigned cena;
    struct pizza_st *sledeci;
} PIZZE;

void init_list(PIZZE **);
void add_to_list(PIZZE **, PIZZE *);
PIZZE *create_item(const unsigned, const char *, const char *, const char *);
void print_list(FILE *, PIZZE *);
void destroy_list(PIZZE **);

FILE *otvori_datoteku(char *, char *);
void load_data(FILE *, PIZZE **);
void avg_pizza(FILE *, PIZZE *, char *, char *);

int main(int argc, char **args)
{
    if(argc != 5)
    {
        printf("\nUsage: %s DRZAVA tipPizze in.txt out.txt\n\n", args[1]);
        exit(35);
    }
    PIZZE *glava;
    FILE *ulazna = otvori_datoteku(args[3], "r");
    FILE *izlazna = otvori_datoteku(args[4], "w");

    init_list(&glava);
    load_data(ulazna, &glava);
    print_list(izlazna, glava);
    avg_pizza(izlazna, glava, args[1], args[2]);
    destroy_list(&glava);

    fclose(ulazna);
    fclose(izlazna);

    return 0;
}

void init_list(PIZZE **glava)
{
    *glava = NULL;
}

void add_to_list(PIZZE **glava, PIZZE *novi)
{
   if(*glava == NULL) {
       *glava = novi;
       return;
   }
   add_to_list(&(*glava) -> sledeci, novi);
}

PIZZE *create_item(const unsigned cena, const char *drzava, const char *grad, const char *naziv)
{
    PIZZE *tmp = malloc(sizeof(PIZZE));
    if(tmp == NULL)
    {
        printf("\nNo memory for new item in list!\n\n");
        exit(42);
    }
    strcpy(tmp -> naziv, naziv); 
    strcpy(tmp -> drzava, drzava);
    strcpy(tmp -> grad, grad);
    (*tmp).cena = cena;
    tmp -> sledeci = NULL;

    return tmp;
}

void print_list(FILE *out, PIZZE *glava)
{   
    if(glava == NULL)
    {
        printf("\nLISTA JE PRAZNA!\n");
        exit(33);
    }
    while(glava != NULL)
    {
        fprintf(out, "%4u %s %s %s\n", glava -> cena, glava -> drzava, glava -> grad, glava -> naziv);
        glava = glava -> sledeci;
    }
}

void destroy_list(PIZZE **glava)
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

void load_data(FILE *in, PIZZE **glava)
{
    PIZZE *tmp = malloc(sizeof(PIZZE));
    while(fscanf(in, "%u %s %s %s", &tmp -> cena, tmp -> drzava, tmp -> grad, tmp -> naziv) != EOF)
    {
        PIZZE *novi = create_item(tmp -> cena, tmp -> drzava, tmp -> grad, tmp -> naziv);
        add_to_list(glava, novi);
    }
}

void avg_pizza(FILE *out, PIZZE *g, char *drzava, char *naziv)
{
    int br = 0; 
    double suma = 0.0;
    while(g != NULL) {
        if(strcmp(g -> drzava, drzava) == 0 && strcmp(g -> naziv, naziv) == 0) {
            suma += g -> cena;
            br++;
        }
        g = g -> sledeci;
    }
    if(br == 0) {
        fprintf(out, "\nNOT FOUND!\n");
        return;
    }
    else {
        fprintf(out, "\nAVG = %6.2lf", suma / br);
        return;
    }
}
