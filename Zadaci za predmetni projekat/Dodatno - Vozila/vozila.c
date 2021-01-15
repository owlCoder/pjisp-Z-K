#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MARKA   10 + 1
#define MAX_OZNAKA   7 + 1
#define MAX_VRSTA    8 + 1
#define PROC_115     1.15
#define PROC_110     1.10

typedef struct vozilo_st {
    char registracija[MAX_OZNAKA], 
         marka[MAX_MARKA],
         vrsta[MAX_VRSTA];
    double nosivost, cena;
    unsigned godiste;
    struct vozilo_st *sledeci;
} VOZILA;

void init_list(VOZILA **);
void add_to_list(VOZILA **, VOZILA *);
VOZILA *create_item(const char *, const char *, const char *, const double, const unsigned, const double);
void destroy_list(VOZILA **);

FILE *otvori_datoteku(char *, char *, int);
void load_data(FILE *, VOZILA **);

void pod_a(FILE *, VOZILA *, char *, int);
void pod_b_1(FILE *, VOZILA *, char *, int);
void pod_b_2(FILE *, VOZILA *, char *, int);
void pod_b_3(FILE *, VOZILA *, char *, int, double);

int main(int argc, char **args)
{
    if(argc != 7)
    {
        printf("\n./zad 2011 teretno vozila.txt ceneVozila.txt 950 filtriranaVozila.txt\n\n");
        exit(3);
    }
    if(strcmp(args[2], "teretno") != 0 && strcmp(args[2], "putnicko") != 0) {
        printf("\nPozvali ste program sa nepoznatom vrednoscu parametra vrstaVozila!\n");
        exit(5);
    }
    VOZILA *glava;
    FILE *ulazna_1 = otvori_datoteku(args[3], "r", 1);
    FILE *izlazna_1 = otvori_datoteku(args[4], "w", 2);
    FILE *izlazna_2 = otvori_datoteku(args[6], "w", 2);

    init_list(&glava);
    load_data(ulazna_1, &glava);
    pod_a(izlazna_1, glava, args[2], atoi(args[1]));
    pod_b_1(izlazna_2, glava, args[2], atoi(args[1]));
    pod_b_2(izlazna_2, glava, args[2], atoi(args[1]));
    pod_b_3(izlazna_2, glava, args[2], atoi(args[1]), atof(args[5]));
    destroy_list(&glava);

    fclose(ulazna_1);
    fclose(izlazna_1);
    fclose(izlazna_2);

    return 0;
}

void init_list(VOZILA **glava)
{
    *glava = NULL;
}

void add_to_list(VOZILA **glava, VOZILA *novi)
{
   if(*glava == NULL) {
       *glava = novi;
       return;
   }
   add_to_list(&(*glava) -> sledeci, novi);
}

VOZILA *create_item(const char *r, const char *m, const char *v, 
                    const double n, const unsigned godiste, 
                    const double cena)
{
    VOZILA *tmp = malloc(sizeof(VOZILA));
    if(tmp == NULL)
    {
        printf("\nNo memory for new item in list!\n\n");
        exit(4);
    }
    strcpy(tmp -> registracija, r); 
    strcpy(tmp -> marka, m);
    strcpy(tmp -> vrsta, v);
    tmp -> nosivost = n;
    tmp -> godiste = godiste;
    tmp -> cena = cena;
    tmp -> sledeci = NULL;

    return tmp;
}

void destroy_list(VOZILA **glava)
{
    if(*glava != NULL)
    {
        destroy_list(&((*glava) -> sledeci));
        free(*glava);
        *glava = NULL;
    }
}

FILE *otvori_datoteku(char *name, char *mode, int ec)
{
    FILE *f = fopen(name, mode);
    if(f == NULL)
    {
        printf("\nFile %s doesn't exist!\n\n", name);
        exit(ec);
    }
    return f;
}

