#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>
#include <set> 
#include <queue>
#include <cmath>

using namespace std;

#define INF 1000000000

double distance(const pair<int, int> &a, const pair<int, int> &b) {
	return pow(pow(a.first - b.first, 2) + pow(a.second - b.second, 2), 0.5);
}

int main() {
	int T, n, r, x, y;
	cin >> T;
	int t = T;
	while (t--) {
		cin >> n >> r;
		vector<pair<int, int>> coordinates(n);
		vector<map<int, double>> delauney(n);
		for (int i = 0; i < n; ++i) {
			cin >> x >> y;
			coordinates[i] = std::make_pair(x, y);
		}
		std::sort(coordinates.begin(), coordinates.end(), [](pair<int, int> const& l, pair<int, int> const& r) {
			if (l.first < r.second) return true;
			else if (l.first == r.first) return l.second < r.second;
			return false;
		});
		for (int i = 0; i < n - 2; ++i) {
			auto &one = coordinates[i];
			auto &two = coordinates[i + 1];
			auto &three = coordinates[i + 2];
			// 1 & 2
			double dist12 = distance(one, two);
			delauney[i].emplace(i + 1, dist12);
			delauney[i + 1].emplace(i, dist12);
			// 2 & 3
			double dist23 = distance(two, three);
			delauney[i + 1].emplace(i + 2, dist23);
			delauney[i + 2].emplace(i + 1, dist23);
			// 1 & 3
			double dist13 = distance(one, three);
			delauney[i].emplace(i + 2, dist13);
			delauney[i + 2].emplace(i, dist13);
		}

		// prim's algorithm
		priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>> > pq;

		std::vector<double> key(n, INF);
		std::vector<pair<int, double>> parents(n, make_pair(-1, 0));
		std::vector<bool> inMST(n, false);
		pq.push(make_pair(0, 0));
		key[0] = 0;

		while(!pq.empty()) {
			int u = pq.top().second;

			pq.pop();

			inMST[u] = true;

			for (auto &x : delauney[u]) {
				int v = x.first;
				int weight = x.second;

				if (!inMST[v] && key[v] > weight) {
					key[v] = weight;
					pq.push(make_pair(key[v], v));
					parents[v] = make_pair(u, weight);
				}
			}
		}

		double roads = 0; 
		double railways = 0;
		int cities = 1;
		for (int v = 1; v < n; ++v) {
			pair<int, double> u = parents[v];
			if (u.second <= r) {
				roads += u.second;
			} else {
				railways += u.second;
				cities++;
			}
		}
		cout << "Case #" << T - t << ": " << cities << " " << (int)(roads + 0.5) << " " << (int)(railways + 0.5) << endl;
	}

	return 0;
}
