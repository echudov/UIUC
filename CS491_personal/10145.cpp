#include <iostream>
#include <map>
#include <tuple>
#include <string>
#include <set>

using namespace std;

typedef tuple<int, int> tii;

int main() {
	char mode;
	int trid, item;
	cin >> mode;
	map<tii, char> locks;
	set<int> denied_transactions;
	while(mode != '#') {
		cin >> trid >> item;
		if (denied_transactions.find(trid) != denied_transactions.end()) {
			cout << "IGNORED" << endl;
			continue;
		} else if (locks[make_tuple(trid, item) == ""]
	}

	return 0;
}