void load_data(FILE *in, VOZILA **glava)
{
    VOZILA *tmp = malloc(sizeof(VOZILA));
    while(fscanf(in, "%s %s %s %lf %u %lf", tmp -> registracija, 
          tmp -> marka, tmp -> vrsta, &tmp -> nosivost, &tmp -> godiste,
          &tmp -> cena) != EOF)
    {
        VOZILA *novi = create_item(tmp -> registracija, 
                       tmp -> marka,   tmp -> vrsta, tmp -> nosivost, 
                       tmp -> godiste, tmp -> cena);
        add_to_list(glava, novi);
    }
}

void pod_a(FILE *out, VOZILA *g, char *vrsta, int godiste)
{
    while(g != NULL) {
        double cenaNova = g -> cena;

        if(g -> godiste > godiste)
             cenaNova *= PROC_115;
        if(strcmp(g -> vrsta, vrsta) == 0)
             cenaNova *= PROC_110;

        fprintf(out, "%-10s %u %-8s %.2lf %-8s\n", g -> marka, g -> godiste, g -> vrsta, cenaNova, g -> registracija);
        g = g -> sledeci;
    }
}

void pod_b_1(FILE *out, VOZILA *g, char *vrsta, int godiste)
{
    /* registarsku oznaku vozila koje je prosleđenog godišta a čija je cena najmanja
     (ako takvo vozilo ne postoji, u izlaznu datoteku ispisati sledeću poruku: 
     Ne postoji vozilo čije je godište jednako prosleđenom!)
    */
    VOZILA *v = NULL, *t = g;
    unsigned br = 0;
    while(t != NULL) {
        if( (t -> godiste == godiste) && (strcmp(t -> vrsta, vrsta) == 0) ) {
            v = t;
            br++;
        }
        if(br > 1)
            if(t -> cena < v -> cena)
                v = t;
        t = t -> sledeci;
    }
    if(v == NULL)
        fprintf(out, "Ne postoji vozilo čije je godište jednako prosleđenom!\n");
    else
        fprintf(out, "Vozilo čija je cena najmanja a prosleđenog je godišta (%u) je %s.\n", godiste, v -> registracija);
}

void pod_b_2(FILE *out, VOZILA *g, char *vrsta, int godiste)
{
    /* koliko je ukupno vozila čije registarske oznake sadrže „NS“ a koja su prosleđene vrste 
       (ako takva vozila ne postoje, u izlaznu datoteku ispisati sledeću poruku: Ne postoje vozila 
       čije registarske oznake sadrze NS!)
    */
    VOZILA *v = NULL, *t = g;
    unsigned br = 0;
    char reg[10];
    while(t != NULL) {
        strcpy(reg, t -> registracija);
        if(strcmp(t -> vrsta, vrsta) == 0) 
            if(reg[0] == 'N' && reg[1] == 'S')
                br++;

        t = t -> sledeci;
    }
    if(br == 0)
        fprintf(out, "Ne postoje vozila čije registarske oznake sadrže NS!\n");
    else
        fprintf(out, "Postoje %u vozila čija je vrsta %s, a čije registarske oznake sadrže %s.\n", br, vrsta, "NS");
}

void pod_b_3(FILE *out, VOZILA *g, char *vrsta, int godiste, double nosivost)
{
    /* broj vozila čija je nosivost veća od prosleđene a pripadaju prosleđenoj vrsti 
       (parametar trazenaNosivost predstavlja referentnu vrednost u odnosu na koju 
       se vrši filtriranje vozila).
    */
    VOZILA *v = NULL, *t = g;
    unsigned br = 0;
    char reg[10];
    while(t != NULL) {
        strcpy(reg, t -> registracija);
        if(strcmp(t -> vrsta, vrsta) == 0) 
            if(t -> nosivost > nosivost)
                br++;

        t = t -> sledeci;
    }
    if(br == 0)
        fprintf(out, "Ne postoje vozila po zadatom kriterijumu!\n");
    else
        fprintf(out, "Ukupno su na raspolaganju %u %s vozila čija je nosivost veća od %2.0lf.", br, vrsta, nosivost);

}
