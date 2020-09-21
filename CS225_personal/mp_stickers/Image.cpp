#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <algorithm>
#include <cmath>

void Image::lighten() {
    for (unsigned int x = 0; x < this->width(); ++x) {
        for (unsigned int y = 0; y < this->height(); ++y) {
            cs225::HSLAPixel &pixel = this->getPixel(x, y);
            pixel.l += 0.1;
            if (pixel.l > 1) {
                pixel.l = 1;
            } 
        }
    }  
}

void Image::lighten(double amount) {
    for (unsigned int x = 0; x < this->width(); ++x) {
        for (unsigned int y = 0; y < this->height(); ++y) {
            cs225::HSLAPixel &pixel = this->getPixel(x, y);
            pixel.l += amount;
            if (pixel.l > 1) {
                pixel.l = 1;
            } 
        }
    }  
}

void Image::darken() {
    for (unsigned int x = 0; x < this->width(); ++x) {
        for (unsigned int y = 0; y < this->height(); ++y) {
            cs225::HSLAPixel &pixel = this->getPixel(x, y);
            pixel.l -= 0.1;
            if (pixel.l < 0) {
                pixel.l = 0;
            } 
        }
    }  
}

void Image::darken(double amount) {
    for (unsigned int x = 0; x < this->width(); ++x) {
        for (unsigned int y = 0; y < this->height(); ++y) {
            cs225::HSLAPixel &pixel = this->getPixel(x, y);
            pixel.l -= amount;
            if (pixel.l < 0) {
                pixel.l = 0;
            } 
        }
    }  
}

void Image::saturate() {
    for (unsigned int x = 0; x < this->width(); ++x) {
        for (unsigned int y = 0; y < this->height(); ++y) {
            cs225::HSLAPixel &pixel = this->getPixel(x, y);
            pixel.s += 0.1;
            if (pixel.s > 1) {
                pixel.s = 1;
            } 
        }
    }  
}

void Image::saturate(double amount) {
    for (unsigned int x = 0; x < this->width(); ++x) {
        for (unsigned int y = 0; y < this->height(); ++y) {
            cs225::HSLAPixel &pixel = this->getPixel(x, y);
            pixel.s += amount;
            if (pixel.s > 1) {
                pixel.s = 1;
            } 
        }
    }  
}

void Image::desaturate() {
    for (unsigned int x = 0; x < this->width(); ++x) {
        for (unsigned int y = 0; y < this->height(); ++y) {
            cs225::HSLAPixel &pixel = this->getPixel(x, y);
            pixel.s -= 0.1;
            if (pixel.s < 0) {
                pixel.s = 0;
            } 
        }
    }  
}

void Image::desaturate(double amount) {
    for (unsigned int x = 0; x < this->width(); ++x) {
        for (unsigned int y = 0; y < this->height(); ++y) {
            cs225::HSLAPixel &pixel = this->getPixel(x, y);
            pixel.s -= amount;
            if (pixel.s < 0) {
                pixel.s = 0;
            } 
        }
    }  
}

void Image::grayscale() {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel &pixel = this->getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }
}

void Image::illinify() {
  double orange = 11;
  double blue = 216;
  for (unsigned int x = 0; x < this->width(); x++) {
    for (unsigned int y = 0; y < this->height(); y++) {
      cs225::HSLAPixel &pixel = this->getPixel(x, y);

      if (std::min(std::abs(pixel.h - orange), std::abs(360 - orange - pixel.h)) < 
          std::min(std::abs(pixel.h - blue), std::abs(360 - blue - pixel.h))) {
        pixel.h = orange;
      }
      else {
        pixel.h = blue;
      }
    }
  }
}

void Image::rotateColor(double degrees) {
    for (unsigned int x = 0; x < this->width(); ++x) {
        for (unsigned int y = 0; y < this->height(); ++y) {
            cs225::HSLAPixel &pixel = this->getPixel(x, y);
            pixel.h += degrees;
            pixel.h = fmod(pixel.h + 360, 360);
            if (pixel.s < 0) {
                pixel.s = 0;
            } 
        }
    }  
}

void Image::scale(double factor) {
    Image *temp = new Image(*this);
    this->resize(this->width() * factor, this->height() * factor);
    for (unsigned int x = 0; x < this->width(); ++x) {
        for (unsigned int y = 0; y < this->height(); ++y) {
            cs225::HSLAPixel *toReplace = new cs225::HSLAPixel(temp->getPixel(int(float(x) / factor), int(float(y) / factor)));
            this->getPixel(x, y) = *toReplace;
            delete toReplace;
        }
    }
    delete temp;

}

void Image::scale(unsigned w, unsigned h) {
    this->scale(std::min(float(w) / float(this->width()), float(h) / float(this->height())));
}
