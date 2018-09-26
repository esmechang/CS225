#include "StickerSheet.h"
#include <string>
#include "Image.h"
#include "cs225/PNG.h"
using namespace cs225;

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
  array = new Image*[max];
  original = new Image(picture);
  x_ = new unsigned[max];
  y_ = new unsigned[max];
  max_ = max;

  for (unsigned int i = 0; i < max_; i++) {
    array[i] = NULL;
    x_[i] = 0;
    y_[i] = 0;
  }
}

StickerSheet::StickerSheet(const StickerSheet &other) {
  copy(other);
}

void StickerSheet::copy(const StickerSheet &other) {
  original = new Image(*other.original);
  max_ = other.max_;
  // numStickers = other.numStickers;
  x_ = new unsigned[max_];
  y_ = new unsigned[max_];
  array = new Image *[max_];

  for (unsigned int i = 0; i < max_; i++) {
    if (other.array[i] != NULL) {
      array[i] = new Image (*other.array[i]);
      x_[i] = other.x_[i];
      y_[i] = other.y_[i];
    } else {
      array[i] = NULL;
    }
  }
}

StickerSheet::~StickerSheet() {
  destroy();
}

void StickerSheet::destroy() {
  if (array != NULL) {
    for (unsigned i = 0; i < max_; i++) {
        delete array[i];
        array[i] = NULL;
    }
  }
  delete[] array;
  delete[] x_;
  delete[] y_;

  y_ = NULL;
  x_ = NULL;
  array = NULL;
}

const StickerSheet &StickerSheet::operator=(const StickerSheet &other) {
  if (this != &other) {
    destroy();
    copy(other);
  }
  return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
  if (max == max_) {
    return;
  }
  Image **temp = new Image*[max];
  unsigned * otherx = new unsigned[max];
  unsigned * othery = new unsigned[max];

  // changing and setting max
  if (max > max_) {
    for (unsigned int i = 0; i < max_; i++) {
      temp[i] = array[i];
      otherx[i] = x_[i];
      othery[i] = y_[i];
    }
    for (unsigned int i = max_; i < max_; i++) {
      temp[i] = NULL;
      otherx[i] = 0;
      othery[i] = 0;
    }
    max_ = max;
  } else {
    for (unsigned int i = 0; i < max_; i++) {
      temp[i] = array[i];
      otherx[i] = x_[i];
      othery[i] = y_[i];
    }
    for (unsigned i = max; i < max_; i++) {
      delete array[i];
    }
  }
  // new max
  delete[] array;
  array = temp;
  x_ = otherx;
  y_ = othery;
  max_ = max;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
  for (unsigned i = 0; i < max_; i++) {
    if (array[i] == NULL) {
      array[i] = new Image(sticker);
      // position of sticker
      x_[i] = x;
      y_[i] = y;
      return i;
    }
  }
  return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
  if (index <= max_) {
    return false;
  }
  if (array[index]->width() == 0 && array[index]->height() == 0) {
    return false;
  }
  indices[index] = x;
  indices[index] = y;
  return true;
}

Image * StickerSheet::getSticker(unsigned index) const {
  if (index < max_ && array[index] != NULL) {
    return index[array];
  }
  return NULL;

  // Image * thing;
  // if (index <= 0 || index <= max_-1) {
  //   thing = NULL;
  //   return thing;
  // }
  // if ((index[array].width() == 0) && (index[array].height() == 0)) {
  //   thing = NULL;
  //   return thing;
  // }
  // thing = array[index];
  // return thing;
}

void StickerSheet::removeSticker(unsigned index) {
  if ((index > max_-1) && array[index] == NULL) {
    return;
  }
  delete array[index];
  array[index] = NULL;
  x_[index] = 0;
  y_[index] = 0;
  return;
}

Image StickerSheet::render() const {
  unsigned int picWidth = original->width();
  unsigned int picHeight = original->height();

  for (unsigned int i = 0; i < max_; i++) {
    if (array[i] != NULL) {
      // setting new image dimensions
      unsigned width = x_[i] + array[i]->width();
      unsigned height = y_[i] + array[i]->height();

      if (width > picWidth) {
        picWidth = width;
      }
      if (height > picHeight) {
        picHeight = height;
      }
    }
  }
  Image *output = new Image(*original);
  output->resize(picWidth, picHeight);

  // positioning stickers
  for (unsigned int i = 0; i < max_; i++) {
    if (array[i] != NULL) {
      for (unsigned int a = x_[i]; a < x_[i] + array[i]->width(); a++) {
        for (unsigned int b = y_[i]; b < y_[i] + array[i]->height(); b++) {
          HSLAPixel &photo = output->getPixel(a, b);
          HSLAPixel &newSticker = array[i]->getPixel(a-x_[i], b-y_[i]);
          if (newSticker.a != 0) {
            photo = newSticker;
          }
        }
      }
    }
  }
  Image result = *output;
  delete output;
  return result;
}
