#include <iostream>
#include <tuple>

using namespace std;

void build(int a[], int v, int tl, int tr, tuple<int, int> t[]) {
	if (tl == tr) {
		t[v] = make_tuple(a[tl], 1);
	} else {
		int tm = (tl + tr) / 2;
		build(a, v * 2, tl, tm, t);
		build(a, v * 2 + 1, tm, tr, t);
		auto tv2 = t[v*2];
		auto tv21 = t[v * 2 + 1];
		if (get<0>(tv2) == get<0>(tv21)) {
			t[v] = make_tuple(get<0>(tv21), get<1>(tv21) + get<1>(tv2));
		} else if (get<1>(tv2) > get<1>(tv21)) {
			t[v] = tv2;
		} else {
			t[v] = tv21;
		}
	}
}

tuple<int, int> mode(int v, int tl, int tr, int l, int r, tuple<int, int> t[]) {
	if (l > r) 
		return make_tuple(0, 0);
	if (l == tl && r == tr) {
		return t[v];
	}
	int tm = (tl + tr) / 2;
	auto model = mode(v * 2, tl, tm, l, min(r, tm), t);
	auto moder = mode(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, t);
	if (get<0>(model) == get<0>(moder)) {
		return make_tuple(get<0>(model), get<1>(model) + get<1>(moder));
	} else if (get<1>(moder) > get<1>(model)) {
		return moder;
	} else {
		return model;
	}
}

int main() {
	int n, q;
	while(cin >> n >> q) {
		tuple<int, int> st[n * 4];
		int arr[n];
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
		}
		int l, r;
		for (int i = 0; i < q; ++i) {
			cin >> l >> r;
			cout << get<1>(mode(0, l, r, l, r, st)) << endl;
		}


	}

	return 0;
}