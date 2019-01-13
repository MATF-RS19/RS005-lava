/*preuzeto  sa https://github.com/MATF-RG16/RG16-005-3d-lavirint/blob/master/image.c i prevedeno u cpp*/

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "image.hpp"

Image::Image(int width, int height)
    : width(width),
      height(height),
      pixels(nullptr)
{}

Image::~Image()
{
    delete [] pixels;
}

void Image::read(const char *filename) {

  BITMAPFILEHEADER bfh;
  BITMAPINFOHEADER bih;
  unsigned int i;
  char r, g, b, a;

  delete [] pixels;

  /* Otvara se fajl koji sadrzi sliku u binarnom rezimu. */
  std::ifstream file(filename, std::ios_base::binary);
  assert(file.is_open());

  /* Ocitavaju se podaci prvog zaglavlja. */
  file.read(reinterpret_cast<char *>(&bfh.type), sizeof(bfh.type));
  file.read(reinterpret_cast<char *>(&bfh.size), sizeof(bfh.size));
  file.read(reinterpret_cast<char *>(&bfh.reserved1), sizeof(bfh.reserved1));
  file.read(reinterpret_cast<char *>(&bfh.reserved2), sizeof(bfh.reserved2));
  file.read(reinterpret_cast<char *>(&bfh.offsetbits), sizeof(bfh.offsetbits));

  /* Ocitavaju se podaci drugog zaglavlja. */
  file.read(reinterpret_cast<char *>(&bih.size), sizeof(bih.size));
  file.read(reinterpret_cast<char *>(&bih.width), sizeof(bih.width));
  file.read(reinterpret_cast<char *>(&bih.height), sizeof(bih.height));
  file.read(reinterpret_cast<char *>(&bih.planes), sizeof(bih.planes));
  file.read(reinterpret_cast<char *>(&bih.bitcount), sizeof(bih.bitcount));
  file.read(reinterpret_cast<char *>(&bih.compression), sizeof(bih.compression));
  file.read(reinterpret_cast<char *>(&bih.sizeimage), sizeof(bih.sizeimage));
  file.read(reinterpret_cast<char *>(&bih.xpelspermeter), sizeof(bih.xpelspermeter));
  file.read(reinterpret_cast<char *>(&bih.ypelspermeter), sizeof(bih.ypelspermeter));
  file.read(reinterpret_cast<char *>(&bih.colorsused), sizeof(bih.colorsused));
  file.read(reinterpret_cast<char *>(&bih.colorsimportant), sizeof(bih.colorsimportant));

  /*
   * Od podataka iz drugog zaglavlja koristimo samo informacije
   * o dimenzijama slike.
   */
  width = bih.width;
  height = bih.height;

  /*
   * U zavisnosti od toga koliko bitova informacija se cita po pikselu 
   * (da li samo R, G i B komponenta ili R, G, B i A), alociramo niz 
   * odgovarajuce duzine.
   */
  if (bih.bitcount == 24)
    pixels = new char [3 * bih.width * bih.height];
  else if (bih.bitcount == 32)
    pixels = new char [4 * bih.width * bih.height];
  else {
    std::cerr << "image_read(): Podrzane su samo slike koje po pikselu cuvaju 24 ili 32 bita podataka." << std::endl;
    exit(1);
  }
  assert(pixels != nullptr);
  
  /* Neke bitmape imaju "visak" polja u zaglavlju.
     offsetbits definise odakle pocinju podaci o pikselima. */
  file.read(pixels, sizeof(char)*(bfh.offsetbits-0x36));

  /* Ucitavaju se podaci o pikselima i smestaju u alocirani niz. */
  if (bih.bitcount == 24)
    /*
     * Ako se po pikselu cita 24 bita = 3 bajta informacija, pretpostavljamo 
     * da oni (ta 3 bajta) predstavljaju R, G i B komponentu boje (1 bajt po 
     * komponenti).
     */
    for (i = 0; i < bih.width * bih.height; i++) {
      /*
       * Ovo mozda izgleda cudno, to sto se komponente boje citaju u suprotnom redosledu, 
       * tj. prvo plava, pa zelena, pa crvena, ali tako pise u specifikaciji bmp formata.
       */
      file.read(&b, sizeof(b));
      file.read(&g, sizeof(g));
      file.read(&r, sizeof(r));

      pixels[3 * i] = r;
      pixels[3 * i + 1] = g;
      pixels[3 * i + 2] = b;
    }
  else if (bih.bitcount == 32)
    /*
     * Ako se po pikselu cita 32 bita = 4 bajta informacija, pretpostavljamo 
     * da oni (ta 4 bajta) predstavljaju R, G, B i A komponentu boje (1 bajt po 
     * komponenti).
     */
    for (i = 0; i < bih.width * bih.height; i++) {
      file.read(&b, sizeof(b));
      file.read(&g, sizeof(g));
      file.read(&r, sizeof(r));
      file.read(&a, sizeof(a));

      pixels[4 * i] = r;
      pixels[4 * i + 1] = g;
      pixels[4 * i + 2] = b;
      pixels[4 * i + 3] = a;
    }

  /* Zatvara se fajl. */
  file.close();
}
