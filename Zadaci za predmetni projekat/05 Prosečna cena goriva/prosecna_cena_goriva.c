#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GRAD 2 + 1
#define MAX_GORIVO 10 + 1

typedef struct gorivo_st {
    char skrOznakaGrada[MAX_GRAD];
    char tipGoriva[MAX_GORIVO];
    double cena;
    struct gorivo_st *sledeci;
} goriva;

void init_list(goriva **);
void add_to_list(goriva **, goriva *);
goriva *create_item(const char *, const char *, const double);
void print_list(FILE *, goriva *);
void destroy_list(goriva **);

FILE *otvori_datoteku(char *, char *);
void load_data(FILE *, goriva **);
void avg_gorivo(FILE *, goriva *, char *);

int main(int argc, char **args)
{
    if(argc != 4)
    {
        printf("\nUsage: %s tipgoriva in.txt out.txt\n\n", args[1]);
        exit(35);
    }
    goriva *glava;
    FILE *ulazna = otvori_datoteku(args[2], "r");
    FILE *izlazna = otvori_datoteku(args[3], "w");

    init_list(&glava);
    load_data(ulazna, &glava);
    print_list(izlazna, glava);
    avg_gorivo(izlazna, glava, args[1]);
    destroy_list(&glava);

    fclose(ulazna);
    fclose(izlazna);

    return 0;
}

void init_list(goriva **glava)
{
    *glava = NULL;
}

void add_to_list(goriva **glava, goriva *novi)
{
   if(*glava == NULL) {
       *glava = novi;
       return;
   }
   add_to_list(&(*glava) -> sledeci, novi);
}

goriva *create_item(const char *grad, const char *tipGoriva, const double cena)
{
    goriva *tmp = malloc(sizeof(goriva));
    if(tmp == NULL)
    {
        printf("\nNo memory for new item in list!\n\n");
        exit(42);
    }
    strcpy(tmp -> skrOznakaGrada, grad); 
    strcpy(tmp -> tipGoriva, tipGoriva);
    (*tmp).cena = cena;
    tmp -> sledeci = NULL;

    return tmp;
}

void print_list(FILE *out, goriva *glava)
{   
    if(glava == NULL)
    {
        printf("\nLISTA JE PRAZNA!\n");
        exit(33);
    }
    while(glava != NULL)
    {
        fprintf(out, "%6.2lf %s %s\n", glava -> cena, glava -> skrOznakaGrada, glava -> tipGoriva);
        glava = glava -> sledeci;
    }
}

void destroy_list(goriva **glava)
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

void load_data(FILE *in, goriva **glava)
{
    goriva *tmp = malloc(sizeof(goriva));
    while(fscanf(in, "%s %s %lf", tmp -> skrOznakaGrada, tmp -> tipGoriva, &(*tmp).cena) != EOF)
    {
        goriva *novi = create_item(tmp -> skrOznakaGrada, tmp -> tipGoriva, (*tmp).cena);
        add_to_list(glava, novi);
    }
}

void avg_gorivo(FILE *out, goriva *g, char *criteria)
{
    int br = 0; 
    double suma = 0.0;
    while(g != NULL) {
        if(strcmp(g -> tipGoriva, criteria) == 0) {
            suma += g -> cena;
            br++;
        }
        g = g -> sledeci;
    }
    if(br == 0) {
        fprintf(out, "\nNema %sa", criteria);
        return;
    }
    else {
        fprintf(out, "\nAVG = %6.2lf", suma / br);
        return;
    }
}
