#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAZIV 16 + 1

typedef struct pekara_st {
    char naziv[MAX_NAZIV];
    unsigned obimProdaje;
    double avgCena;
    struct pekara_st *sledeci;
} PEKARE;

void init_stack(PEKARE **);
PEKARE *create_item(const char *, const unsigned, const double);
unsigned push(PEKARE **, PEKARE *, FILE *, const unsigned);
PEKARE *pop(PEKARE **);
unsigned is_empty_stack(PEKARE *);
void empty_stack(PEKARE **);

void load_data(FILE *, FILE *, PEKARE **, const unsigned);
FILE *file_open(char *, char *);

unsigned raspodela_peciva(FILE *, PEKARE **, unsigned);

int main(int argn, char **args)
{
    if (argn != 4) {
        printf("USAGE: %s PROIZVODNJA IN_FILENAME OUT_FILENAME\n", args[0]);
        exit(11);
    }

    PEKARE *vrh;

    FILE *in = file_open(args[2], "r");
    FILE *out = file_open(args[3], "w");

    init_stack(&vrh);
    load_data(in, out, &vrh, atoi(args[1]));
    empty_stack(&vrh);

    fclose(in);
    fclose(out);

    return 0;
}

void init_stack(PEKARE **vrh) { *vrh = NULL; }

unsigned is_empty_stack(PEKARE *vrh) {
    if(vrh == NULL)
        return 1;
    else 
        return 0;
}

PEKARE *create_item(const char *naziv, const unsigned obimProdaje, const double avgCena) {
    PEKARE *new = (PEKARE *) malloc(sizeof(PEKARE));

    if(new == NULL) {
        printf("\nRAM allocation failed!\n\n");
        exit(42);
    }
    strcpy(new -> naziv, naziv);
    new -> obimProdaje = obimProdaje;
    new -> avgCena = avgCena;
    new -> sledeci = NULL;

    return new;
}

unsigned push(PEKARE **vrh, PEKARE *new, FILE *out, const unsigned proizvedeno)
{
    new -> sledeci = *vrh;
    *vrh = new;

    return raspodela_peciva(out, vrh, proizvedeno);
}

PEKARE *pop(PEKARE **vrh) {
    if(is_empty_stack(*vrh))
        return NULL;
    
    PEKARE *tmp = *vrh;
    *vrh = (*vrh) -> sledeci;
    
    return tmp;
}

void empty_stack(PEKARE **vrh) {
   
    while(*vrh != NULL) {
        pop(vrh); 
    }
}

void load_data(FILE *in, FILE *out, PEKARE **vrh, const unsigned proizvedeno) {
    PEKARE p;
    int ostatak = proizvedeno;
    while(fscanf(in, "%s %d %lf", 
                       p.naziv, 
                      &p.obimProdaje, 
                      &p.avgCena) != EOF)
        ostatak = push(vrh, create_item(p.naziv, p.obimProdaje, p.avgCena), out, ostatak);
}

FILE *file_open(char *name, char *mode) {
    FILE *f = fopen(name, mode);

    if(f == NULL) {
        printf("\nFile doesn't exist!\n");
        exit(45);
    }
    return f;
}

unsigned raspodela_peciva(FILE *out, PEKARE **vrh, unsigned proizvedeno)
{
    if(is_empty_stack(*vrh))
        exit(EXIT_FAILURE);
    else {
        int ostatak, dobijeno;
        char status[10];
        proizvedeno = proizvedeno < 0 ? 0 : proizvedeno;

        if(proizvedeno >= (*vrh) -> obimProdaje) {
            ostatak = proizvedeno - ((*vrh) -> obimProdaje);
            dobijeno = (*vrh) -> obimProdaje;
            strcpy(status, "OK");
        }
        else if(proizvedeno == 0) {
            dobijeno = 0;
            strcpy(status, "MANJAK");
        }
        else {
            if(proizvedeno > 0) {
                dobijeno = ostatak;
                ostatak = 0;
            }
            strcpy(status, "MANJAK");
        }
        fprintf(out, "%-10s %5d %-10s\n", (*vrh) -> naziv, dobijeno, status);
        pop(vrh);

        return ostatak;
    }
}
