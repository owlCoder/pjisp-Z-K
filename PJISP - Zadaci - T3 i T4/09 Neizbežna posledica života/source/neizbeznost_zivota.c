#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NIZ 100

struct poreska_stopa_st {
    char skrOznakaGrada[2 + 1];
    unsigned osnovniPorez;
    double dodPorezPoKvNekretnine;
    double procPorPopustaPoClPorodice;
};

struct porez_st {
    char skrOznakaGrada[2 + 1];
    double ukupanPorezBezPopusta;
    double ukupanPorezSaPopustom;
};

FILE *otvoriDatoteku(char *, char *);
int ucitajPodatke(FILE *, struct poreska_stopa_st[]);
void ukupanPorez(int, double, unsigned, struct poreska_stopa_st[], struct porez_st[]);
void upisiIzvestaj(FILE *, int, struct porez_st[]);

int main(int argc, char **argm)
{
    if(argc != 5)
    {
		printf("USAGE: %s povrsina_nekretnine broj_clanova_domacinstva IN_FILENAME OUT_FILENAME\n", argm[0]);
		exit(42);
    }
    else {

        FILE *datoteka = otvoriDatoteku(argm[3], "r");
        FILE *upis = otvoriDatoteku(argm[4], "w");

        struct poreska_stopa_st porezi[MAX_NIZ];
        struct porez_st stope[MAX_NIZ];

        int i = ucitajPodatke(datoteka, porezi);
        double kvadratura = atof(argm[1]);
        unsigned clanovaDomacinstva = atoi(argm[2]);

        ukupanPorez(i, kvadratura, clanovaDomacinstva, porezi, stope);
        upisiIzvestaj(upis, i, stope);

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

int ucitajPodatke(FILE *datoteka, struct poreska_stopa_st stope[])
{
	int i = 0;
	rewind(datoteka);
    while( (fscanf(datoteka, "%s %d %lf %lf",
                stope[i].skrOznakaGrada,
               &stope[i].osnovniPorez,
               &stope[i].dodPorezPoKvNekretnine,
               &stope[i].procPorPopustaPoClPorodice)) != EOF) {
        i++;
    }
	return i;
}

void ukupanPorez(int i, double kvadratura, unsigned clanovaDomacinstva, struct poreska_stopa_st stope[], struct porez_st porezi[])
{
    int j;
	for(j = 0; j < i; j++)
	{
		strcpy(porezi[j].skrOznakaGrada,
			   stope[j].skrOznakaGrada);

        porezi[j].ukupanPorezBezPopusta = 
                (stope[j].dodPorezPoKvNekretnine * kvadratura) + stope[j].osnovniPorez;
        
        porezi[j].ukupanPorezSaPopustom =  porezi[j].ukupanPorezBezPopusta -  (porezi[j].ukupanPorezBezPopusta 
                    * ((stope[j].procPorPopustaPoClPorodice / 100) * clanovaDomacinstva) );
        
    }
}

void upisiIzvestaj(FILE *upis, int i, struct porez_st porezi[])
{
	int j;
	for(j = 0; j < i; j++)
        fprintf(upis, "%s %5.0lf %5.0lf\n",
                porezi[j].skrOznakaGrada,
                porezi[j].ukupanPorezBezPopusta,
                porezi[j].ukupanPorezSaPopustom);
}