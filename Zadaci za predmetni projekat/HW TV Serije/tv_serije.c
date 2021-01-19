#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING      20 + 1
#define MAX_POREKLO      3 + 1

typedef struct serija_st {
    char naziv[MAX_STRING], 
         madeIn[MAX_POREKLO], zanr[MAX_STRING];
    int godinaPremijere, brEpizoda;
    double avgTrajanje;
    struct serija_st *sledeci;
} SERIJE;

unsigned main__test_case(const int, char **);

void init_list(SERIJE **);
SERIJE *create_item(const char *, const int, const int, const double, const char *, const char *);
void add_to_list(SERIJE **, SERIJE *);
void load_data(FILE *, SERIJE **);
FILE *fopen_dat(char *, char *);
void item_print(FILE *, SERIJE *);
void avg_trajanje_state_criteria(FILE *, SERIJE *, const char *);
void max_duzina_trajanja(SERIJE *);
void brisanje_liste(SERIJE **);

void main(int argn, char **args) 
{ 
    main__test_case(argn, args); 
}

unsigned main__test_case(const int argn, char **args)
{
    if (argn != 6) {
        printf("USAGE: %s IN_FILENAME DRZAVA SERIJA GODINA ZANR\n", args[0]);
        exit(11);
    }
    SERIJE *g;

    char *izl = (char *) malloc( (10 + 1) * sizeof(char));
    char *extension = (char *) malloc(strlen("SCC.txt")); // SCC - SPECIFIC COUNTRY CODE

    strcpy(extension, (args[2])); strcat(extension, ".txt");
    strcpy(izl, "serije_"); strcat(izl, extension);
    free(extension);

    FILE *in = fopen_dat(args[1], "r");
    FILE *out = fopen_dat(izl, "w");

    init_list(&g);
    load_data(in, &g);
    avg_trajanje_state_criteria(out, g, args[2]);
    max_duzina_trajanja(g);
    brisanje_liste(&g);

    fclose(in);
    fclose(out);
    free(izl);

    return EXIT_SUCCESS;
}

void init_list(SERIJE **g) { *g = NULL; }

SERIJE *create_item(const char *n, const int be, const int g, 
                    const double t, const char *scc, const char *z)
{
    SERIJE *new = (SERIJE *) malloc(sizeof(SERIJE));

    if(new == NULL)
    {
        printf("\nAllocation failed!\tError code: %s\n\n", "0xN0MEM0RY");
        exit(42);
    }

    strcpy(new -> naziv, n);
    new -> brEpizoda = be;
    new -> godinaPremijere = g;
    new -> avgTrajanje = t;
    strcpy(new -> madeIn, scc);
    strcpy(new -> zanr, z);
    new -> sledeci = NULL;

    return new;
}

void add_to_list(SERIJE **g, SERIJE *new)
{
    if(*g != NULL) {
        add_to_list(&( (*g) -> sledeci), new);
    }
    else {
        *g = new;
        return;
    }
}

void load_data(FILE *in, SERIJE **g)
{
    SERIJE load;
    while(fscanf(in, "%s %d %d %lf %s %s", load.naziv, &load.brEpizoda, &load.godinaPremijere, 
                                          &load.avgTrajanje, load.madeIn, load.zanr) != EOF) {
        add_to_list(g, create_item(load.naziv,       load.brEpizoda,   load.godinaPremijere, 
                                   load.avgTrajanje, load.madeIn,      load.zanr));
    }
}

FILE *fopen_dat(char *name, char *mode)
{
    FILE *f = fopen(name, mode);

    if(f == NULL)
    {
        printf("\nFile doesn't exist!\tError code: %s\n\n", "0xN0F1LE");
        exit(45);
    }
    return f;
}

void item_print(FILE *out, SERIJE *g)
{
    if(g == NULL) {
      printf("\nLista je prazna!\n");
      exit(7);
    }

    fprintf(out, "%-10s %3d %d %5.2lf %-3s %-10s\n", g -> naziv,           g -> brEpizoda,   
                                                      g -> godinaPremijere, g -> avgTrajanje,
                                                      g -> madeIn,          g -> zanr);
}

void avg_trajanje_state_criteria(FILE *out, SERIJE *g, const char *madeIn)
{
    double suma = 0.0; 
    unsigned counter = 0;

    while(g != NULL) {
        if((strcmp(g -> madeIn, madeIn) == 0)) {
            suma += g -> brEpizoda;
            counter++;
        }
        g = g -> sledeci;
    }

    if(counter == 0) {
        fprintf(out, "Za %s ne postoje snimljene SERIJE!\n", madeIn);
        return;
    }
    else
    {
        fprintf(out, "Za %s prosečan broj epizoda je: %.3lf\n", madeIn, suma / counter);
        return;
    }
}

void max_duzina_trajanja(SERIJE *g)
{
    SERIJE *tmp;
    tmp = NULL;
    double *max = (double *) malloc(sizeof(double)),
           *chk = (double *) malloc(sizeof(double));

    while(g != NULL)
    {
        if(tmp == NULL) {
             tmp = g;
            *max = tmp -> brEpizoda * (double) (tmp -> avgTrajanje);
        }
        *chk = g -> brEpizoda * (double) (g -> avgTrajanje);

        if(*chk > *max) {
            tmp = g;
            *max = tmp -> brEpizoda * (double) (tmp -> avgTrajanje);
        }
        g = g -> sledeci;
    }
    item_print(stdout, tmp);

    free(chk); 
    free(max);    
}

void brisanje_liste(SERIJE **glava)
{
    if(*glava == NULL)
        return;
    
    brisanje_liste(&((*glava) -> sledeci));
    
    free(*glava);
    (*glava) = NULL;
}
