#include <cmath>
#include <iterator>
#include <iostream>
#include <vector>

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
double ImageTraversal::calculateDelta(const HSLAPixel &p1, const HSLAPixel &p2)
{
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180)
  {
    h = 360 - h;
  }
  h /= 360;

  return sqrt((h * h) + (s * s) + (l * l));
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(ImageTraversal *traversal, Point &start, double &tolerance, PNG &image) : tolerance_(tolerance),
                                                                                                             start_(start),
                                                                                                             image_(image)
{
  traversal_ = traversal;
  width_ = image.width();
  height_ = image.height();
  visited_.resize(width_ * height_, false);
  current_ = traversal_->peek();
  for (unsigned int i = 0; i < width_ * height_; ++i)
  {
    visited_[i] = false;
  }
}

ImageTraversal::Iterator::Iterator()
{
  traversal_ = NULL;
  current_ = Point(0, 0);
}

bool ImageTraversal::Iterator::seen(const Point &toCheck) const
{
  return visited_[toCheck.x * height_ + toCheck.y];
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator &ImageTraversal::Iterator::operator++()
{
  /** @todo [Part 1] */
  if (!traversal_->empty())
  {
    traversal_->pop();
    visited_[current_.x * height_ + current_.y] = true;
    Point right(current_.x + 1, current_.y);
    Point below(current_.x, current_.y + 1);
    Point left(current_.x - 1, current_.y);
    Point above(current_.x, current_.y - 1);

    while (!traversal_->empty() && seen(Point(traversal_->peek().x, traversal_->peek().y)))
    {
      traversal_->pop();
    }
    if (isValid(right, width_, height_) &&
        calculateDelta(image_.getPixel(right.x, right.y), image_.getPixel(start_.x, start_.y)) <= tolerance_ &&
        !seen(right))
    {
      traversal_->add(right);
    }
    if (isValid(below, width_, height_) &&
        calculateDelta(image_.getPixel(below.x, below.y), image_.getPixel(start_.x, start_.y)) <= tolerance_ &&
        !seen(below))
    {
      traversal_->add(below);
    }
    if (isValid(left, width_, height_) &&
        calculateDelta(image_.getPixel(left.x, left.y), image_.getPixel(start_.x, start_.y)) <= tolerance_ &&
        !seen(left))
    {
      traversal_->add(left);
    }
    if (isValid(above, width_, height_) &&
        calculateDelta(image_.getPixel(above.x, above.y), image_.getPixel(start_.x, start_.y)) <= tolerance_ &&
        !seen(above))
    {
      traversal_->add(above);
    }

    if (!traversal_->empty())
    {
      current_ = traversal_->peek();
    }
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*()
{
  /** @todo [Part 1] */
  return current_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other)
{
  /** @todo [Part 1] */
  bool thisEmpty = false, otherEmpty = false;

  if (traversal_ == NULL)
    thisEmpty = true;
  if (other.traversal_ == NULL)
    otherEmpty = true;

  if (!thisEmpty)
    thisEmpty = traversal_->empty();
  if (!otherEmpty)
    otherEmpty = other.traversal_->empty();

  return !(thisEmpty && otherEmpty);
}

bool ImageTraversal::Iterator::isValid(const Point &p, const unsigned int width, const unsigned int height)
{
  return (p.x >= 0 && p.x < width) && (p.y >= 0 && p.y < height);
}