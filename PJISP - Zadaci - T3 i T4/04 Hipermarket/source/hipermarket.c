#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NIZ 100

struct artikal_st {
    double cena;
    int brojProdatihArtikala;
    double trgovackaMarza;
    char naziv[20 + 1];
};

struct zarada_st {
    char naziv[20 + 1];
    double ostvarenaZarada;
};

FILE *otvoriDatoteku(char *, char *);
int ucitajPodatke(FILE *, struct artikal_st[]);
void zarada(int, struct artikal_st[], struct zarada_st[]);
void upisiIzvestaj(FILE *, int, struct zarada_st[]);

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

        struct artikal_st artikli[MAX_NIZ];
        struct zarada_st analizaZarade[MAX_NIZ];

        int i = ucitajPodatke(datoteka, artikli);

        zarada(i, artikli, analizaZarade);
        upisiIzvestaj(upis, i, analizaZarade);

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

int ucitajPodatke(FILE *datoteka, struct artikal_st artikli[])
{
	int i = 0;
	rewind(datoteka);
    while( (fscanf(datoteka, "%lf %d %lf %s",
               &artikli[i].cena,
               &artikli[i].brojProdatihArtikala,
               &artikli[i].trgovackaMarza,
                artikli[i].naziv)) != EOF) {
        i++;
    }
	return i;
}

void zarada(int i, struct artikal_st artikli[], struct zarada_st analizaZarade[])
{
    int j;
	for(j = 0; j < i; j++)
	{
		strcpy(analizaZarade[j].naziv,
			   artikli[j].naziv);

        analizaZarade[j].ostvarenaZarada = (
                (artikli[j].cena * artikli[j].brojProdatihArtikala)
                * (artikli[j].trgovackaMarza / 100) );
	}
}

void upisiIzvestaj(FILE *upis, int i, struct zarada_st analizaZarade[])
{
	int j;
	for(j = 0; j < i; j++)
        fprintf(upis, "%7.2lf %s\n",
                analizaZarade[j].ostvarenaZarada,
                analizaZarade[j].naziv);
}
