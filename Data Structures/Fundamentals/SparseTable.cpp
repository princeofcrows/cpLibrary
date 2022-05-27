#include <iostream>
#define MAXN 100005
#define K 22
using namespace std;

int table[MAXN][K], ara[MAXN];

int callBackFn(int a, int b) {
	return max(a, b);
}

void initSparseTable(int n){
	for (int i=0; i<n; i++) {
		table[i][0] = ara[i];
	}

	for(int j = 1; j <= K; j++) {
		for(int i = 0; i <= n - (1 << j); i++)
			table[i][j] = callBackFn(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
	}
}

int query(int L, int R, int n){
	int ans = 0;
	for(int j = K; j >= 0; j--) {
		if(L + (1<<j) - 1 <= R) {
			ans = callBackFn(ans, table[L][j]);
			L += 1 << j;
		}
	}
	return ans;
}
