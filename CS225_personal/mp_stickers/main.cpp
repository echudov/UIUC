#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image god; god.readFromFile("god.png");
  Image evans; evans.readFromFile("gcevans.png");
  Image i; i.readFromFile("i.png");
  Image course; course.readFromFile("cs225.png");

  StickerSheet sheet(god, 3);
  evans.scale(2.3);
  course.scale(1.5);
  sheet.addSticker(evans, 850, 250);
  sheet.addSticker(i, 1700, 1200);
  sheet.addSticker(course, 150, 1600);
  Image myImage = sheet.render();
  myImage.writeToFile("myImage.png");
  return 0;
}
