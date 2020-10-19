#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

int main() {
	int N;
	cin >> N;
	while (N != 0) {
		int max_denom = 98765 / N;
		bool solution = false;
		std::array<int, 10> values = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		while(std::next_permutation(values.begin(), values.end())) {
			int den = values[0] * 10000 + values[1] * 1000 + values[2] * 100 + values[3] * 10 + values[4];
			if (den > max_denom) {
				continue;
			}
			int num = values[5] * 10000 + values[6] * 1000 + values[7] * 100 + values[8] * 10 + values[9];
			if (float(num) / float(den) == float(N)) {
				cout << num << " / " << values[0] << values[1] << values[2] << values[3] << values[4] << " = " << N << endl;
				solution = true;
			}
		}
		if (!solution) {
			cout << "There are no solutions for " << N << "." << endl;
		}
		cin >> N;
		if (N != 0) {
			cout << endl;
		}
	}
	return 0;
}
