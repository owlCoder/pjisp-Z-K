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
    if(argc != 3) // broj argumenata zavisi od postavke zadatka
    {
		printf("USAGE: %s IN_FILENAME OUT_FILENAME\n", argm[0]);
		exit(42);
    }
    else {
        FILE *datoteka = otvoriDatoteku(argm[1], "r"); // od broja paremetra zavisi na kom indeksu je datoteka za citanje
        FILE *upis = otvoriDatoteku(argm[2], "w"); // od broja paremetra zavisi na kom indeksu je datoteka za pisanje

        int i = ucitajPodatke(datoteka);
        
        obrada(i);                                  // od zadatka zavisi da li se prosledjuje jos neki parametar
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
    while( /* (fscanf(datoteka, "%tip1 %tip2 ....",
               &strukturaX[i].par1,
               &strukturaX[i].par2,
               &strukturaX[i].par3,
               .....               )) != EOF) { */
        i++;
    }
	return i;
}

void obrada(int i, ...)
{
    int j;
	for(j = 0; j < i; j++)
	{
		// deo koda za prolaz kroz podatke upisane u strukturu iz datoteke
    }
}

void upisiIzvestaj(FILE *upis, int i)
{
	int j;
	for(j = 0; j < i; j++)
        /* fprintf(upis, "%tip1 %tip2 ....\n",
                struktura[j].parametar1,
                ....                    );
}