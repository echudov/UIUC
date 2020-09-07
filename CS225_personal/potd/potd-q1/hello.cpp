/* Your code here! */
#include <iostream>
#include <string>

int age = 19;
std::string name = "Elia Chudov";

std::string hello() {
	return "Hello world! My name is " + name + " and I am " + std::to_string(age) + " years old.";
}