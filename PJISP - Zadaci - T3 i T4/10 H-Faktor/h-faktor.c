#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NIZ 100

struct serija_st {
    char naziv[30 + 1];
    double IMDBOcena;
    double maxZabelGledanost;
    unsigned maxBrMeseciIzmedjuDveSezone;
} serije[MAX_NIZ];

struct hype_st {
    char naziv[30 + 1];
    double hypeFaktor;
} hype[MAX_NIZ];

FILE *otvoriDatoteku(char *, char *);
int ucitajPodatke(FILE *);
void hypeCalc(int);
void upisiIzvestaj(FILE *, int);

int main(int argc, char **argm)
{
    if(argc != 3)
    {
		printf("USAGE: %s IN_FILENAME OUT_FILENAME\n", argm[0]);
		exit(42);
    }
    else {

        FILE *datoteka = otvoriDatoteku(argm[1], "r");
        FILE *upis = otvoriDatoteku(argm[2], "w");

        int i = ucitajPodatke(datoteka);
        
        hypeCalc(i);
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
    while( (fscanf(datoteka, "%s %lf %lf %d",
               &serije[i].naziv,
               &serije[i].IMDBOcena,
               &serije[i].maxZabelGledanost,
               &serije[i].maxBrMeseciIzmedjuDveSezone)) != EOF) {
        i++;
    }
	return i;
}

void hypeCalc(int i)
{
    int j;
	for(j = 0; j < i; j++)
	{
		strcpy(hype[j].naziv,
			   serije[j].naziv);

        hype[j].hypeFaktor = serije[j].IMDBOcena * 
                serije[j].maxBrMeseciIzmedjuDveSezone / serije[j].maxZabelGledanost;
    }
}

void upisiIzvestaj(FILE *upis, int i)
{
	int j;
	for(j = 0; j < i; j++)
        fprintf(upis, "%6.2lf %s\n",
                hype[j].hypeFaktor,
                hype[j].naziv);
}