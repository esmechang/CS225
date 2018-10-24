#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  pos = NULL;
}

ImageTraversal::Iterator::Iterator(ImageTraversal *ptr) {
  pos = ptr;
  pos->seen[pos->pt.x][pos->pt.y] = 1;
}

ImageTraversal::ImageTraversal(const PNG &png, const Point &beginning, double tolerance):pt(beginning), picture(png) {
  pw = picture.width();
  ph = picture.height();
  toler = tolerance;
  seen = new int *[pw];
  for (unsigned i = 0; i < pw; i++) {
    seen[i] = new int[ph];
  }
  for (unsigned i = 0; i < pw; i++) {
    for (unsigned j = 0; j < ph; j++) {
      seen[i][j] = 0;
    }
  }
  seen[pt.x][pt.y] = 1;
}

bool ImageTraversal::check(Point checker) {
  HSLAPixel &pics1 = (picture.getPixel(checker.x, checker.y));
  HSLAPixel &pics2 = (picture.getPixel(pt.x, pt.y));
  if (calculateDelta(pics1, pics2) < toler) {
    return true;
  }
  return false;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  Point first = pos->pop();
  Point pt1 = Point(first.x+1, first.y);
  Point pt2 = Point(first.x, first.y+1);
  Point pt3 = Point(first.x-1, first.y);
  Point pt4 = Point(first.x, first.y-1);

  if (first.x < pos->pw - 1) {
    if (pos->seen[first.x+1][first.y] == 0) {
      if (pos->check(pt1)) {
        pos->add(pt1);
      }
    }
  }
  if (first.y < pos->ph - 1) {
    if (pos->seen[first.x][first.y+1] == 0) {
      if (pos->check(pt2)) {
        pos->add(pt2);
      }
    }
  }
  if (first.x > 0) {
    if (pos->seen[first.x-1][first.y] == 0) {
      if (pos->check(pt3)) {
        pos->add(pt3);
      }
    }
  }
  if (first.y > 0) {
    if (pos->seen[first.x][first.y-1] == 0) {
      if (pos->check(pt4)) {
        pos->add(pt4);
      }
    }
  }
  while (1) {
    if (pos->empty()) {
      pos = NULL;
      break;
    }
    Point curr = pos->peek();
    if (pos->seen[curr.x][curr.y] == 1) {
      pos->pop();
      continue;
    }
    pos->seen[curr.x][curr.y] = 1;
    break;
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  if (pos != NULL) {
    return pos->peek();
  } else {
    return Point();
  }
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if (this->pos == other.pos) {
    return false;
  } else {
    return true;
  }
}

ImageTraversal::~ImageTraversal() {
  for (unsigned i = 0; i < pw; i++) {
    delete seen[i];
  }
  delete seen;
}
