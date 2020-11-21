/*
    Truth factor - 100%
    Slikovno pojašnjenje rada programa:
    https://upload.wikimedia.org/wikipedia/commons/c/c4/BMPfileFormat.png
*/

#include <stdio.h>
#include <stdlib.h>

#define HEADER_SIZE 54
#define WIDTH_POS 18
#define HEIGHT_POS 22

struct pixel_st {
    unsigned char B, G, R; // gcc is pretty weird, swap variables location and fix bug!?
};

FILE *s_fopen(char *, char *);
void *s_calloc(size_t, size_t);
unsigned bmp_heder(FILE *, unsigned char *);
void read_img(FILE *, struct pixel_st *, unsigned);
void write_img(FILE *, unsigned char *, struct pixel_st *, unsigned);
void istinitost_na_max(struct pixel_st *pixels, unsigned image_size, double truth_factor);

int main(int argc, char **argm)
{   
    if(argc != 4) {
        printf("\n\nUPOTREBA: %s in.bmp out.bmp truth_factor\n\n", argm[0]);
        exit(0xBAD042);
    }
    else {
        FILE *inDatoteka = s_fopen(argm[1], "rb");
        FILE *izlaznaDatoteka = s_fopen(argm[2], "wb");
    
        double faktor_istine = atof(argm[3]);

        unsigned char *heder = s_calloc(HEADER_SIZE, sizeof(unsigned char));
        unsigned img_size = bmp_heder(inDatoteka, heder);

        struct pixel_st *pixels = s_calloc(img_size, sizeof(struct pixel_st));
        
        read_img(inDatoteka, pixels, img_size);
        istinitost_na_max(pixels, img_size, faktor_istine);
        write_img(izlaznaDatoteka, heder, pixels, img_size);

        free(pixels); free(heder); 
        fclose(inDatoteka); fclose(izlaznaDatoteka);

        return 0;
    }
}

FILE *s_fopen(char *dat, char *rezim)
{ 
    FILE *datoteka =  fopen(dat, rezim);
    if(datoteka == NULL)
    { 
        printf("\nNije moguce otvoriti datoteku %s\n\n", dat);
        exit(42);
    }
    else
        return datoteka;
}

void *s_calloc(size_t brClanova, size_t velicinaClana)
{
    void *niz = calloc(brClanova, velicinaClana);
    if(niz == NULL) { 
        printf("\nNema memorije za alokaciju\nError code: %x\n", 0xBADA110C);
        exit(43);
    }
    else
        return niz;
}

unsigned bmp_heder(FILE *datoteka, unsigned char *heder)
{
    fread(heder, sizeof(unsigned char), HEADER_SIZE, datoteka);
    
    unsigned  width = *(unsigned *) &heder[WIDTH_POS];
    unsigned  height = *(unsigned *) &heder[HEIGHT_POS];

    return width * height;
}

void read_img(FILE *datoteka, struct pixel_st *pixels, unsigned img_size)
{
    fread(pixels, sizeof(struct pixel_st), img_size, datoteka);
}

void write_img(FILE *datoteka, unsigned char *heder, struct pixel_st *pixels, unsigned img_size)
{
    fwrite(heder, sizeof(unsigned char), HEADER_SIZE, datoteka);
    fwrite(pixels, sizeof(struct pixel_st), img_size, datoteka);
}

void istinitost_na_max(struct pixel_st *pixels, unsigned image_size, double truth_factor) {
    unsigned i;
    for(i=0; i<image_size; i++) {
        pixels[i].R = pixels[i].R * (1 - truth_factor) + 0xFC * truth_factor;
        pixels[i].G = pixels[i].G * (1 - truth_factor) + 0x89 * truth_factor;
        pixels[i].B = pixels[i].B * (1 - truth_factor) + 0xAC * truth_factor;
    }
}
