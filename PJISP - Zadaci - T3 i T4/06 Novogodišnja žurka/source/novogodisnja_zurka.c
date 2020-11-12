#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NIZ 100

struct zelja_st {
    char nazivZeljenjePice[20 + 1];
    unsigned brojGostiju;
};

struct porudzbina_st {
    double brojPotrebnihParcadi;
    unsigned brojPotrebnihCelihParcadi;
    char nazivZeljenjePice[20 + 1];
};

FILE *otvoriDatoteku(char *, char *);
int ucitajPodatke(FILE *, struct zelja_st[]);
void celePice(int, double, struct zelja_st[], struct porudzbina_st[]);
void upisiIzvestaj(FILE *, int, struct porudzbina_st[]);

int main(int argc, char **argm)
{
    if(argc != 4)
    {
		printf("USAGE: %s apetit IN_FILENAME OUT_FILENAME\n", argm[0]);
		exit(42);
    }
    else {

        FILE *datoteka = otvoriDatoteku(argm[2], "r");
        FILE *upis = otvoriDatoteku(argm[3], "w");
        
        struct zelja_st zelje[MAX_NIZ];
        struct porudzbina_st porudzbine[MAX_NIZ];

        int i = ucitajPodatke(datoteka, zelje);
        double apetit = atof(argm[1]);

        celePice(i, apetit, zelje, porudzbine);
        upisiIzvestaj(upis, i, porudzbine);

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

int ucitajPodatke(FILE *datoteka, struct zelja_st zelje[])
{
	int i = 0;
	rewind(datoteka);
    while( (fscanf(datoteka, "%u %s",
               &zelje[i].brojGostiju,
                zelje[i].nazivZeljenjePice)) != EOF) {
        i++;
    }
	return i;
}

void celePice(int i, double apetit, struct zelja_st zelje[], struct porudzbina_st porudzbine[])
{
    int j;
	for(j = 0; j < i; j++)
	{
		strcpy(porudzbine[j].nazivZeljenjePice,
			   zelje[j].nazivZeljenjePice);

        porudzbine[j].brojPotrebnihParcadi = (double)zelje[j].brojGostiju * apetit;

        double tmp = (porudzbine[j].brojPotrebnihParcadi / 8);
        if( (tmp - (int)tmp) != 0. )
            porudzbine[j].brojPotrebnihCelihParcadi = (int)tmp + 1;
        else
            porudzbine[j].brojPotrebnihCelihParcadi = (int)tmp;

	}
}

void upisiIzvestaj(FILE *upis, int i, struct porudzbina_st porudzbine[])
{
	int j;
	for(j = 0; j < i; j++)
        fprintf(upis, "%5.1lf %2u %s\n",
                porudzbine[j].brojPotrebnihParcadi,
                porudzbine[j].brojPotrebnihCelihParcadi,
                porudzbine[j].nazivZeljenjePice);
}
