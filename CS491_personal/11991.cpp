#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, vi> umivi;

int main() {
	int n, m;
	while (cin >> n >> m) {
		vi array(n);
		umii counts;
		umivi occurrences;
		for (int i = 0; i < n; i++) {
			cin >> array[i];
			counts[array[i]] = counts[array[i]] + 1;
		}
		for (const auto &element : counts) {
			vi tracker(element.second);
			occurrences[element.first] = tracker;
		}
		for (int i = 0; i < n; i++) {
			counts[array[i]]--;
			occurrences[array[i]][counts[array[i]]]	= i;		
		}
		vi toprint(m);
		for (int query = 0; query < m; ++query) {
			int k, v;
			cin >> k >> v;
			vi &positions = occurrences[v];
			if (positions.size() < k) { 
				toprint[query] = 0;
			} 
			else {
				toprint[query] = positions[positions.size() - k] + 1;
			}
		}
		for (int i : toprint) {
			cout << i << endl;
		}
	}
	return 0;
}