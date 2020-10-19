#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned short int usi;
typedef tuple<int, int> tii;
typedef vector<vector<tii>> vvtii;
typedef vector<tii> vtii;

bool possible(int row, int col, vtii &currentArrangement, int placed) {
	for (int i = 0; i < placed; ++i) {
		auto &elem = currentArrangement[i];
		if (row == get<0>(elem)
			|| col == get<1>(elem)
			|| row + col == get<0>(elem) + get<1>(elem) 
			|| col - row == get<1>(elem) - get<0>(elem)) {
			return false;
		}
	}
	return true;
}

void solve(vtii currentArrangement, int queensPlaced, vvtii &solutions) {
	if (queensPlaced == 8) {
		solutions.push_back(currentArrangement);
		return;
	}
	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			if (possible(row, col, currentArrangement, queensPlaced)) {
				currentArrangement[queensPlaced] = make_tuple(row, col);
				solve(currentArrangement, queensPlaced + 1, solutions);
			}
		}
	}
}

int main() {
	int tests;
	cin >> tests;
	string line;
	for (int i = 0; i < tests; ++i) {
		int f, s;
		cin >> f >> s;
		tii first(f - 1, s - 1);
		vvtii solutions;
		vtii current(8);
		current[0] = first;
		solve(current, 1, solutions);
		cout << "SOLN       COLUMN" << endl;
		cout << " #      1 2 3 4 5 6 7 8" << endl << endl;

		for (auto elem : solutions) {
			std::sort(elem.begin(), elem.end(), [](tii a, tii b) {
       			return get<1>(a) < get<1>(b);   
    		});
		}
		std::sort(solutions.begin(), solutions.end(), [](vtii a, vtii b) {
			for (int i = 0; i < 8; ++i) {
				if (a[i] < b[i]) {
					return true;
				} else if (a[i] > b[i]) {
					return false;
				}
			}
			return false;
		});
		for (int i = 0; i < solutions.size(); ++i) {
			cout << " " << i + 1 << "      ";
			for (tii &elem : solutions[i]) {
				cout << get<0>(elem) + 1 << " ";
			}
			cout << endl;
		}
	}

	return 0;
}