#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GRAD        2 + 1
#define MAX_BIOSKOP    10 + 1
#define MAX_FILM        8 + 1
#define MAX_ZANR        9 + 1

typedef struct projekcija_st {
    char grad[MAX_GRAD], bioskop[MAX_BIOSKOP], 
         film[MAX_FILM], zanr[MAX_ZANR];
    double cena;
    struct projekcija_st *levi, *desni;
} PROJEKCIJA;

void init_tree(PROJEKCIJA **);
void add_to_tree(PROJEKCIJA **, PROJEKCIJA *);
PROJEKCIJA *create_item(const char *, const char *, const char *, const char *, const double);
void print_tree(FILE *, PROJEKCIJA *);
void destroy_tree(PROJEKCIJA **);

FILE *otvori_datoteku(char *, char *);
void load_data(FILE *, PROJEKCIJA **);
void povoljne_projekcije(FILE *, PROJEKCIJA *, char *, char *);

int main(int argc, char **args)
{
    if(argc != 5)
    {
        printf("\nUsage: %s grad zanr in.txt out.txt\n\n", args[1]);
        exit(35);
    }
    PROJEKCIJA *koren;
    FILE *ulazna = otvori_datoteku(args[3], "r");
    FILE *izlazna = otvori_datoteku(args[4], "w");

    init_tree(&koren);
    load_data(ulazna, &koren);
    print_tree(izlazna, koren);
    povoljne_projekcije(izlazna, koren, args[1], args[2]);
    destroy_tree(&koren);

    fclose(ulazna);
    fclose(izlazna);

    return 0;
}

void init_tree(PROJEKCIJA **koren)
{
    *koren = NULL;
}

void add_to_tree(PROJEKCIJA **koren, PROJEKCIJA *novi)
{
   if(*koren == NULL) {
       *koren = novi;
       return;
   }
   else if(novi -> cena > (*koren) -> cena)
        add_to_tree(&(*koren) -> levi, novi);
   else
        add_to_tree(&(*koren) -> desni, novi);
}

PROJEKCIJA *create_item(const char *grad, const char *bioskop, const char *film, const char *zanr, const double cena)
{
    PROJEKCIJA *tmp = malloc(sizeof(PROJEKCIJA));
    if(tmp == NULL)
    {
        printf("\nNo memory for new item in tree!\n\n");
        exit(42);
    }
    strcpy(tmp -> grad, grad); 
    strcpy(tmp -> bioskop, bioskop);
    strcpy(tmp -> film, film);
    strcpy(tmp -> zanr, zanr);
    tmp -> cena = cena;
    tmp -> levi = NULL;
    tmp -> desni = NULL;

    return tmp;
}

void print_tree(FILE *out, PROJEKCIJA *koren)
{   
    if(koren == NULL)
        return;

    print_tree(out, koren -> desni);
    fprintf(out, "%2s %-10s %-8s %-9s %6.2lf\n", koren -> grad, koren -> bioskop, koren -> film, koren -> zanr, koren -> cena);
    print_tree(out, koren -> levi);
}

void destroy_tree(PROJEKCIJA **koren)
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

void load_data(FILE *in, PROJEKCIJA **koren)
{
    PROJEKCIJA *tmp = malloc(sizeof(PROJEKCIJA));
    while(fscanf(in, "%s %s %s %s %lf\n", tmp -> grad, tmp -> bioskop, tmp -> film, tmp -> zanr, &tmp -> cena) != EOF)
    {
        PROJEKCIJA *novi = create_item(tmp -> grad, tmp -> bioskop, tmp -> film, tmp -> zanr, tmp -> cena);
        add_to_tree(koren, novi);
    }
}

void povoljne_projekcije(FILE *out, PROJEKCIJA *g, char *grad, char *zanr)
{
    PROJEKCIJA *r = NULL;
    while(g != NULL) {
        if(strcmp(g -> grad, grad) == 0 && strcmp(g -> zanr, zanr) == 0) {
            if(r == NULL)
                r = g;
            if(g -> cena < r -> cena)
                r = g;
        }
        g = g -> desni;
    }

    if(r == NULL)
        fprintf(out, "\nNiko ne projektuje %s filmove u %s!", zanr, grad);
    else
        fprintf(out, "\nNajpovoljnija projekcija za %s filmove u %s je:\n%-9s %6.2lf\n", 
               zanr, grad, r -> film, r -> cena);
}
