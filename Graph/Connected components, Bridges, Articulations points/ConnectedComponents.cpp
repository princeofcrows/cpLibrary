#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAXN 100005

int n;
vector<int> g[MAXN];
bool used[MAXN];
vector<int> comp;
vector<vector<int> > compCol;

void init(int n) {
	for (int i = 1; i <= n ; ++i) {
		used [i] = false;
	}
}

void dfs(int v) {
	used[v] = true;
	comp.push_back(v);

	for (auto to: g[v]) {
		if (!used[to]) {
			dfs(to);
		}

	}
}

void findComps() {
	init(n);

	for (int i = 1; i <= n ; ++i) {
		if (!used[i]) {
			comp.clear();
			dfs(i);
			compCol.push_back(comp);
		}
	}
}
