#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <random>
#include <math.h>
#include <time.h>

void rotate(std::string inputFile, std::string outputFile) {
  cs225::PNG *input = new cs225::PNG();
  input->readFromFile(inputFile);
  unsigned int width = input->width();
  unsigned int height = input->height();

  cs225::PNG *output = new cs225::PNG(width, height);

  for (unsigned int x = 0; x < width; ++x) {
    for (unsigned int y = 0; y < height; ++y) {
      cs225::HSLAPixel inPixel = input->getPixel(x, y);
      cs225::HSLAPixel &outPixel = output->getPixel(width - x - 1, height - y - 1);
      outPixel = inPixel;
    }
  }

  output->writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  // TODO: Part 3

  srand(time(NULL));
  unsigned int centerQuantity = 5;
  unsigned int totalCenters = centerQuantity + 4;
  int centerX[totalCenters], centerY[totalCenters];
  cs225::HSLAPixel *centers[totalCenters];
  for (unsigned int i = 0; i < 4; i++) {
    unsigned int x, y;
    if (i % 2 == 0) {
      x = 0;
    } else {
      x = width - 1;
    }
    if (i / 2 == 0) {
      y = 0;
    } else {
      y = height - 1;
    }
    centerX[i] = x;
    centerY[i] = y;
    centers[i] = new cs225::HSLAPixel(std::rand() % 360, 0.5, 1);
  }
  for (unsigned int c = 4; c < totalCenters; ++c) {
    centerX[c] = std::rand() % width;
    centerY[c] = std::rand() % height;
    centers[c] = new cs225::HSLAPixel(std::rand() % 360, 0.5, 1);
    // std::cout << "c: " << c << " X: " << centerX[c] << " Y: " << centerY[c] << std::endl;
  }

  cs225::PNG *art = new cs225::PNG(width, height);
  for (unsigned int x = 0; x < width; ++x) {
    for (unsigned int y = 0; y < height; ++y) {
      cs225::HSLAPixel &pixel = art->getPixel(x, y);
      // Takes the weighted average of the distances between all of the colors
      pixel.h = 0;
      double distances[totalCenters];
      double distance_sum = 0;
      double closest_distance = width + height; // since the distance can't be more than the l1 norm of the endpoints
      
      for (unsigned int c = 0; c < totalCenters; ++c) {
        distances[c] = std::sqrt(std::pow(x - centerX[c], 2) + std::pow(y - centerY[c], 2));
        distance_sum += distances[c];
        if (distances[c] < closest_distance) {
          closest_distance = distances[c];
        }
      }
      pixel.l = 0.5 - 0.004 * closest_distance;
      pixel.s = 1;

      for (unsigned int c = 0; c < totalCenters; ++c) {
        pixel.h += (centers[c]->h) * ((distance_sum - distances[c]) / distance_sum) / centerQuantity;
      }
      // std::cout << "x: " << x << " y: " << y << " h: " << pixel.h << std::endl;
    }
  }

  return *art;
}