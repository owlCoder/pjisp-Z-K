#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIMBOL    2 + 1
#define MAX_STR      20 + 1

typedef struct element_st {
    char simbol[MAX_SIMBOL];
    char ime[MAX_STR];
    int atomska_t;
    char vrsta[MAX_SIMBOL];
    struct element_st *s;
} ELEMENT;

void head_e(ELEMENT **);

int main(int argn, char **args)
{
    if(argn != 4) {
        puts("%s VRSTA IN_FILENAME OUT_FILENAME");
        exit(11);
    }
    ELEMENT *e;

    head_e(&e);
    
    return 0;
}

void head_e(ELEMENT **e)
{
    *e = NULL;
}
