#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAMIRNICA  13 + 1
#define MAX_VRSTA      10 + 1

typedef struct namirnica_st {
    char naziv[MAX_NAMIRNICA];
    char vrsta[MAX_VRSTA];
    unsigned kolicina;
    struct namirnica_st *levi, *desni;
} NAMIRNICA;

void init_tree(NAMIRNICA **);
void add_to_tree(NAMIRNICA **, NAMIRNICA *);
NAMIRNICA *create_item(const char *, const unsigned, const char *);
void print_tree(FILE *, NAMIRNICA *);
void destroy_tree(NAMIRNICA **);

FILE *otvori_datoteku(char *, char *);
void load_data(FILE *, NAMIRNICA **);
void max_c_vitamin(FILE *, NAMIRNICA *);

int main(int argc, char **args)
{
    if(argc != 3)
    {
        printf("\nUsage: %s in.txt out.txt\n\n", args[1]);
        exit(35);
    }
    NAMIRNICA *koren;
    FILE *ulazna = otvori_datoteku(args[1], "r");
    FILE *izlazna = otvori_datoteku(args[2], "w");

    init_tree(&koren);
    load_data(ulazna, &koren);
    print_tree(izlazna, koren);
    max_c_vitamin(izlazna, koren);
    destroy_tree(&koren);

    fclose(ulazna);
    fclose(izlazna);

    return 0;
}

void init_tree(NAMIRNICA **koren)
{
    *koren = NULL;
}

void add_to_tree(NAMIRNICA **koren, NAMIRNICA *novi)
{
   if(*koren == NULL) {
       *koren = novi;
       return;
   }
   else if(novi -> kolicina < (*koren) -> kolicina)
        add_to_tree(&(*koren) -> levi, novi);
   else
        add_to_tree(&(*koren) -> desni, novi);
}

NAMIRNICA *create_item(const char *naziv, const unsigned kolicina, const char *vrsta)
{
    NAMIRNICA *tmp = malloc(sizeof(NAMIRNICA));
    if(tmp == NULL)
    {
        printf("\nNo memory for new item in tree!\n\n");
        exit(42);
    }
    strcpy(tmp -> naziv, naziv); 
    strcpy(tmp -> vrsta, vrsta);
    tmp -> kolicina = kolicina;
    tmp -> levi = NULL;
    tmp -> desni = NULL;

    return tmp;
}

void print_tree(FILE *out, NAMIRNICA *koren)
{   
    if(koren == NULL)
        return;

    print_tree(out, koren -> desni);
    fprintf(out, "%3u %-13s %s\n", koren -> kolicina, koren -> naziv, koren -> vrsta);
    print_tree(out, koren -> levi);
}

void destroy_tree(NAMIRNICA **koren)
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

void load_data(FILE *in, NAMIRNICA **koren)
{
    NAMIRNICA *tmp = malloc(sizeof(NAMIRNICA));
    while(fscanf(in, "%s %u %s", tmp -> naziv, &tmp -> kolicina, tmp -> vrsta) != EOF)
    {
        NAMIRNICA *novi = create_item(tmp -> naziv, tmp -> kolicina, tmp -> vrsta);
        add_to_tree(koren, novi);
    }
}

void max_c_vitamin(FILE *out, NAMIRNICA *g)
{
    NAMIRNICA *r = NULL;
    while(g != NULL) {
        if(r == NULL)
            r = g;
        if(g -> kolicina > r -> kolicina)
            r = g;
        g = g -> desni;
    }

    fprintf(out, "\nNamirnica sa najviše vitamina C je::\n%3u %-10s %s", 
            r -> kolicina, r -> naziv, r -> vrsta);
}
