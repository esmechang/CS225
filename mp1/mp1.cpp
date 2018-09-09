#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>



void rotate(std::string inputFile, std::string outputFile) {
  PNG* photo = new PNG();
  photo->readFromFile(inputFile);
  unsigned int w = photo->width();
  unsigned int h = photo->height();
  PNG* output = new PNG(w, h);

  for (unsigned int x = 0; x < w; x++) {
    for (unsigned int y = 0; y < h; y++) {
      HSLAPixel &a = photo->getPixel(w-x-1, h-y-1);
      HSLAPixel &b = output->getPixel(x, y);
      b = a;
    }
  }
  output->writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png = PNG(width, height);

  for (unsigned int x = 0; x < width; x++) {
    for (unsigned int y = 0; y < height; y++) {
      HSLAPixel *gradient = new HSLAPixel(196 + x/7, 1, 0.5);
      HSLAPixel &output = png.getPixel(x, y);
      output = *gradient;
    }
  }

  // for (unsigned int x = 0; x < width; x++) {
  //   for (unsigned int y = 0; y < height; y++) {
  //     HSLAPixel &output = png.getPixel(x, y);
  //     output = HSLAPixel(196 + (sqrt(x*x + y*y))/(width/50), 1, 0.5);
  //   }
  // }
  //
  // for (unsigned int x = 0; x < width; x++) {
  //   for (unsigned int y = 0; y < height; y++) {
  //     HSLAPixel &output = png.getPixel(x, y);
  //     output = HSLAPixel(196 + x/(width/40), 1, 0.5);
  //   }
  // }

  // for (unsigned int x = 0; x < width; x++) {
  //   for (unsigned int y = 0; y < height; y++) {
  //     HSLAPixel &output = png.getPixel(x, y);
  //     output = *color2;
  //   }
  // }

  return png;
}
