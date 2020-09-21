// Your code here! :)
#include <string>
#include "student.h"

potd::Student::Student() {
	name_ = "Sally";
	grade_ = 6;
}

void potd::Student::set_name(std::string newName) {
	name_ = newName;
}

void potd::Student::set_grade(int newGrade) {
	grade_ = newGrade;
}

std::string potd::Student::get_name() {
	return name_;
}

int potd::Student::get_grade() {
	return grade_;
}