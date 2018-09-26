/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

 #include "Image.h"
 #include <string>
 #include <iostream>
 using namespace std;

 class StickerSheet : public Image {
 public:
   StickerSheet(const Image &picture, unsigned max);
   StickerSheet(const StickerSheet &other);
   ~StickerSheet();
   const StickerSheet &operator = (const StickerSheet &other);
   void changeMaxStickers(unsigned max);
   int addSticker(Image &sticker, unsigned x, unsigned y);
   bool translate(unsigned index, unsigned x, unsigned y);
   Image * getSticker(unsigned index) const;
   void removeSticker(unsigned index);
   Image render() const;
   void copy(const StickerSheet &other);
   void destroy();
   unsigned * indices;
   unsigned int numIndices;
   unsigned int numStickers;

 private:
   Image **array;
   unsigned *xs;
   unsigned *ys;
   unsigned max_;
   Image *original;
 };
