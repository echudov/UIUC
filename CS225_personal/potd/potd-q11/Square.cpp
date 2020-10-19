#include <iostream>
#include <string>

#include "Square.h"

Square::Square() {
    name = "mysquare";
    lengthptr = new double;
    *lengthptr = 2.0;
}

Square & Square::operator=(const Square &other) {
	this->name = other.name;
	this->lengthptr = new double(*other.lengthptr);
	return *this;
}

Square Square::operator+(const Square &other) {
	Square toReturn(*this);
	toReturn.name = this->name + other.name;
	*(toReturn.lengthptr) = *(this->lengthptr) + *(other.lengthptr);
	return toReturn;
}

void Square::setName(std::string newName) {
  name = newName;
}

void Square::setLength(double newVal) {
  *lengthptr = newVal;
}

std::string Square::getName() const {
  return name;
}

double Square::getLength() const {
  return *lengthptr;
}

Square::Square(const Square & other) {
    name = other.getName();
    lengthptr = new double;
    *lengthptr = other.getLength();
}

Square::~Square() {
    delete lengthptr;
}
