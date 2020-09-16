#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int dfs(vector<vector<int>> &positions, int startX, int startY, int N) {
	if (positions[startX][startY] == 0) {
		return 0;
	}
	int current = 0;
	if (positions[startX][startY] == 1) {
		current += 1;
	}
	positions[startX][startY] = 0;
	current += dfs(positions, min(startX + 1, N - 1), startY, N);
	current += dfs(positions, startX, min(startY + 1, N - 1), N);
	current += dfs(positions, max(startX - 1, 0), startY, N);
	current += dfs(positions, startX, max(startY - 1, 0), N);
	return current;
}

int main() {
	int T, N;
	cin >> T;
	int results[T];
	int test = 0;
	while (T - test > 0) {
		cin >> N;
		char pos;
		vector<vector<int>> positions(N, vector<int>(N, 0));
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				cin >> pos;
				if (pos == '.') {
					continue;
				} else if (pos == 'x') {
					positions[i][j] = 1;
				} else {
					positions[i][j] = 2;
				}
			}
		}
		int count = 0;
		for (int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				if (dfs(positions, i, j, N) > 0) {
					count++;
				}
			}
		}
		results[test++] = count;
	}
	for (int i = 0; i < T; ++i) {
		cout << "Case " << i + 1 << ": " << results[i] << endl;
	}


	return 0;
}