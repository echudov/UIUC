#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

MyColorPicker::MyColorPicker(HSLAPixel mainColor, HSLAPixel secondColor, unsigned spacing) : mainColor(mainColor),
                                                                                             secondColor(secondColor),
                                                                                             spacing(spacing) {}
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y)
{
  if (((x + y) / spacing) % 2 == 0)
  {
    return mainColor;
  }
  else
  {
    return secondColor;
  }
}
