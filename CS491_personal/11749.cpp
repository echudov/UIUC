#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<tuple<int, int>>> vvii;
typedef tuple<int, int> tii;

long long dfs(vvii &G, int start, vector<bool> &seen, long long ppi) {
	seen[start] = true;
	for (int v : G[start]) {
		if (!seen[v]) {
			dfs(G, v, seen, ppi);
		}
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	vector<int> results;
	while (n != 0) {
		vvii G(n);
		for (int i = 0; i < m; i++) {
			int start, end, ppa;
			cin >> start >> end >> ppa;
			G[start - 1].push_back(make_tuple(end - 1, ppa));
			G[end - 1].push_back(make_tuple(start - 1, ppa));
		}
	}

	return 0;
}