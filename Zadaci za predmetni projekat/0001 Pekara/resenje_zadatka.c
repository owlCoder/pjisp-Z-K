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
void push(PEKARE **, PEKARE *);
char *pop(PEKARE **);
char *top_data(PEKARE *);
unsigned is_empty_stack(PEKARE *);
void empty_stack(PEKARE **);

void load_data(FILE *, PEKARE **);
FILE *file_open(char *, char *);

void raspodela_peciva(FILE *, PEKARE **, const unsigned);

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
    load_data(in, &vrh);
    raspodela_peciva(out, &vrh, atoi(args[1]));
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

void push(PEKARE **vrh, PEKARE *new)
{
    new -> sledeci = *vrh;
    *vrh = new;
}

char *pop(PEKARE **vrh) {
    if(is_empty_stack(*vrh))
        return "\nSTEK JE PRAZAN!\n";
    
    PEKARE *tmp = *vrh;
    *vrh = (*vrh) -> sledeci;
    
    char *s = malloc(30 * sizeof(char));
    sprintf(s, "%s %d", tmp -> naziv, tmp -> obimProdaje);
    free(tmp);

    return s;
}

char *top_data(PEKARE *vrh) {
    if(is_empty_stack(vrh)) {
        printf("\nSTEK JE PRAZAN!\n");
        return NULL;
    }
    else {
        return pop(&vrh);
    }
}

void empty_stack(PEKARE **vrh) {
   
    while(*vrh != NULL) {
        pop(vrh); 
    }
}

void load_data(FILE *in, PEKARE **vrh) {
    PEKARE p;

    while(fscanf(in, "%s %d %lf", 
                       p.naziv, 
                      &p.obimProdaje, 
                      &p.avgCena) != EOF)
        push(vrh, create_item(p.naziv, p.obimProdaje, p.avgCena));
}

FILE *file_open(char *name, char *mode) {
    FILE *f = fopen(name, mode);

    if(f == NULL) {
        printf("\nFile doesn't exist!\n");
        exit(45);
    }
    return f;
}

void raspodela_peciva(FILE *out, PEKARE **vrh, const unsigned proizvedeno)
{
    return;
}
