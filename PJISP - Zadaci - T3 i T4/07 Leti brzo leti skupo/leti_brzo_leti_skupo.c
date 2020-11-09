/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NIZ 100

struct prevoznik_st {
    char nazivOperatera[20 + 1];
    double cenaKarte;
    double maxMasaFreePrtljaga;
    double cenaVanMaxMase;
} prevoznici[MAX_NIZ];

struct cena_st {
    double ukupnaCenaLeta;
    char nazivOperatera[20 + 1];
} cene[MAX_NIZ];

FILE *otvoriDatoteku(char *, char *);
int ucitajPodatke(FILE *);
void ukupnaCena(int, double);
void upisiIzvestaj(FILE *, int);

int main(int argc, char **argm)
{
    if(argc != 4)
    {
		printf("USAGE: %s masa IN_FILENAME OUT_FILENAME\n", argm[0]);
		exit(42);
    }
    else {

        FILE *datoteka = otvoriDatoteku(argm[2], "r");
        FILE *upis = otvoriDatoteku(argm[3], "w");

        int i = ucitajPodatke(datoteka);
        double masa = atof(argm[1]);

        ukupnaCena(i, masa);
        upisiIzvestaj(upis, i);

        fclose(datoteka);
        fclose(upis);

        return 0;
    }
}

FILE *otvoriDatoteku(char *naziv, char *rezim) {
    FILE *datoteka;

    datoteka = fopen(naziv, rezim);

    if(datoteka == NULL) {
        printf("Nije moguce otvoriti datoteku -> \"%s\"\n", naziv);
        exit(0xda7);
    }
    else
        return datoteka;
}

int ucitajPodatke(FILE *datoteka)
{
	int i = 0;
	rewind(datoteka);
    while( (fscanf(datoteka, "%s %lf %lf %lf",
               &prevoznici[i].nazivOperatera,
               &prevoznici[i].cenaKarte,
               &prevoznici[i].maxMasaFreePrtljaga,
               &prevoznici[i].cenaVanMaxMase)) != EOF) {
        i++;
    }
	return i;
}

void ukupnaCena(int i, double masa)
{
    int j;
	for(j = 0; j < i; j++)
	{
		strcpy(cene[j].nazivOperatera,
			   prevoznici[j].nazivOperatera);

		double tmpMasa = prevoznici[j].maxMasaFreePrtljaga - masa;
		double masaVanPaketa;

        if(tmpMasa < 0) { // masa van paketa free mase
            masaVanPaketa = (tmpMasa * (-1.0)) * prevoznici[j].cenaVanMaxMase;
            cene[j].ukupnaCenaLeta = prevoznici[j].cenaKarte + masaVanPaketa;
        }
        else
            cene[j].ukupnaCenaLeta = prevoznici[j].cenaKarte + masaVanPaketa;
	}
}

void upisiIzvestaj(FILE *upis, int i)
{
	int j;
	for(j = 0; j < i; j++)
        fprintf(upis, "%7.2lf %s\n",
                cene[j].ukupnaCenaLeta,
                cene[j].nazivOperatera);
}
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAZIV 20+1
#define MAX_NIZ 30

struct prevoznik_st {
    char operater[MAX_NAZIV];
    double cena_karte;
    double max_masa_besplatnog_prtljaga;
    double cena_po_kg;
};

struct cena_st {
    double ukupna_cena;
    char operater[MAX_NAZIV];
};


FILE *safe_fopen(char filename[], char mode[], int error_code);
void ucitaj_prevoznike(FILE *in, struct prevoznik_st prevoznici[], int *n);
double odredi_ukupnu_cenu(struct prevoznik_st prevoznik, double masa);
void transform(struct prevoznik_st prevoznici[], struct cena_st cene[], int n,
double masa);
void snimi_cene(FILE *out, struct cena_st cene[], int n);


int main(int arg_num, char **args) {
    if (arg_num != 4) {
        printf("USAGE: %s MASA IN_FILENAME OUT_FILENAME\n", args[0]);
        exit(42);
    }

    double masa = atof(args[1]);
    char *in_filename = args[2];
    char *out_filename = args[3];

    FILE *in  = safe_fopen(in_filename,  "r", 1);
    FILE *out = safe_fopen(out_filename, "w", 2);

    struct prevoznik_st prevoznici[MAX_NIZ];
    struct cena_st cene[MAX_NIZ];
    int n;

    ucitaj_prevoznike(in, prevoznici, &n);
    transform(prevoznici, cene, n, masa);
    snimi_cene(out, cene, n);

    fclose(in);
    fclose(out);

    return 0;
}

FILE *safe_fopen(char filename[], char mode[], int error_code) {
    FILE *fp = fopen(filename, mode);
    if(fp == NULL) {
        printf("Can't open '%s'!\n", filename);
        exit(error_code);
    }
    return fp;
}

void ucitaj_prevoznike(FILE *in, struct prevoznik_st prevoznici[], int *n) {
    *n = 0;
    while(fscanf(
        in, "%s %lf %lf %lf",
         prevoznici[*n].operater,
        &prevoznici[*n].cena_karte,
        &prevoznici[*n].max_masa_besplatnog_prtljaga,
        &prevoznici[*n].cena_po_kg
    ) != EOF) {
        (*n)++;
    }
}

double odredi_ukupnu_cenu(struct prevoznik_st prevoznik, double masa) {
    double base = prevoznik.cena_karte;

    double extra_masa = masa - prevoznik.max_masa_besplatnog_prtljaga;
    if (extra_masa > 0) {
        base += extra_masa * prevoznik.cena_po_kg;
    }

    return base;
}

void transform(struct prevoznik_st prevoznici[], struct cena_st cene[], int n,
double masa) {
    int i;
    for(i=0; i<n; i++) {
        strcpy(cene[i].operater, prevoznici[i].operater);

        cene[i].ukupna_cena = odredi_ukupnu_cenu(prevoznici[i], masa);
    }
}

void snimi_cene(FILE *out, struct cena_st cene[], int n) {
    int i;
    for(i=0; i<n; i++) {
        fprintf(
            out, "%7.2f %s\n",
            cene[i].ukupna_cena,
            cene[i].operater
        );
    }
}