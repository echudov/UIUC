#include <iostream>
#include <string>
#include <list>
#include <sstream>
#include <vector>

using namespace std;

typedef list<string> ls;

int main() {
	vector<string> tests;
	string line = "a" ;
	
	while(line.length() != 0) {
		getline(cin, line);
		tests.push_back("[" + line);
	}

	for (int k = 0; k < tests.size() - 1; k++) {
		string &test = tests[k];
		ls to_concat;

		for (int i = 0; i < test.length(); i++) {
			if (test[i] == '[') {
				int j = i + 1;
				for (; j < test.length(); j++) {
					if (test[j] == '[' || test[j] == ']') {
						break;
					}
				}
				to_concat.push_front(test.substr(i + 1, j - i - 1));
			} else if (test[i] == ']') {
				int j = i + 1;
				for (; j < test.length(); j++) {
					if (test[j] == '[' || test[j] == ']') {
						break;
					}
				}
				to_concat.push_back(test.substr(i + 1, j - i - 1));
			}
		}

		stringstream ss;
		while(!to_concat.empty()) {
			ss << to_concat.front();
			to_concat.pop_front();
		}

		cout << ss.str() << endl;
	}

	return 0;
}