#include <iostream>

using namespace std;

#define inf 10000

int main() {
	int tests;
	scanf("%d", &tests);
	int toPay, N;
	int M[10001], A[101];
	while(tests--) {
		scanf("%d %d", &toPay, &N);
		for (int i = 1; i <= N; i++) {
			scanf("%d", &A[i]);
		}
		for (int i = 1; i < 10000; i++) {
			M[i] = inf;
		}
		M[0] = 0;
		for (int i = 1; i <= N; i++) {
			for (int j = 10000; j > 0; --j) {
				if (j - A[i] >= 0 && M[j - A[i]] + 1 < M[j]) {
					M[j] = M[j - A[i]] + 1;
				}
			}
		}
		int i;
		for (i = toPay; M[i] == inf; i++);

		printf("%d %d\n", i, M[i]);
	}

	return 0;
}