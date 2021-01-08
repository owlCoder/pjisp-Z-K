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

// Generic files functions

int main(int argn, char **args)
{
    if(argn != 4) {
        puts("%s VRSTA IN_FILENAME OUT_FILENAME");
        exit(11);
    }
    ELEMENT *e;

    head_e(&e);
    //add_e(&e, create_e("C", "VINO", 33, "metal"));

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
