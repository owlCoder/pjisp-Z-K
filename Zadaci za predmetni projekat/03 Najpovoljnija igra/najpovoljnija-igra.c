#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IGRA      10 + 1
#define MAX_ZANR       8 + 1
#define MAX_PLATFORMA  8 + 1

typedef struct igra_st {
    char nazivIgre[MAX_IGRA], zanr[MAX_ZANR], platforma[MAX_PLATFORMA];
    double cena;
    struct igra_st *sledeci;
} IGRE;

void init_list(IGRE **);
IGRE *create_item(const char *, const char *, const char *, const double);
void add_to_list(IGRE **, IGRE *);
void load_data(FILE *, IGRE **);
FILE *fopen_dat(char *, char *);
void list_to_file(FILE *, IGRE *);
void najpovoljnija_igra(FILE *, IGRE *, const char *, const char *);

int main(int argn, char **args)
{
    IGRE *g;
    
    FILE *in = fopen_dat(args[3], "r");
    FILE *out = fopen_dat(args[4], "w");

    init_list(&g);
    load_data(in, &g);
    list_to_file(out, g);
    najpovoljnija_igra(out, g, args[1], args[2]);

    fclose(in);
    fclose(out);

    return 0;
}

void init_list(IGRE **g) { *g = NULL; }

IGRE *create_item(const char *nazivIgre, const char *zanr, const char *platforma, const double cena)
{
    IGRE *new = (IGRE *) malloc(sizeof(IGRE));

    if(new == NULL)
    {
        printf("\nAllocation failed!\tError code: %s\n\n", "0xN0MEM0RY");
        exit(42);
    }

    strcpy(new -> nazivIgre, nazivIgre);
    strcpy(new -> zanr, zanr);
    strcpy(new -> platforma, platforma);
    new -> cena = cena;
    new -> sledeci = NULL;

    return new;
}

void add_to_list(IGRE **g, IGRE *new)
{
    if(*g != NULL) {
        add_to_list(&( (*g) -> sledeci), new);
    }
    else {
        *g = new;
        return;
    }
}

void load_data(FILE *in, IGRE **g)
{
    IGRE load;
    while(fscanf(in, "%s %s %s %lf", load.nazivIgre, load.zanr, load.platforma, &load.cena) != EOF) {
        add_to_list(g, create_item(load.nazivIgre, load.zanr, load.platforma, load.cena));
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

void list_to_file(FILE *out, IGRE *g)
{
    if(g == NULL) {
      printf("\nLista je prazna!\n");
      exit(7);
    }

    while(g != NULL) {
        fprintf(out, "%-10s %-8s %-8s %5.2lf\n", g -> nazivIgre, g -> zanr, g -> platforma , g -> cena);
        g = g -> sledeci;
    }
}

void najpovoljnija_igra(FILE *out, IGRE *g, const char *platforma, const char *zanr)
{
    IGRE *tmp = NULL;
        
    while(g != NULL) 
    {
        if((strcmp(g -> platforma, platforma) == 0) && (strcmp(g -> zanr, zanr) == 0)) {
            if(tmp == NULL)
                tmp = g;
            else if(g -> cena < tmp -> cena)
                tmp = g;
            }
            g = g -> sledeci;
    }

    if(tmp == NULL) {
        fprintf(out, "\nZa %s platformu ne postoje '%s' igre!\n", platforma, zanr);
        return;
    }
    else
    {
        fprintf(out, "\nNajpovoljnija '%s' igra za %s platformu je:\n%s %.2lf\n", zanr, platforma, tmp -> nazivIgre, tmp -> cena);
        return;
    }
}
