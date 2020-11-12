#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NIZ 100

struct serija_st {
    char naziv[30 + 1];
    double IMDBOcena;
    double maxZabelGledanost;
    unsigned maxBrMeseciIzmedjuDveSezone;
};

struct hype_st {
    char naziv[30 + 1];
    double hypeFaktor;
};

FILE *otvoriDatoteku(char *, char *);
int ucitajPodatke(FILE *, struct serija_st[]);
void hypeCalc(int, struct serija_st[], struct hype_st[]);
void upisiIzvestaj(FILE *, int, struct hype_st[]);

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

        struct serija_st serije[MAX_NIZ];
        struct hype_st hype[MAX_NIZ];

        int i = ucitajPodatke(datoteka, serije);
        
        hypeCalc(i, serije, hype);
        upisiIzvestaj(upis, i, hype);

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

int ucitajPodatke(FILE *datoteka, struct serija_st serije[])
{
	int i = 0;
	rewind(datoteka);
    while( (fscanf(datoteka, "%s %lf %lf %u",
                serije[i].naziv,
               &serije[i].IMDBOcena,
               &serije[i].maxZabelGledanost,
               &serije[i].maxBrMeseciIzmedjuDveSezone)) != EOF) {
        i++;
    }
	return i;
}

void hypeCalc(int i, struct serija_st serije[], struct hype_st hype[])
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

void upisiIzvestaj(FILE *upis, int i, struct hype_st hype[])
{
	int j;
	for(j = 0; j < i; j++)
        fprintf(upis, "%6.2lf %s\n",
                hype[j].hypeFaktor,
                hype[j].naziv);
}