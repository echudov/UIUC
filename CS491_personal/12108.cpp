#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;

void increment(vi &A, vi &B, vi &C, int n, int asleep);
int sleeping_count(vi &A, vi &B, vi &C, int n);

int main() {
	vvi studentsA;
	vvi studentsB;
	vvi studentsC;
	vi N;
	int n;
	cin >> n;
	while (n != 0) {
		N.push_back(n);
		vector<int> A(n), B(n), C(n);
		for (int i = 0; i < n; i++) {
			cin >> A[i] >> B[i] >> C[i];
		}
		studentsA.push_back(A);
		studentsB.push_back(B);
		studentsC.push_back(C);
		cin >> n;
	}

	for (int i = 0; i < N.size(); i++) {
		vi &A = studentsA[i];
		vi &B = studentsB[i];
		vi &C = studentsC[i];
		vi original_condition = studentsC[i];
		int &n = N[i];
		int steps = 1;

		int asleep;
		while(true) {
			asleep = sleeping_count(A, B, C, n);
			if (asleep == 0) {
				cout << "Case " << i + 1 << ": " << steps << endl;;
				break;
			} else if (steps > 1 && C == original_condition) {
				cout << "Case " << i + 1 << ": " << -1 << endl;
				break;
			}
			increment(A, B, C, n, asleep);
			steps++;
		}

	}

	return 0;
}

void increment(vi &A, vi &B, vi &C, int n, int asleep) {
	for (int i = 0; i < n; i++) {
		if (C[i] < A[i]) {
			C[i]++;
		} else if (C[i] == A[i]) {
			if (asleep * 2 > n) {
				C[i]++;
			} else {
				C[i] = 1;
			}
		} else if (C[i] < A[i] + B[i]) {
			C[i]++;
		} else {
			C[i] = 1;
		}
	}
}

int sleeping_count(vi &A, vi &B, vi &C, int n) {
	int toreturn = 0;
	for (int i = 0; i < n; i++) {
		if (C[i] > A[i]) {
			toreturn++;
		}
	}
	return toreturn;
}