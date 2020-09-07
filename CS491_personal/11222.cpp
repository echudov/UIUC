#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

typedef set<int> si;

int main() {
	int T;
	cin >> T;

	si friends[T][3];

	for (int i = 0; i < T * 3; ++i) {
		int size;
		cin >> size;
		for (int j = 0; j < size; j++) {
			int current_problem;
			cin >> current_problem;
			friends[i / 3][i % 3].insert(current_problem);
		}
	
}
	for (int t = 0; t < T; ++t) {
		si& first = friends[t][0];
		si& second = friends[t][1];
		si& third = friends[t][2];

		for (auto it = first.begin(); it != first.end();) {
			// compare to second
			bool found = false;
			auto it2 = second.find(*it);
			if (it2 != second.end()) {
				found = true;
				second.erase (it2);
			}
			// compre to third
			auto it3 = third.find(*it);
			if (it3 != third.end()) {
				found = true;
				third.erase (it3);
			}
			if (found) {
				first.erase (it++);
			} else {
				it++;
			}
		}

		for (auto it2 = second.begin(); it2 != second.end();) {
			auto it3 = third.find(*it2);
			if (it3 != third.end()) {
				third.erase (it3);
				second.erase (it2++);
			} else {
				it2++;
			}
		}

		int max = std::max({first.size(), second.size(), third.size()});

		cout << "Case #" << t + 1 << ":" << endl;
		if (first.size() == max) {
			cout << 1 << " " << max;
			for (int element : first) {
				cout << " " << element;
			}
			cout << endl;
		}
		if (second.size() == max) {
			cout << 2 << " " << max;
			for (int element : second) {
				cout << " " << element;
			}
			cout << endl;
		}
		if (third.size() == max) {
			cout << 3 << " " << max;
			for (int element : third) {
				cout << " " << element;
			}
			cout << endl;
		}
	}
}