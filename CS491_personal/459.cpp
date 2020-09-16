#include <iostream>
#include <vector>
#include <map>

using namespace std;

void dfs(vector<vector<int>> &G, int start, bool *seen) {
	seen[start] = true;
	for (int out : G[start]) {
		if (seen[out] == false) {
			dfs(G, out, seen);
		}
	}
}

void TrimSpaces( string& str)
{
    size_t startpos = str.find_first_not_of(" \t");
    size_t endpos = str.find_last_not_of(" \t");
 
    if(( string::npos == startpos ) || ( string::npos == endpos))
    {
        str = "";
    }
    else
        str = str.substr( startpos, endpos-startpos+1 );
}

int main() {
	int tests;
	cin >> tests;
	int tests2 = tests;
	int results[tests];
	string input;
	getline(cin, input);
	while (tests--) {
		char maxVertex;
		cin >> maxVertex;
		int vertices = maxVertex - 'A' + 1;
		vector<vector<int>> g(vertices);
		getline(cin, input);
		while (getline(cin, input)) {
			TrimSpaces(input);

			if (input.size() == 0) {
				break;
			}
			g[input[0] - 'A'].push_back(input[1] - 'A');
			g[input[1] - 'A'].push_back(input[0] - 'A');
		}

		bool visited[vertices] = { false };
		int count = 0;
		for (int i = 0; i < vertices; ++i) {
			if (visited[i] == false) {
				count++;
				dfs(g, i, visited);
			}
		}
		results[tests2 - tests - 1] = count;

	}

	for (int i = 0; i < tests2; ++i) {
		cout << results[i] << endl;
		if (i < tests2 - 1) {
			cout << endl;
		}
	}
}