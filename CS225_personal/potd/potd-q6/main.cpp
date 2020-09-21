// Your code here! :)
#include <iostream>
#include "student.h"
#include "q6.h"

int main() {
	potd::Student *sally = new potd::Student();
	sally->set_name("Sally");
	sally->set_grade(6);

	std::cout << sally->get_name() << " is in grade " << sally->get_grade() << "." << std::endl;
	graduate(*sally);
	std::cout << sally->get_name() << " is in grade " << sally->get_grade() << "." << std::endl;
	return 0;
}