#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NIZ 100

struct takmicar_st {
    char ime[16 + 1];
    char prezime[16 + 1];
    unsigned ocena1, ocena2, ocena3;
} takmicari[MAX_NIZ];

struct ocena_st {
    char ime[16 + 1];
    char prezime[16 + 1];
    double avgOcena;
} ocene[MAX_NIZ];

FILE *otvoriDatoteku(char *, char *);
int ucitajPodatke(FILE *);
void average(int);
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
        
        average(i);
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
    while( (fscanf(datoteka, "%s %s %u %u %u",
               &takmicari[i].ime,
               &takmicari[i].prezime,
               &takmicari[i].ocena1,
               &takmicari[i].ocena2,
               &takmicari[i].ocena3)) != EOF) {
        i++;
    }
	return i;
}

void average(int i)
{
    int j;
	for(j = 0; j < i; j++)
	{
		strcpy(ocene[j].ime,
			   takmicari[j].ime);

        strcpy(ocene[j].prezime,
			   takmicari[j].prezime);

        ocene[j].avgOcena =
            (takmicari[j].ocena1 + takmicari[j].ocena2
            + takmicari[j].ocena3) / 3.0;
    }
}

void upisiIzvestaj(FILE *upis, int i)
{
	int j;
	for(j = 0; j < i; j++)
        fprintf(upis, "%4.2lf %s %s\n",
                ocene[j].avgOcena,
                ocene[j].ime,
                ocene[j].prezime);
}