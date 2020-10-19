#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

int main() {
	int N;
	string line;
	cin >> N;

	while (N != 0) {
		int elem;
		cin >> elem;
		while(elem != 0) {
			stack<int> starting_train;
			stack<int> station;
			stack<int> inputs;
			inputs.push(elem);
			for (int i = 1; i < N; i++) {
				cin >> elem;
				inputs.push(elem);
			}
			for (int i = 1; i <= N; ++i) {
				starting_train.push(i);
			}
			while(inputs.size() != 0) {
				int car = inputs.top();
				station.push(car);
				while (station.size() != 0 && station.top() == starting_train.top()) {
					starting_train.pop();
					station.pop();
				}
				inputs.pop();
			}
			if (starting_train.size() > 0) {
				cout << "No" << endl;
			} else {
				cout << "Yes" << endl;
			}
			cin >> elem;
		}
		cout << endl;
		cin >> N;

	}

	return 0;
}