#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NIZ 100

struct gorivo_st {
    char oznakaGrada[2 + 1];
    char tipGoriva[10 + 1];
    double cenaGoriva;
};

struct analiza_st {
    double novaCenaGoriva;
    double procUvecanjaCeneGoriva;
    char oznakaGrada[2 + 1];
    char tipGoriva[10 + 1];
};

FILE *otvoriDatoteku(char *, char *);
int ucitajPodatke(FILE *, struct gorivo_st[]);
void analizaSaAkcizom(int, double, struct gorivo_st[], struct analiza_st[]);
void upisiIzvestaj(FILE *, int, struct analiza_st[]);

int main(int argc, char **argm)
{
    if(argc != 4)
    {
		printf("USAGE: %s akciza IN_FILENAME OUT_FILENAME\n", argm[0]);
		exit(42);
    }
    else {

        FILE *datoteka = otvoriDatoteku(argm[2], "r");
        FILE *upis = otvoriDatoteku(argm[3], "w");

        struct gorivo_st goriva[MAX_NIZ];
        struct analiza_st  analize[MAX_NIZ];

        int i = ucitajPodatke(datoteka, goriva);
        double akciza = atof(argm[1]);

        if(akciza <= 0)
        {
            printf("\nAkciza ne može biti negativan broj!\n");
            exit(42);
        }
        else {
            analizaSaAkcizom(i, akciza, goriva, analize);
            upisiIzvestaj(upis, i, analize);

            fclose(datoteka);
            fclose(upis);

            return 0;
        }
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

int ucitajPodatke(FILE *datoteka, struct gorivo_st goriva[])
{
	int i = 0;
	rewind(datoteka);
    while( (fscanf(datoteka, "%s %s %lf",
                goriva[i].oznakaGrada,
                goriva[i].tipGoriva,
               &goriva[i].cenaGoriva)) != EOF) {
        i++;
    }
	return i;
}

void analizaSaAkcizom(int i, double akciza, struct gorivo_st goriva[], struct analiza_st analize[])
{
    int j;
	for(j = 0; j < i; j++)
	{
		strcpy(analize[j].oznakaGrada,
			   goriva[j].oznakaGrada);

        strcpy(analize[j].tipGoriva,
			   goriva[j].tipGoriva);

        analize[j].novaCenaGoriva = goriva[j].cenaGoriva + akciza;

        analize[j].procUvecanjaCeneGoriva = (
               (analize[j].novaCenaGoriva / goriva[j].cenaGoriva) - 1) * 100;
	}
}

void upisiIzvestaj(FILE *upis, int i, struct analiza_st analize[])
{
	int j;
	for(j = 0; j < i; j++)
        fprintf(upis, "%6.2lf %5.2lf %s %s\n",
                analize[j].novaCenaGoriva,
                analize[j].procUvecanjaCeneGoriva,
                analize[j].oznakaGrada,
                analize[j].tipGoriva);
}
