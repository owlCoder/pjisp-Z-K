/* 
Napisati program koji iz zadate datoteke (licna_karta.txt) ucitava statitcki niz strukture licnost, koja sadrzi 
sledeca polja: ime, adresa, dan rodjenja, mesec rodjenja i godina rodjenja.
Prikazati osobe koje su u horoskopu vodolije tako sto ce formirati novi statitcki niz strukture vodolije i upisati
ga u zadatu izlaznu datoteku (npr. vodolije.txt).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAZIV 24 + 1
#define MAX_NIZ 100

struct licnost_st {
    char ime[MAX_NAZIV];
    char adresa[MAX_NAZIV];
    unsigned danR;
    unsigned mesecR;
    unsigned godinaR;
};

struct vodolije_st {
    char ime[MAX_NAZIV];
    char adresa[MAX_NAZIV];
    char horoskopski_znak[MAX_NAZIV];
};

FILE *safe_fopen(char *, char *);
unsigned load_data(FILE *, struct licnost_st *);
unsigned process_data(struct licnost_st *, struct vodolije_st *, const unsigned);
void write_data(FILE *, struct vodolije_st *, const unsigned);

int main(int argc, char **argm)
{
    if(argc != 3)
    {
		printf("\n\nUSAGE: %s IN_FILENAME OUT_FILENAME\n\n", argm[0]);
		exit(42);
    }
    unsigned i, j;

    FILE *in = safe_fopen(argm[1], "r");
    FILE *out = safe_fopen(argm[2], "w");

    struct licnost_st licnosti[MAX_NIZ];
    struct vodolije_st vodolije[MAX_NIZ];

    unsigned n = load_data(in, licnosti);
    j = process_data(licnosti, vodolije, n);
    write_data(out, vodolije, j);
    
    fclose(in);
    fclose(out);

    return 0;
}

FILE *safe_fopen(char *dat, char *rezim) {
    FILE *datoteka = fopen(dat, rezim);

    if(datoteka == NULL) {
        printf("\n\n\nFile %s doesn't exist!\n\n\n", dat);
        exit(42);
    }
    else
        return datoteka;
}

unsigned load_data(FILE *in, struct licnost_st *licnosti) {
    unsigned i = 0;

    while( fscanf(in, "%s %s %u %u %u", 
            licnosti[i].ime,
            licnosti[i].adresa,
           &licnosti[i].danR,
           &licnosti[i].mesecR,
           &licnosti[i].godinaR) != EOF ) { 
        i++; 
    }

    return i;
}

unsigned process_data(struct licnost_st *licnosti, struct vodolije_st *vodolije, const unsigned n) {
    unsigned i, j = 0;
    
    for(i = 0; i < n; i++) {
        if( (licnosti[i].mesecR == 1 && licnosti[i].danR >= 21)  ||
            (licnosti[i].mesecR == 2 && licnosti[i].danR <= 19) ) 
        {
            strcpy(vodolije[j].ime, licnosti[i].ime);
            strcpy(vodolije[j].adresa, licnosti[i].adresa);
            strcpy(vodolije[j].horoskopski_znak, "VODOLIJA");
            j++;
        }
    }
    return j;
}

void write_data(FILE *out, struct vodolije_st *vodolije, const unsigned n) {
    unsigned i; 

    for(i = 0; i < n; i++) { 
        fprintf(out, "%-10s %15s %10s\n", 
                vodolije[i].ime, 
                vodolije[i].adresa, 
                vodolije[i].horoskopski_znak);
    }
}
