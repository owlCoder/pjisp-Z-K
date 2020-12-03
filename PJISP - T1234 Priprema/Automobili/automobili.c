#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CH 10 + 1
#define MAX_NIZ 25

struct automobil_st {
    char marka[MAX_CH];
    unsigned kubikaza;
    unsigned godiste;
};

FILE *fopen_sdef(char *, char *);
unsigned load_data(FILE *, struct automobil_st *);
void automobili_zadata_marka(FILE *, struct automobil_st *, const unsigned);
void pronadji_najmladji_automobil(struct automobil_st *, const unsigned);
void unos_marke_automobila(char *);

int main(int argc, char **args)
{
    if(argc != 2)
    {
        printf("\nUsage: %s IN_FILENAME\n\n", args[0]);
        exit(0xBADCA11);
    }

    FILE *in = fopen_sdef(args[1], "r");
    FILE *out = fopen_sdef("izlaz.txt", "w");

    struct automobil_st automobili[MAX_NIZ];
    unsigned n = load_data(in, automobili);
    
    automobili_zadata_marka(out, automobili, n);
    pronadji_najmladji_automobil(automobili, n);

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

unsigned load_data(FILE *in, struct automobil_st *automobili)
{
    unsigned i = 0;

    while(fscanf(in, "%s %u %u", 
                    automobili[i].marka,
                   &automobili[i].kubikaza,
                   &automobili[i].godiste) != EOF )
    { i++; }

    return i;
}

void automobili_zadata_marka(FILE *out, struct automobil_st *automobili, const unsigned n) 
{
    unsigned i;
    char marka[MAX_NIZ];
    unos_marke_automobila(marka);

    for(i = 0; i < n; i++)
        if(strcmp(automobili[i].marka, marka) == 0)
            fprintf(out, "%s %u %u\n",
                    automobili[i].marka,
                    automobili[i].kubikaza,
                    automobili[i].godiste);
}

void pronadji_najmladji_automobil(struct automobil_st *automobili, const unsigned n)
{
    unsigned i, j, maxGodiste = 0;
    
   for(i = 1; i < n; i++)
        if(automobili[i].godiste > automobili[maxGodiste].godiste)
            maxGodiste = i;

   printf("\nNajmladji automobil je\n>> %s %u %u\n", 
                automobili[maxGodiste].marka, automobili[maxGodiste].kubikaza, automobili[maxGodiste].godiste);    
}

void unos_marke_automobila(char *marka)
{
    printf("\n\nMarka automobila\n>> ");
    scanf("%[^\n]s", marka);

    unsigned i = 0, len = (unsigned)strlen(marka), suma = 0;
    while(i < len) {
        marka[i] = tolower(marka[i]);
        i++;
    }
}