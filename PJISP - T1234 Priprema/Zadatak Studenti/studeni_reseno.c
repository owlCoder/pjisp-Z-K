#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BR_INDEX 15
#define MAX_NAZIV 20 + 1
#define MAX_studenti 100

struct student_st
{
    char brojIndeksa[MAX_BR_INDEX];
    char ime[MAX_NAZIV];
    char prezime[MAX_NAZIV];
    unsigned brojPoena;
};

FILE *otvori_fajl(char *, char *);
unsigned ucitaj_podatke(FILE *, struct student_st *);
void sortiraj_studente(struct student_st *, unsigned );
void najduze_prezime(struct student_st *, unsigned);
void najkrace_prezime(struct student_st *, unsigned);
void preko_x_poena(FILE *, struct student_st *, unsigned, unsigned);
void avg_len_ime(FILE *, struct student_st *, unsigned);

int main(int argc, char **argm)
{
    unsigned poeni = atoi(argm[2]);
    char nazivOut[MAX_NAZIV] = "preko_";
    strcat(nazivOut, argm[2]);
    strcat(nazivOut, "_poena.txt");

    FILE *in = otvori_fajl(argm[1], "r");
    FILE *prekoPoena = otvori_fajl(nazivOut, "w");
    FILE *out = otvori_fajl("izlaz.txt", "w");

    struct student_st studenti[MAX_studenti];

    unsigned n = ucitaj_podatke(in, studenti);
    sortiraj_studente(studenti, n);
    najduze_prezime(studenti, n);
    najkrace_prezime(studenti, n);
    preko_x_poena(prekoPoena, studenti, n , poeni);
    avg_len_ime(out, studenti, n);

    fclose(in);
    fclose(prekoPoena);
    fclose(out);

    return 0;
}

FILE *otvori_fajl(char *naziv, char *rezim)
{
    FILE *f = fopen(naziv, rezim);

    if(f == NULL)
    {
        printf("\nFile %s doesn't exist!", naziv);
        exit(50);
    }
    return f;
}

unsigned ucitaj_podatke(FILE *dat, struct student_st *studenti)
{
    unsigned i = 0;

    while( fscanf(dat, "%s %s %s %u",
                         studenti[i].brojIndeksa,
                         studenti[i].ime,
                         studenti[i].prezime,
                        &studenti[i].brojPoena) != EOF)
    {
        i++;
    }
    return i;
}

void sortiraj_studente(struct student_st *studenti, unsigned n)
{
    unsigned i, j = 0;
    const unsigned maxLenBrIndeksa = 10;
    struct student_st temp;

    for(i = 0; i < n -1; ++i)
        for(j = i + 1; j < n ; ++j) {
            if(strcmp(studenti[i].brojIndeksa, studenti[j].brojIndeksa) > 0) {
                strcpy(temp.brojIndeksa, studenti[i].brojIndeksa);
                strcpy(temp.ime, studenti[i].ime);
                strcpy(temp.prezime, studenti[i].prezime);
                temp.brojPoena = studenti[i].brojPoena;
                
                strcpy(studenti[i].brojIndeksa, studenti[j].brojIndeksa);
                strcpy(studenti[i].ime, studenti[j].ime);
                strcpy(studenti[i].prezime, studenti[j].prezime);
                studenti[i].brojPoena = studenti[j].brojPoena;
                
                strcpy(studenti[j].brojIndeksa, temp.brojIndeksa);
                strcpy(studenti[j].ime, temp.ime);
                strcpy(studenti[j].prezime, temp.prezime);
                studenti[j].brojPoena = temp.brojPoena;
            }
        }

    FILE *sortStudent = otvori_fajl("sortirani_studenti.txt", "w");
    for(i = 0; i < n; i++)
    {
        fprintf(sortStudent, "%s %s %s %u\n", 
                        studenti[i].brojIndeksa,
                        studenti[i].ime,
                        studenti[i].prezime,
                        studenti[i].brojPoena);
    }
    fclose(sortStudent);
}

void najduze_prezime(struct student_st *studenti, unsigned n)
{
    unsigned i, j = 0;
    unsigned najduze = strlen(studenti[0].prezime);

    for(i = 1; i < n; i++)
    {
        unsigned tmp = strlen(studenti[i].prezime);
        if(tmp > najduze) {
            najduze = tmp;
            j = i;
        }
    }
    printf("\nStudent sa najduzim prezimenom je:\n%s %s %s\n",
        studenti[j].brojIndeksa, studenti[j].ime, studenti[j].prezime);
}

void najkrace_prezime(struct student_st *studenti, unsigned n)
{
    unsigned i, j = 0;
    unsigned najkrace = strlen(studenti[0].prezime);

    for(i = 1; i < n; i++)
    {
        unsigned tmp = strlen(studenti[i].prezime);
        if(tmp < najkrace) {
            najkrace = tmp;
            j = i;
        }
    }
    printf("\nStudent sa najkracim prezimenom je:\n%s %s %s\n",
        studenti[j].brojIndeksa, studenti[j].ime, studenti[j].prezime);
}

void preko_x_poena(FILE *preko, struct student_st *studenti, unsigned n, unsigned poeni)
{
    unsigned i;
    for(i = 0; i < n; i++)
    {
        if(studenti[i].brojPoena > poeni)
            fprintf(preko, "%s %s %s %u\n", 
                         studenti[i].brojIndeksa,
                         studenti[i].ime,
                         studenti[i].prezime,
                         studenti[i].brojPoena);
    }
}

void avg_len_ime(FILE *out, struct student_st *studenti, unsigned n)
{
    double suma = 0.0;
    unsigned i;

    for(i = 0; i < n; i++)
    {
        unsigned tmp = strlen(studenti[i].ime);
        suma += (double)tmp;
    }

    fprintf(out, "Prosecna duzina imena studenata iznosi %.2lf karaktera.\n",
                suma / n);
}