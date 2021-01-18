#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAZIV 13 + 1

typedef struct artikli_st 
{
	int serijskiBroj;
	char naziv[MAX_NAZIV];
	double jedCena;
	unsigned komada;
	double ukupnaCena;
	struct artikli_st *sledeci;
} ARTIKLI;

void init_list(ARTIKLI **);
ARTIKLI *create_new_item(const int, const char *, const double, const unsigned, const double);
void destroy_list(ARTIKLI **);

void add_to_list_sorted(ARTIKLI **, ARTIKLI *);

FILE *s_fopen(char *, char *);
void data_load(FILE *, ARTIKLI **);

void print_list(ARTIKLI *);
void kupljeni_artikli(ARTIKLI *, double);

int main(int argn, char **args) 
{
	if(argn != 3) {
		printf("\nUsage: %s budzet IN_FILENAME\n", args[0]);
		exit(1);
	}
    if(atof(args[1]) < 0.0) {
        printf("\nBudzet mora biti pozitivan broj!\n");
		exit(6);
    }
	ARTIKLI *glava;
	FILE *in = s_fopen(args[2], "r");

	init_list(&glava);
	data_load(in, &glava);
	kupljeni_artikli(glava, atof(args[1]));
	destroy_list(&glava);
	fclose(in);

    return 0;
}

void init_list(ARTIKLI **glava)
{
	*glava = NULL;
}

ARTIKLI *create_new_item(const int sb, const char *n, const double jc, const unsigned kom, const double uc)
{
	ARTIKLI *o = (ARTIKLI *) malloc(sizeof(ARTIKLI));
	if(o == NULL)
	{
		printf("\nAllocation failed!\n");
		exit(2);
	}
	strcpy(o -> naziv, n);
	o -> serijskiBroj = sb;
	o -> jedCena = jc;
    o -> komada = kom;
    o -> ukupnaCena = uc;
	o -> sledeci = NULL;

	return o;
}

void destroy_list(ARTIKLI **glava)
{
	if(*glava != NULL)
	{
		destroy_list(&(*glava) -> sledeci);
		free(*glava);
		*glava = NULL;
	}
}

void add_to_list(ARTIKLI **glava, ARTIKLI *novi)
{
	if(*glava == NULL || (*glava) -> serijskiBroj >= novi -> serijskiBroj) {
		novi -> sledeci = *glava;
		*glava = novi;
	}
	else if( (*glava) -> sledeci != NULL && (*glava) -> serijskiBroj < novi -> serijskiBroj)
	{
		add_to_list(&(*glava) -> sledeci, novi);
	}
	else
	{
		novi -> sledeci = (*glava) -> sledeci;
       (*glava) -> sledeci = novi;
	}
}

FILE *s_fopen(char *name, char *mode)
{
	FILE *f = fopen(name, mode);
	if(f == NULL) {
		printf("\nCouldn't open %s!\n", name);
		exit(3);
	}
	return f;
}

void data_load(FILE *in, ARTIKLI **glava)
{
	ARTIKLI *o;
	while(fscanf(in, "%d %s %lf %u", &o -> serijskiBroj, o -> naziv, &o -> jedCena, &o -> komada) != EOF) {
        o -> ukupnaCena = (o -> jedCena) * (o -> komada);
		ARTIKLI *novi = create_new_item(o -> serijskiBroj, o -> naziv, o -> jedCena, o -> komada, o -> ukupnaCena);
		add_to_list(glava, novi);
	}
}

void print_list(ARTIKLI *g)
{
	while(g != NULL)
	{
        printf("%3d %-10s %6.2lf %3u %6.2lf\n", g -> serijskiBroj, g -> naziv, g -> jedCena, g -> komada, g -> ukupnaCena);
		g = g -> sledeci;
	}
}

void kupljeni_artikli(ARTIKLI *g, double budzet)
{
	unsigned kupljeno = 0;
	while(g != NULL)
	{
        double stanje = g -> ukupnaCena;
		if(stanje <= budzet) {
			 printf("%3d %-10s %6.2lf %3u %6.2lf\n", g -> serijskiBroj, g -> naziv, g -> jedCena, g -> komada, g -> ukupnaCena);
             budzet -= stanje;
             kupljeno = 1;
        }
        else {
            if(!kupljeno) {
                printf("\nNemate sredstava za kupovinu artikala!\n");
                break;
            }
        }
		g = g -> sledeci;
	}
    // printf("\nPreostali budzet je: %6.2lf\n", budzet); // NIJE TRAŽENO U ZADATKU
}
