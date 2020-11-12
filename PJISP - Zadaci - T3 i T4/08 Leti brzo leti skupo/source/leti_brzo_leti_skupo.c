#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NIZ 100

struct prevoznik_st {
    char nazivOperatera[20 + 1];
    double cenaKarte;
    double maxMasaFreePrtljaga;
    double cenaVanMaxMase;
};

struct cena_st {
    double ukupnaCenaLeta;
    char nazivOperatera[20 + 1];
};

FILE *otvoriDatoteku(char *, char *);
int ucitajPodatke(FILE *, struct prevoznik_st[]);
void ukupnaCena(int, double, struct prevoznik_st[], struct cena_st[]);
void upisiIzvestaj(FILE *, int, struct cena_st[]);

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

        struct prevoznik_st prevoznici[MAX_NIZ];
        struct cena_st cene[MAX_NIZ];

        int i = ucitajPodatke(datoteka, prevoznici);
        double masa = atof(argm[1]);

        ukupnaCena(i, masa, prevoznici, cene);
        upisiIzvestaj(upis, i, cene);

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

int ucitajPodatke(FILE *datoteka, struct prevoznik_st prevoznici[])
{
	int i = 0;
	rewind(datoteka);
    while( (fscanf(datoteka, "%s %lf %lf %lf",
                prevoznici[i].nazivOperatera,
               &prevoznici[i].cenaKarte,
               &prevoznici[i].maxMasaFreePrtljaga,
               &prevoznici[i].cenaVanMaxMase)) != EOF) {
        i++;
    }
	return i;
}

void ukupnaCena(int i, double masa, struct prevoznik_st prevoznici[], struct cena_st cene[])
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

void upisiIzvestaj(FILE *upis, int i, struct cena_st cene[])
{
	int j;
	for(j = 0; j < i; j++)
        fprintf(upis, "%7.2lf %s\n",
                cene[j].ukupnaCenaLeta,
                cene[j].nazivOperatera);
}
