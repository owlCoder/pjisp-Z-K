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

int main(int argc, char **argn)
{
    if(argc != 4)
    {
        printf("\nUsage: %s tipgoriva in.txt out.txt\n\n", argn[0]);
        exit(35);
    }
    goriva *glava;
    FILE *ulazna = otvori_datoteku(argn[2], "r");
    FILE *izlazna = otvori_datoteku(argn[3], "w");

    init_list(&glava);
    load_data(ulazna, &glava);
    print_list(izlazna, glava);
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
   struct gorivo_st* trenutni; 

    if (*glava == NULL || (*glava) -> cena >= novi -> cena) { 
        novi -> sledeci = *glava; 
        *glava = novi; 
    } 
    else { 
        trenutni = *glava; 
        while (trenutni -> sledeci != NULL 
               && trenutni -> sledeci -> cena < novi -> cena) { 
            trenutni  = trenutni -> sledeci; 
        } 
        novi -> sledeci = trenutni -> sledeci; // prevezivanje na 
        trenutni -> sledeci = novi; 
    } 
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
