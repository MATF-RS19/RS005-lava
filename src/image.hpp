#ifndef _H_IMAGES_H_
#define _H_IMAGES_H_


/*
 * Dve strukture koje opisuju strukturu dva zaglavlja
 * kojima pocinje svaka slika u bmp formatu.
 */
 
typedef struct {
  unsigned short type;
  unsigned int size;
  unsigned short reserved1;
  unsigned short reserved2;
  unsigned int offsetbits;
} BITMAPFILEHEADER;

typedef struct {
  unsigned int size;
  unsigned int width;
  unsigned int height;
  unsigned short planes;
  unsigned short bitcount;
  unsigned int compression;
  unsigned int sizeimage;
  int xpelspermeter;
  int ypelspermeter;
  unsigned int colorsused;
  unsigned int colorsimportant;
} BITMAPINFOHEADER;

/* Struktura za smestanje podataka o slici. */
typedef struct Image {
    Image(int width, int height);
    ~Image();
    /*
     * Funkcija za ucitavanje podataka o slici koja se nalazi
     * u fajlu cije je ime filename u strukturu na koju pokazuje
     * image.
     */
    void read(const char *filename);
  int width, height; /* Dimenzije slike. */
  char *pixels; /* Niz u kojem se cuvaju podaci za sve piksele u obliku (R, G, B). */
} Image;

#endif
