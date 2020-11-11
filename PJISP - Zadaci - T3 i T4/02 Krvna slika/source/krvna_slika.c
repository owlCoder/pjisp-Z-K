#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NIZ 100

struct pacijent_st {
    char ime[20 + 1];
    char prezime[20 + 1];
    double holesterol;
    double pritisak;
    double secer;
};

struct analiza_st {
    char upozorenje[2];
    char ime[20 + 1];
    char prezime[20 + 1];
};

FILE *otvoriDatoteku(char *, char *);
int ucitajPodatke(FILE *, struct pacijent_st []);
void calcPrSeHo(int, char *, struct pacijent_st [], struct analiza_st []);
void upisiIzvestaj(FILE *, int, struct analiza_st []);

int main(int argc, char **argm)
{
    if(argc != 4)
    {
		printf("USAGE: %s TIP_IZVESTAJA IN_FILENAME OUT_FILENAME\n", argm[0]);
		exit(42);
    }
    else {

        FILE *datoteka = otvoriDatoteku(argm[2], "r");
        FILE *upis = otvoriDatoteku(argm[3], "w");

        struct pacijent_st pacijenti[MAX_NIZ];
        struct analiza_st analize[MAX_NIZ];

        int i = ucitajPodatke(datoteka, pacijenti);

        calcPrSeHo(i, argm[1], pacijenti, analize);
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
    while( (fscanf(datoteka, "%s %s %lf %lf %lf",
                pacijenti[i].ime,
                pacijenti[i].prezime,
               &pacijenti[i].holesterol,
               &pacijenti[i].pritisak,
               &pacijenti[i].secer)) != EOF) {
        i++;
    }
	return i;
}

void calcPrSeHo(int i, char *tipIzvestaja, struct pacijent_st pacijenti[], struct analiza_st analize[])
{
    int ti = 0; /// 1 - holesterol   2 - pritisak  3 - secer
    if(strcmp("pritisak", tipIzvestaja) == 0)
        ti = 2;
    else if(strcmp("holesterol", tipIzvestaja) == 0)
        ti = 1;
    else if(strcmp("secer", tipIzvestaja) == 0)
        ti = 3;

    printf("%d", ti);
	int j, tmp = 0;
	for(j = 0; j < i; j++)
	{
		strcpy(analize[j].ime,
			   pacijenti[j].ime);
		strcpy(analize[j].prezime,
			   pacijenti[j].prezime);

        switch(ti) {
            case 1:
                if(pacijenti[j].holesterol < 5.2) {
                    analize[j].upozorenje[0] = '-';
                    analize[j].upozorenje[1] = '\0';
                }
                else {
                    analize[j].upozorenje[0] = '+';
                    analize[j].upozorenje[1] = '\0';
                }
                break;

            case 2:
                if( (pacijenti[j].pritisak < 120) && (pacijenti[j].pritisak >= 90) ) {
                    analize[j].upozorenje[0] = '-';
                    analize[j].upozorenje[1] = '\0';
                }
                else {
                    analize[j].upozorenje[0] = '+';
                    analize[j].upozorenje[1] = '\0';
                }
                break;

            case 3:
                if( (pacijenti[j].secer < 5.6) && (pacijenti[j].secer >= 3.9) ) {
                    analize[j].upozorenje[0] = '-';
                    analize[j].upozorenje[1] = '\0';
                }
                else {
                    analize[j].upozorenje[0] = '+';
                    analize[j].upozorenje[1] = '\0';
                }
                break;

            default:
                printf("\nZa analizu tipa %s nije dostupan izvestaj!\n", tipIzvestaja);
                exit(-1);
        }
	}
}

void upisiIzvestaj(FILE *upis, int i, struct analiza_st analize[])
{
	int j;
	for(j = 0; j < i; j++)
        fprintf(upis, "%s %s %s\n",
                analize[j].upozorenje,
                analize[j].ime,
                analize[j].prezime);
}
