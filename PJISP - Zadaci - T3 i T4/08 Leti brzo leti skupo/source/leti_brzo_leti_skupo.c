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
