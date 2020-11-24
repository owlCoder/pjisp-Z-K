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

struct horoskop_st {
    char ime[MAX_NAZIV];
    char adresa[MAX_NAZIV];
    char horoskopski_znak[MAX_NAZIV];
};

FILE *safe_fopen(char *, char *);
unsigned load_data(FILE *, struct licnost_st *);
unsigned process_data(struct licnost_st *, struct horoskop_st *, char *, unsigned, const unsigned);
unsigned hor_znak(const unsigned, const unsigned);
void write_data(FILE *, struct horoskop_st *, const unsigned);
unsigned hor_znak_toInt(char *);

int main(int argc, char **argm)
{
    if(argc != 3)
    {
		printf("\n\nUSAGE: %s IN_FILENAME TRAZENI_HOROSKOPSKI_ZNAK\n\n", argm[0]);
		exit(42);
    }
    unsigned i, j;
    char *trazeniZnak = argm[2];

    for(i = 0; trazeniZnak[i]; i++) 
        trazeniZnak[i] = tolower(trazeniZnak[i]); // sve u mala slova

    char tmp[15]; strcpy(tmp, trazeniZnak);

    FILE *in = safe_fopen(argm[1], "r");
    FILE *out = safe_fopen(strcat(argm[2], ".txt"), "w");
   
    unsigned konvertovano = hor_znak_toInt(tmp);

    struct licnost_st licnosti[MAX_NIZ];
    struct horoskop_st horoskopi[MAX_NIZ];

    unsigned n = load_data(in, licnosti);
    j = process_data(licnosti, horoskopi, tmp, konvertovano, n);
    write_data(out, horoskopi, j);
    
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

unsigned process_data(struct licnost_st *licnosti, struct horoskop_st *horoskopi, char *tmp, unsigned uneto, const unsigned n) {
    unsigned i, j = 0;
    
    for(i = 0; i < n; i++) {
        unsigned konvertovano = hor_znak(licnosti[i].danR, licnosti[i].mesecR);
        if(konvertovano == uneto) {
            strcpy(horoskopi[j].ime, licnosti[i].ime);
            strcpy(horoskopi[j].adresa, licnosti[i].adresa);
            strcpy(horoskopi[j].horoskopski_znak, tmp);
            j++;
        }
    }
    return j;
}

unsigned hor_znak(const unsigned danR, const unsigned mesecR) 
{
    if( (mesecR == 3   && danR >= 21)  || (mesecR == 4   && danR <= 20) ) return 1; // strcpy(znak, "ovan");     // 21.3  -> 20.4
    if( (mesecR == 4   && danR >= 21)  || (mesecR == 5   && danR <= 21) ) return 2; // strcpy(znak, "bik");      // 21.4  -> 21.5
    if( (mesecR == 5   && danR >= 22)  || (mesecR == 6   && danR <= 21) ) return 3; // strcpy(znak, "blizanci"); // 22.5  -> 21.6
    if( (mesecR == 6   && danR >= 22)  || (mesecR == 7   && danR <= 22) ) return 4; // strcpy(znak, "rak");      // 22.6  -> 22.7
    if( (mesecR == 7   && danR >= 23)  || (mesecR == 8   && danR <= 22) ) return 5; // strcpy(znak, "lav");      // 23.7  -> 22.8
    if( (mesecR == 8   && danR >= 23)  || (mesecR == 9   && danR <= 22) ) return 6; // strcpy(znak, "devica");   // 23.8  -> 22.9
    if( (mesecR == 9   && danR >= 23)  || (mesecR == 10  && danR <= 23) ) return 7; // strcpy(znak, "vaga");     // 23.9  -> 23.10
    if( (mesecR == 10  && danR >= 24)  || (mesecR == 11  && danR <= 22) ) return 8; // strcpy(znak, "skorpija"); // 24.10 -> 22.11
    if( (mesecR == 11  && danR >= 23)  || (mesecR == 12  && danR <= 21) ) return 9; // strcpy(znak, "strelac");  // 23.11 -> 21.12
    if( (mesecR == 12  && danR >= 22)  || (mesecR == 1   && danR <= 20) ) return 10; // strcpy(znak, "jarac");    // 22.12 -> 20.1
    if( (mesecR == 1   && danR >= 21)  || (mesecR == 2   && danR <= 19) ) return 11; // strcpy(znak, "vodolija"); // 21.1  -> 19.2
    if( (mesecR == 2   && danR >= 20)  || (mesecR == 3   && danR <= 20) ) return 12; // strcpy(znak, "ribe");     // 20.2  -> 20.3
}

unsigned hor_znak_toInt(char *str) 
{
    if(strcmp(str, "ovan") == 0)        return 1;
    if(strcmp(str, "bik") == 0)         return 2;
    if(strcmp(str, "blizanci") == 0)    return 3;
    if(strcmp(str, "rak") == 0)         return 4;
    if(strcmp(str, "lav") == 0)         return 5;
    if(strcmp(str, "devica") == 0)      return 6;
    if(strcmp(str, "vaga") == 0)        return 7;
    if(strcmp(str, "skorpija") == 0)    return 8;
    if(strcmp(str, "strelac") == 0)     return 9;
    if(strcmp(str, "jarac") == 0)       return 10;
    if(strcmp(str, "vodolija") == 0)    return 11;
    if(strcmp(str, "ribe") == 0)        return 12;  
}

void write_data(FILE *out, struct horoskop_st *horoskopi, const unsigned n) {
    unsigned i; 

    for(i = 0; i < n; i++) { 
        fprintf(out, "%-10s %15s %10s\n", 
                horoskopi[i].ime, 
                horoskopi[i].adresa, 
                horoskopi[i].horoskopski_znak);
    }
}
