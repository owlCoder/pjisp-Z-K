#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NIZ 100

struct pacijent_st {
    char ime[20 + 1];
    char prezime[20 + 1];
    int masa;
    double visinaM;
} pacijenti[MAX_NIZ];

struct analiza_st {
    char ime[20 + 1];
    char prezime[20 + 1];
    double BMI;
    char *dijagnoza;
} analize[MAX_NIZ];

FILE *otvoriDatoteku(char *, char *);
int ucitajPodatke(FILE *);
void calcBMI(int);
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

        calcBMI(i);
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
    while( (fscanf(datoteka, "%s %s %d %lf",
               &pacijenti[i].ime,
               &pacijenti[i].prezime,
               &pacijenti[i].masa,
               &pacijenti[i].visinaM)) != EOF) {
        i++;
    }
	return i;
}

void calcBMI(int i)
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
            analize[j].dijagnoza = "Idealna težina";
        }
        else if(analize[j].BMI >= 25.0 && analize[j].BMI < 30.0) {
            analize[j].dijagnoza = "Prekomerna težina";
        }
        else if(analize[j].BMI >= 30.0) {
            analize[j].dijagnoza = "Gojaznost";
        }
        else
            analize[i].dijagnoza = "\nUneta težina nije u opsegu prirodnih brojeva!\n";
	}
}

void upisiIzvestaj(FILE *upis, int i)
{
	int j;
	for(j = 0; j < i; j++)
        fprintf(upis, "%s %s %.2lf %s\n",
                analize[j].ime,
                analize[j].prezime,
                analize[j].BMI,
                analize[j].dijagnoza);
}
