#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CH 20 + 1
#define MAX_RND 30 + 1
#define MAX_NIZ 50

struct naucnik_st {
    char ime[MAX_CH];
    char prezime[MAX_CH];
    unsigned brObjRadova;
    char rndArea[MAX_RND];
};

FILE *fopen_sdef(char *, char *);
unsigned load_data(FILE *, struct naucnik_st *);
void broj_radova_veci_od_zadatog(FILE *, struct naucnik_st *, const unsigned, const unsigned);
void unos_oblasti_istrazivanja(char *);
void avg_prezime(struct naucnik_st *, const unsigned, char *);
void broj_radova_za_oblast(struct naucnik_st *, const unsigned, char *);

int main(int argc, char **args)
{
    if(argc != 4)
    {
        printf("\nUsage: %s IN_FILENAME OUT_FILENAME brojRadova\n\n", args[0]);
        exit(0xBADCA11);
    }

    FILE *in = fopen_sdef(args[1], "r");
    FILE *out = fopen_sdef(args[2], "w");

    struct naucnik_st naucnici[MAX_NIZ];
    unsigned zadatBrRadova = atoi(args[3]);
    unsigned n = load_data(in, naucnici);
    char oblast[MAX_CH];

    broj_radova_veci_od_zadatog(out, naucnici, n, zadatBrRadova);
    unos_oblasti_istrazivanja(oblast);
    broj_radova_za_oblast(naucnici, n, oblast);
    avg_prezime(naucnici, n, oblast);

    fclose(in);
    fclose(out);

    return 0;
}

FILE *fopen_sdef(char *dat, char *mod)
{
    FILE *f = fopen(dat, mod);
    if (f == NULL) { 
        printf("\nFile %s doesn't exist!\n", dat); 
        exit(45); 
    }
    return f;
}

unsigned load_data(FILE *in, struct naucnik_st *naucnici)
{
    unsigned i = 0;

    while(fscanf(in, "%s %s %u %s", 
                   naucnici[i].ime,
                   naucnici[i].prezime,
                  &naucnici[i].brObjRadova,
                   naucnici[i].rndArea) != EOF )
    { i++; }

    return i;
}

void broj_radova_veci_od_zadatog(FILE *out, struct naucnik_st *naucnici, const unsigned n, const unsigned zadatBrRadova) 
{
    unsigned i;

    for(i = 0; i < n; i++)
        if(naucnici[i].brObjRadova > zadatBrRadova)
            fprintf(out, "%s %s %u %s\n",
                         naucnici[i].ime,
                         naucnici[i].prezime,
                         naucnici[i].brObjRadova,
                         naucnici[i].rndArea);
}

void avg_prezime(struct naucnik_st *naucnici, const unsigned n, char *oblast)
{
   int i, j, suma, brojac, prezime;

	suma = strlen(naucnici[0].prezime);
	brojac = 1;

	for(i=1;i<n;i++) {
		prezime = 0;
		for(j=0;j<i;j++) {
			if(strcmp(naucnici[i].prezime, naucnici[j].prezime) == 0) {
				prezime = 1;
			}
		}
		if(prezime == 0) {
			suma += strlen(naucnici[i].prezime);
			brojac++;
		}
	} 
    printf("\nProsecna duzina prezimena je %.2f\n", (float)suma/(float)brojac);
}

void broj_radova_za_oblast(struct naucnik_st *naucnici, const unsigned n, char *oblast)
{
    unsigned i, suma = 0;

    for(i = 0; i < n; i++)
        if(strcmp(oblast, naucnici[i].rndArea) == 0)
            suma += naucnici[i].brObjRadova;
    
    char tmpOblast[30];

    strcpy(tmpOblast, oblast);
    strcat(tmpOblast, ".txt");
    FILE *out = fopen_sdef(tmpOblast, "w");
    fprintf(out, "%u", suma);

    fclose(out);
}

void unos_oblasti_istrazivanja(char *oblast)
{
    printf("\n\nOblast istrazivanja\n>> ");
    scanf("%[^\n]s", oblast);

    unsigned i = 0, len = (unsigned)strlen(oblast), suma = 0;
    while(i < len) {
        oblast[i] = tolower(oblast[i]);
        i++;
    }
}