#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAZIV 20 + 1

typedef struct obrok_st 
{
	char naziv[MAX_NAZIV];
	char vrsta[MAX_NAZIV];
	unsigned gramaza;
	unsigned kalorije;
	struct obrok_st *sledeci;
} OBROCI;


void init_list(OBROCI **glava)
{
	*glava = NULL;
}

OBROCI *create_new_item(const char *naziv, const char *vrsta, const unsigned gramaza, const unsigned kalorije)
{
	OBROCI *o = (OBROCI *) malloc(sizeof(OBROCI));
	if(o == NULL)
	{
		printf("\nAllocation failed!\n");
		exit(2);
	}
	strcpy(o -> naziv, naziv);
	strcpy(o -> vrsta, vrsta);
	o -> gramaza = gramaza;
	o -> kalorije = kalorije;
	o -> sledeci = NULL;

	return o;
}

void destroy_list(OBROCI **glava)
{
	if(*glava != NULL)
	{
		destroy_list(&(*glava) -> sledeci);
		free(*glava);
		*glava = NULL;
	}
}

void add_to_list(OBROCI **glava, OBROCI *novi)
{
	if(*glava == NULL) {
       *glava = novi;
       return;
	}
    add_to_list(&(*glava) -> sledeci, novi);
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

void data_load(FILE *in, OBROCI **glava)
{
	OBROCI *o;
	while(fscanf(in, "%s %s %u %u", o -> naziv, o -> vrsta, &o -> gramaza, &o -> kalorije) != EOF) {
		OBROCI *novi = create_new_item(o -> naziv, o -> vrsta, o -> gramaza, o -> kalorije);
		add_to_list(glava, novi);
	}
}

void print_list(OBROCI *glava, char *criteria)
{
	while(glava != NULL)
	{
		if(strcmp(glava -> vrsta, criteria) == 0)
			printf("%-10s %3u %3u\n", glava -> naziv, glava -> gramaza, glava -> kalorije);
		glava = glava -> sledeci;
	}
}

void najmanje_kalorican(OBROCI *glava, char *criteria)
{
	OBROCI *min = NULL;
	while(glava != NULL)
	{
		if(strcmp(glava -> vrsta, criteria) == 0) {
			if(min == NULL)
				min = glava;
			else if( ((glava -> gramaza * glava -> kalorije) / 100) < ((min -> gramaza * min -> kalorije) / 100))
				min = glava;
		}
		glava = glava -> sledeci;
	}
	if(min == NULL)
		printf("\nNe postoji %s sa najmanje kalorija!\n", criteria);
	else
		printf("\nNajmanje kalorija ima:\n%-8s %10s %u %u\n", min -> naziv, min -> vrsta, min -> gramaza, min -> kalorije);
}

int main(int argn, char **args) 
{
	if(argn != 3)
	{
		printf("\nUsage: %s vrstaObroka IN_FILENAME\n", args[0]);
		exit(1);
	}
	OBROCI *glava;
	FILE *in = s_fopen(args[2], "r");

	init_list(&glava);
	data_load(in, &glava);
	print_list(glava, args[1]);
	najmanje_kalorican(glava, args[1]);
	destroy_list(&glava);
	fclose(in);

    return 0;
}

