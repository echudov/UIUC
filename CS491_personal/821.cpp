#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

const int N = 100;
const int INF = 10000;

int main() {
	int a, b;
	int test = 1;
	while(cin >> a >> b, !(a == 0 && b == 0)) {
		vector<vector<int>> dist(N + 1, vector<int>(N + 1, INF));

		do {
		dist[a][b] = 1;
		} while(cin >> a >> b, !(a == 0 && b == 0));
		for (int i = 1; i <= 1; i++) {
			dist[i][i] = 0;
		}
		for (int k = 1; k <= N; k++) {
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					if (dist[i][j] > dist[i][k] + dist[k][j]) {
						dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
		}
		int sum = 0;
		int count = 0;
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				if (i != j && dist[i][j] != INF) {
					sum += dist[i][j];
					count++;
				}
			}
		}
		cout << "Case "
             << test++
             << ": average length between pages = "
             << setprecision(3)
             << fixed
             << (double)sum / count
             << " clicks"
             << endl;

	}
	
	return 0;
}