#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NIZ 100

struct pacijent_st {
    char ime[20 + 1];
    char prezime[20 + 1];
    int masa;
    double visinaM;
};

struct analiza_st {
    char ime[20 + 1];
    char prezime[20 + 1];
    double BMI;
    char *dijagnoza;
};

FILE *otvoriDatoteku(char *, char *);
int ucitajPodatke(FILE *, struct pacijent_st []);
void calcBMI(int, struct pacijent_st [], struct analiza_st []);
void upisiIzvestaj(FILE *, int, struct analiza_st []);

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

        struct pacijent_st pacijenti[MAX_NIZ];
        struct analiza_st analize[MAX_NIZ];

        int i = ucitajPodatke(datoteka, pacijenti);

        calcBMI(i, pacijenti, analize);
        upisiIzvestaj(upis, i, analize);

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

int ucitajPodatke(FILE *datoteka, struct pacijent_st pacijenti[])
{
	int i = 0;
	rewind(datoteka);
    while( (fscanf(datoteka, "%s %s %d %lf",
                pacijenti[i].ime,
                pacijenti[i].prezime,
               &pacijenti[i].masa,
               &pacijenti[i].visinaM)) != EOF) {
        i++;
    }
	return i;
}

void calcBMI(int i, struct pacijent_st pacijenti[], struct analiza_st analize[])
{
    int j;
	for(j = 0; j < i; j++)
	{
		strcpy(analize[j].ime,
			   pacijenti[j].ime);
		strcpy(analize[j].prezime,
			   pacijenti[j].prezime);

        analize[j].BMI = (pacijenti[j].masa / (pacijenti[j].visinaM * pacijenti[j].visinaM));

        if(analize[j].BMI < 18.5) {
            analize[j].dijagnoza = "Pothranjenost";
        }
        else if(analize[j].BMI >= 18.5 && analize[j].BMI < 25.0) {
            analize[j].dijagnoza = "Idealna tezina";
        }
        else if(analize[j].BMI >= 25.0 && analize[j].BMI < 30.0) {
            analize[j].dijagnoza = "Prekomerna tezina";
        }
        else if(analize[j].BMI >= 30.0) {
            analize[j].dijagnoza = "Gojaznost";
        }
        else
            analize[i].dijagnoza = "\nUneta tezina nije u opsegu prirodnih brojeva!\n";
	}
}

void upisiIzvestaj(FILE *upis, int i, struct analiza_st analize[])
{
	int j;
	for(j = 0; j < i; j++)
        fprintf(upis, "%s %s %.2lf %s\n",
                analize[j].ime,
                analize[j].prezime,
                analize[j].BMI,
                analize[j].dijagnoza);
}
