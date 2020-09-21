// Your code here! :)
#pragma once
#include <string>

namespace potd { 
	class Student {
	public:
		Student();
		void set_name(std::string newName);
		void set_grade(int newGrade);
		std::string get_name();
		int get_grade();
	private:
		std::string name_;
		int grade_;
	};
}