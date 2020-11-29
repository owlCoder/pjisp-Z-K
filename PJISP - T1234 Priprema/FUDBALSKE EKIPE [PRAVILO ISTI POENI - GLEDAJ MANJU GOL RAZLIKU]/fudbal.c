#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAZIV 20 + 1
#define MAX_NIZ 15

struct ekipa_st {
    char imeEkipe[MAX_NAZIV];
    unsigned brojBodova;
    int golRazlika;
};

FILE *otvori_fajl(char *, char *);
unsigned ucitaj_podatke(FILE *, struct ekipa_st *);
void ekipa_max_bodova(struct ekipa_st *, const unsigned);
void sortiraj_ekipe(struct ekipa_st *, const unsigned);
void swap(struct ekipa_st *, const unsigned, const unsigned);
void upis_podataka(FILE *, struct ekipa_st *, const unsigned);
unsigned u_abs(int);
void isti_broj_bodova(struct ekipa_st *, const unsigned, const unsigned);
void resort_criteria(struct ekipa_st *, const unsigned);

int main(int argc, char **argm)
{
    if(argc != 3) {
        printf("\nUSAGE: %s IN_FILENAME OUT_FILENAME\n\nError 0xBAD_PROGRAM_CALL..... Exiting\n\n", argm[0]);
        exit(0xBADCA11);
    }

    FILE *in = otvori_fajl(argm[1], "r");
    FILE *out = otvori_fajl(argm[2], "w");

    struct ekipa_st ekipe[MAX_NIZ];
    
    unsigned n = ucitaj_podatke(in, ekipe);
    sortiraj_ekipe(ekipe, n);
    resort_criteria(ekipe, n);
    ekipa_max_bodova(ekipe, n);
    upis_podataka(out, ekipe, n);

    fclose(in);
    fclose(out);

    return 0;
}

FILE *otvori_fajl(char *naziv, char *rezim)
{
    FILE *f = fopen(naziv, rezim);

    if(f == NULL)
    {
        printf("\nFile %s doesn't exist!", naziv);
        exit(50);
    }
    return f;
}

unsigned ucitaj_podatke(FILE *dat, struct ekipa_st *ekipe)
{
    unsigned i = 0;

    while( fscanf(dat, "%s %u %i",
                         ekipe[i].imeEkipe,
                        &ekipe[i].brojBodova,
                        &ekipe[i].golRazlika) != EOF)
    {
        i++;
    }
    return i;
}

void ekipa_max_bodova(struct ekipa_st *ekipe, const unsigned n)
{
    unsigned i, maxIndex = 0;

    char ek[MAX_NAZIV] = "";
    strcat(ek, ekipe[maxIndex].imeEkipe);
    strcat(ek, ".txt");

    FILE *out = otvori_fajl(ek, "w");
    fprintf(out, "%s %u %d\n", ekipe[maxIndex].imeEkipe, ekipe[maxIndex].brojBodova, ekipe[maxIndex].golRazlika);

    fclose(out);
}

void sortiraj_ekipe(struct ekipa_st *ekipe, const unsigned n)
{
    unsigned i, j;
    for(i = 0; i < n - 1; i++)
        for(j = i + 1; j < n; j++)
            if(ekipe[i].brojBodova < ekipe[j].brojBodova)
                swap(ekipe, i, j);
}

void resort_criteria(struct ekipa_st *ekipe, const unsigned n)
{
    unsigned i;
    for(i = 0; i < n - 1; i++)
        if(ekipe[i].brojBodova == ekipe[i + 1].brojBodova)
            isti_broj_bodova(ekipe, i, i + 1);
}

void swap(struct ekipa_st *ekipe, const unsigned i, const unsigned j)
{
    struct ekipa_st tmp;

    strcpy(tmp.imeEkipe, ekipe[i].imeEkipe);
    tmp.brojBodova = ekipe[i].brojBodova;
    tmp.golRazlika = ekipe[i].golRazlika; 

    strcpy(ekipe[i].imeEkipe, ekipe[j].imeEkipe);
    ekipe[i].brojBodova =  ekipe[j].brojBodova;
    ekipe[i].golRazlika = ekipe[j].golRazlika; 

    strcpy(ekipe[j].imeEkipe, tmp.imeEkipe);
    ekipe[j].brojBodova = tmp.brojBodova;
    ekipe[j].golRazlika = tmp.golRazlika; 
}

void isti_broj_bodova(struct ekipa_st *ekipe, const unsigned i, const unsigned j)
{
    if( u_abs(ekipe[i].golRazlika) < u_abs(ekipe[j].brojBodova) )
        swap(ekipe, i, j);
}

void upis_podataka(FILE *out, struct ekipa_st *ekipe, const unsigned n)
{
    unsigned i;
    for(i = 0; i < n; i++)
        fprintf(out, "%-10s %5u %5d\n", ekipe[i].imeEkipe, ekipe[i].brojBodova, ekipe[i].golRazlika);
}

unsigned u_abs(int broj) { return broj < 0 ? -broj : broj; }