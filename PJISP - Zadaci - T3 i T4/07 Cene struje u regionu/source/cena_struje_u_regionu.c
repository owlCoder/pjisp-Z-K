#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NIZ 100

struct paket_st {
    char nazivZemlje[20 + 1];
    char nazivOperatera[20 + 1];
    unsigned mesecnaPretplata;
    unsigned brojKWhUkljUPaketu;
    double cenaKWhVanPaketa;
} paketi[MAX_NIZ];

struct cena_st {
    double ukupnaCena;
    char nazivZemlje[20 + 1];
    char nazivOperatora[20 + 1];
} cene[MAX_NIZ];

FILE *otvoriDatoteku(char *, char *);
int ucitajPodatke(FILE *);
void ukupnaCena(int, int);
void upisiIzvestaj(FILE *, int);

int main(int argc, char **argm)
{
    if(argc != 4)
    {
		printf("USAGE: %s potrosenoKWh IN_FILENAME OUT_FILENAME\n", argm[0]);
		exit(42);
    }
    else {

        FILE *datoteka = otvoriDatoteku(argm[2], "r");
        FILE *upis = otvoriDatoteku(argm[3], "w");

        int i = ucitajPodatke(datoteka);
        int potrosenoKWh = atoi(argm[1]);

        ukupnaCena(i, potrosenoKWh);
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
    while( (fscanf(datoteka, "%s %s %d %d %lf",
               &paketi[i].nazivZemlje,
               &paketi[i].nazivOperatera,
               &paketi[i].mesecnaPretplata,
               &paketi[i].brojKWhUkljUPaketu,
               &paketi[i].cenaKWhVanPaketa)) != EOF) {
        i++;
    }
	return i;
}

void ukupnaCena(int i, int potrosenoKWh)
{
    int j;
	for(j = 0; j < i; j++)
	{
		strcpy(cene[j].nazivZemlje,
			   paketi[j].nazivZemlje);

		strcpy(cene[j].nazivOperatora,
			   paketi[j].nazivOperatera);

		int tmpKWh = paketi[j].brojKWhUkljUPaketu - potrosenoKWh;
		double KWhVanPak;

        if(tmpKWh < 0) { // potroseno kwh van paketa
            KWhVanPak = (tmpKWh * (-1)) * paketi[j].cenaKWhVanPaketa;
            cene[j].ukupnaCena = paketi[j].mesecnaPretplata + KWhVanPak;
        }
        else
            cene[j].ukupnaCena = paketi[j].mesecnaPretplata;
	}
}

void upisiIzvestaj(FILE *upis, int i)
{
	int j;
	for(j = 0; j < i; j++)
        fprintf(upis, "%7.2lf %s %s\n",
                cene[j].ukupnaCena,
                cene[j].nazivZemlje,
                cene[j].nazivOperatora);
}
