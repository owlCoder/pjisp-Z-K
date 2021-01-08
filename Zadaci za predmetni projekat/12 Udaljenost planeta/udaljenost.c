#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_NAZIV 16 + 1

typedef struct planeta_st {
    char naziv[MAX_NAZIV];
    int x, y, z;
    struct planeta_st *sledeci;
} PLANETA;

typedef struct razdaljine_st {
    PLANETA *p;
    double udaljenost;
    struct razdaljine_st *sledeci;
} RAZDALJINA;

void init_list(PLANETA **);
void add_to_list(PLANETA **, PLANETA *);
PLANETA *create_item(const char *, const int, const int, const int);
void print_list(FILE *, PLANETA *);
void print_item(FILE *, PLANETA *p);
void destroy_list(PLANETA **);

void i_list(RAZDALJINA **);
void a_list(RAZDALJINA **, RAZDALJINA *);
void p_list(RAZDALJINA *);
RAZDALJINA *c_item(const double, PLANETA *);
void d_list(RAZDALJINA **);

FILE *otvori_datoteku(char *, char *);
void load_data(FILE *, PLANETA **);
void max_udaljenost(FILE *, PLANETA *, RAZDALJINA **r);
double calc_distance(PLANETA *, PLANETA *);

int main(int argc, char **args)
{
    if(argc != 3)
    {
        printf("\nUsage: %s in.txt out.txt\n\n", args[1]);
        exit(35);
    }
    PLANETA *glava;
    RAZDALJINA *r;
    FILE *ulazna = otvori_datoteku(args[1], "r");
    FILE *izlazna = otvori_datoteku(args[2], "w");

    init_list(&glava);
    i_list(&r);
    load_data(ulazna, &glava);
    max_udaljenost(izlazna, glava, &r);
    p_list(r);
    destroy_list(&glava);
    d_list(&r);

    fclose(ulazna);
    fclose(izlazna);

    return 0;
}

void init_list(PLANETA **glava)
{
    *glava = NULL;
}

void add_to_list(PLANETA **glava, PLANETA *novi)
{
   if(*glava == NULL) {
       *glava = novi;
       return;
   }
    add_to_list(&(*glava) -> sledeci, novi);
}

PLANETA *create_item(const char *naziv, const int x, const int y, const int z)
{
    PLANETA *tmp = malloc(sizeof(PLANETA));
    if(tmp == NULL)
    {
        printf("\nNo memory for new item in list!\n\n");
        exit(42);
    }
    strcpy(tmp -> naziv, naziv); 
    tmp -> x = x;
    tmp -> y = y;
    tmp -> z = z;
    tmp -> sledeci = NULL;

    return tmp;
}

void print_list(FILE *out, PLANETA *glava)
{   
    if(glava == NULL)
        return;

    fprintf(out, "%s %d %d %d\n", glava -> naziv, glava -> x, glava -> y, glava -> z);
    print_list(out, glava -> sledeci);
}

void print_item(FILE *out, PLANETA *p)
{
    fprintf(out, "%s %d %d %d\n", p -> naziv, p -> x, p -> y, p -> z);
}

void destroy_list(PLANETA **glava)
{
    if(*glava != NULL)
    {
        destroy_list(&((*glava) -> sledeci));
        free(*glava);
        *glava = NULL;
    }
}

void i_list(RAZDALJINA **glava)
{
    *glava = NULL;
}

void a_list(RAZDALJINA **glava, RAZDALJINA *novi)
{
   if(*glava == NULL) {
       *glava = novi;
       return;
   }
    a_list(&(*glava) -> sledeci, novi);
}

RAZDALJINA *c_item(const double razdaljina, PLANETA *g)
{
    RAZDALJINA *tmp = malloc(sizeof(RAZDALJINA));
    if(tmp == NULL)
    {
        printf("\nNo memory for new item in list!\n\n");
        exit(42);
    }
    tmp -> p = g;
    tmp -> udaljenost = razdaljina;
    tmp -> sledeci = NULL;

    return tmp;
}

void d_list(RAZDALJINA **glava)
{
    if(*glava != NULL)
    {
        d_list(&((*glava) -> sledeci));
        free(*glava);
        *glava = NULL;
    }
}

void p_list(RAZDALJINA *glava)
{   
    if(glava == NULL)
        return;

    printf("%s %3.2lf\n", glava -> p -> naziv, glava -> udaljenost);
    p_list(glava -> sledeci);
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

void load_data(FILE *in, PLANETA **glava)
{
    PLANETA *tmp = malloc(sizeof(PLANETA));
    while(fscanf(in, "%s %d %d %d\n", tmp -> naziv, &tmp -> x, &tmp -> y, &tmp -> z) != EOF)
    {
        PLANETA *novi = create_item(tmp -> naziv, tmp -> x, tmp -> y, tmp -> z);
        add_to_list(glava, novi);
    }
}

void max_udaljenost(FILE *out, PLANETA *glava, RAZDALJINA **d)
{
    PLANETA *p1, *p2;
    p1 = glava;
    p2 = glava -> sledeci;

    PLANETA *a;
    PLANETA *b;
    for(a = glava; a != NULL; a = a -> sledeci) {
        for(b = a -> sledeci; b != NULL; b = b -> sledeci) {
            if (calc_distance(a, b) > calc_distance(p1, p2)) {
                p1 = a;
                p2 = b;
            }
        }
    }
    print_item(out, p1);
    print_item(out, p2);
    fprintf(out, "%.2f\n", calc_distance(p1, p2));

}

double calc_distance(PLANETA *p1, PLANETA *p2)
{
    return sqrt( pow(p1 -> x - p2 -> x, 2) + pow(p1 -> y - p2 -> y, 2) + pow(p1 -> z - p2 -> z, 2));
}
