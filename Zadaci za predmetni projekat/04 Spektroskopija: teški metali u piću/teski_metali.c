#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIMBOL    2 + 1
#define MAX_STR      20 + 1

typedef struct element_st {
    char simbol[MAX_SIMBOL];
    char ime[MAX_STR];
    int atomska_t;
    char vrsta[MAX_STR];
    struct element_st *s;
} ELEMENT;

// Functions for work with LIST
void head_e(ELEMENT **);
ELEMENT *create_e(const char *, const char *, const int, const char *);
void add_e(ELEMENT **, ELEMENT *);
void print_e(ELEMENT *);
void delete_e(ELEMENT **);

// Generic files functions
FILE *safe_f(char *, char *);
void read_f(FILE *, ELEMENT **);
void receive_data(ELEMENT *, ELEMENT **);

int main(int argn, char **args)
{
    if(argn != 4) {
        puts("%s VRSTA IN_FILENAME OUT_FILENAME");
        exit(11);
    }
    ELEMENT *e;

    FILE *in = safe_f(args[2], "r");
    FILE *out = safe_f(args[3], "w");

    head_e(&e); 
    read_f(in, &e);
    delete_e(&e);

    fclose(in);
    fclose(out);

    return 0;
}

void head_e(ELEMENT **e)
{
    *e = NULL;
}

ELEMENT *create_e(const char *s, const char *i, const int a, const char *v)
{
    ELEMENT *new = (ELEMENT *) malloc(sizeof(ELEMENT));
    if(new == NULL) {
        puts("NO RAM!");
        exit(45);
    }
    strcpy(new -> simbol, s);
    strcpy(new -> ime, i);
    new -> atomska_t = a;
    strcpy(new -> vrsta, v);
    new -> s = NULL;

    return new;
}

void add_e(ELEMENT **e, ELEMENT *n)
{
    if(*e == NULL) {
        *e = n;
        return;
    }
    add_e(&(*e) -> s, n);
}

void print_e(ELEMENT *e)
{
    if(e == NULL)
        return;
    printf("%s %s %d %s\n", e -> simbol, e -> ime, e -> atomska_t, e -> vrsta);
    print_e(e -> s);
}

void delete_e(ELEMENT **e)
{
    if(*e == NULL)
        return;
    delete_e(&(*e) -> s);
    free(*e);
    *e = NULL;
}

FILE *safe_f(char *n, char *m)
{
    FILE *f = fopen(n, m);
    if(f == NULL) {
        puts("INVALID REQUEST FOR OPENING FILE!");
        exit(46);
    }
    return f;
}

void read_f(FILE *f, ELEMENT **e) 
{
    ELEMENT *tmp = (ELEMENT *) malloc(sizeof(ELEMENT));

    while(fscanf(f, "%s %s %d %s", tmp -> simbol,    tmp -> ime,
                                &tmp -> atomska_t, tmp -> vrsta) != EOF)
        receive_data(tmp, e);

    free(tmp);
    tmp = NULL;
}

void receive_data(ELEMENT *n, ELEMENT **e)
{
    ELEMENT *new = (ELEMENT *) malloc(sizeof(ELEMENT));
    new = create_e(n -> simbol,    n -> ime,
                      n -> atomska_t, n -> vrsta);
    add_e(e, new);
}
