#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <tuple>
#include <iomanip>

using namespace std;

typedef vector<tuple<char, tuple<int, int>>> vtcii;

template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

bool success(float starting_fuel, const vtcii &events) {
	float consumption;
	float leak = 0;
	float current_fuel = starting_fuel;
	int current_distance = 0;
	for (auto event : events) {
		char type = get<0>(event);
		auto &values = get<1>(event);
		if (type == 'F') {
			consumption = get<1>(values) / float(100);
			current_fuel -= (leak + consumption) * (get<0>(values) - current_distance);
			current_distance = get<0>(values);
		} else if (type == 'L') {
			current_fuel -= (leak + consumption) * (get<0>(values) - current_distance);
			leak++;
			current_distance = get<0>(values);
		} else if (type == 'M') {
			current_fuel -= (leak + consumption) * (get<0>(values) - current_distance);
			leak = 0;
			current_distance = get<0>(values);
		} else if (type == 'A') {
			current_fuel -= (leak + consumption) * (get<0>(values) - current_distance);
			if (current_fuel < 0) {
				return false;
			}
			current_fuel = starting_fuel;
			current_distance = get<0>(values);
		} else {
			current_fuel -= (leak + consumption) * (get<0>(values) - current_distance);
		}
		if (current_fuel < 0) {
			return false;
		}
	}
	return true;
}

int main() {
	vtcii events;
	string line;
	getline(cin, line);
	while (line != "0 Fuel consumption 0") {
		vector<string> input;
		do {
			input = split(line, ' ');
			cout << input[1] << endl;
			if (input[1] == "Fuel") {
				events.push_back(make_tuple('F', make_tuple(stoi(input[0]), stoi(input[3]))));
			} else if (input[1] == "Leak") {
				events.push_back(make_tuple('L', make_tuple(stoi(input[0]), -1)));
			} else if (input[1] == "Mechanic") {
				events.push_back(make_tuple('M', make_tuple(stoi(input[0]), -1)));
			} else if (input[1] == "Gas") {
				events.push_back(make_tuple('A', make_tuple(stoi(input[0]), -1)));
			} else {
				events.push_back(make_tuple('G', make_tuple(stoi(input[0]), -1)));
			}
			getline(cin, line);
		} while (input[1] != "Goal");
		float upper = 1000;
		float lower = 0;
		float mid = (upper + lower) / 2;
		while (upper - lower > 0.001) {
			if (success(mid, events)) {
				upper = mid;
				mid = (upper + lower) / 2;
			} else {
				lower = mid;
			}
		}
		cout << setprecision(3) << fixed << lower << endl;
		getline(cin, line);
		events.clear(); 
	}
	return 0;
}