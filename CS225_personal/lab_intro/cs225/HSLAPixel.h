/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#pragma once

#include <iostream>
#include <sstream>

namespace cs225 {
    class HSLAPixel {
        public:
            double h; // hue
            double s; // saturation
            double l; // luminance
            double a; // alpha

            HSLAPixel();
            HSLAPixel(double hue, double saturation, double luminance);
            HSLAPixel(double hue, double saturation, double luminance, double alpha);
    };
}
