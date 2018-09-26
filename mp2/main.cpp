#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image clouds;
  clouds.readFromFile("clouds.png");
  clouds.scale(6.0);
  Image onedirection;
  onedirection.readFromFile("onedirection.png");
  onedirection.scale(2.0);
  Image bts;
  bts.readFromFile("bts.png");
  bts.scale(2.0);
  Image christianyu;
  christianyu.readFromFile("christianyu.png");
  christianyu.scale(2.0);

  StickerSheet sheet(clouds, 5);
  sheet.addSticker(onedirection, 3000, 2000);
  sheet.addSticker(bts, 3000, 3000);
  sheet.addSticker(christianyu, 5000, 2000);
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image output;
  output= sheet.render();
  output.writeToFile("myImage.png");

  return 0;
}
