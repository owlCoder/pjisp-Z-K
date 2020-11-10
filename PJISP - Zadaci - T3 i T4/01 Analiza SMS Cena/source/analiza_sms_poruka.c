#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_NIZ 100

struct paket_st {
    char nazivProvajdera[20 + 1];
    char nazivPaketa[20 + 1];
    unsigned int mesecnaPretplata;
    unsigned int brojBesplatnihSms;
    double cenaPoSmsBezBesplatnihSms;
};

struct cena_st {
    char nazivProvajdera[20];
    char nazivPaketa[20];
	double ukupnaCenaPaketa;
};

FILE *otvoriDatoteku(char *, char *);
int ucitajPodatkePaketa(FILE *, struct paket_st []);
void calcUkupnaCenaPaketa(int, int, struct paket_st [], struct cena_st []);
void upisiUkupneCene(FILE *, int, struct cena_st []);

int main(int argc, char **argm)
{
    if(argc != 4)
    { 
		printf("USAGE: %s MESECNO_PORUKA IN_FILENAME OUT_FILENAME\n", argm[0]);
		exit(42);       
    }
    else {
        struct paket_st paketi[MAX_NIZ];
        struct cena_st cene[MAX_NIZ];

	    FILE *datoteka = otvoriDatoteku(argm[2], "r");
	    FILE *upis = otvoriDatoteku(argm[3], "w");

	    int mesecno_poruka = atoi(argm[1]), i = ucitajPodatkePaketa(datoteka, paketi);

		calcUkupnaCenaPaketa(i, mesecno_poruka, paketi, cene);
		upisiUkupneCene(upis, i, cene);

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

int ucitajPodatkePaketa(FILE *datoteka, struct paket_st paketi[])
{
	int i = 0;
	rewind(datoteka);
    while( (fscanf(datoteka, "%s %s %d %d %lf",
                paketi[i].nazivProvajdera,
                paketi[i].nazivPaketa,
               &paketi[i].mesecnaPretplata,
               &paketi[i].brojBesplatnihSms,
               &paketi[i].cenaPoSmsBezBesplatnihSms)) != EOF) {
        i++;
    }
	return i;
}

void calcUkupnaCenaPaketa(int i, int mesecno_poruka, struct paket_st paketi[], struct cena_st cene[])
{
	int j, tmp = 0;
	for(j = 0; j < i; j++)
	{
		strcpy(cene[j].nazivProvajdera, 
			   paketi[j].nazivProvajdera);
		strcpy(cene[j].nazivPaketa, 
			   paketi[j].nazivPaketa);
		tmp = paketi[j].brojBesplatnihSms - mesecno_poruka;
		if(tmp < 0) {
			cene[j].ukupnaCenaPaketa = ( 
				abs(tmp) * paketi[j].cenaPoSmsBezBesplatnihSms 
					     + paketi[j].mesecnaPretplata);
		} 
		else {
			cene[j].ukupnaCenaPaketa =  paketi[j].mesecnaPretplata;
		}
	}
}

void upisiUkupneCene(FILE *upis, int i, struct cena_st cene[])
{
	int j;
	for(j = 0; j < i; j++)
        fprintf(upis, "%7.2lf %10s\t%10s\n",
                cene[j].ukupnaCenaPaketa,
                cene[j].nazivProvajdera,
                cene[j].nazivPaketa);
}