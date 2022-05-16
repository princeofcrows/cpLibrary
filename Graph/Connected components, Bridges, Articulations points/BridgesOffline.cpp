#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAXN 100005

int n; // number of nodes
vector<vector<int> > adj(MAXN); // adjacency list of graph

vector<bool> visited;
vector<int> tin, low;
int timer;
vector<pair<int, int> > bridges;

void addBridge(int u, int v) {
	bridges.push_back({u, v});
}

void dfs(int v, int p = -1) {
	visited[v] = true;
	tin[v] = low[v] = timer++;

	for (int to : adj[v]) {
		if (to == p) continue;

		if (visited[to]) {
			low[v] = min(low[v], tin[to]);
		} else {
			dfs(to, v);
			low[v] = min(low[v], low[to]);

			if (low[to] > tin[v])
				addBridge(v, to);
		}
	}
}

void findBridges() {
	timer = 0;
	visited.assign(n+1, false);

	tin.assign(n+1, -1);
	low.assign(n+1, -1);
	bridges.clear();

	for (int i = 1; i <= n; ++i) {
		if (!visited[i])
			dfs(i);
	}
}
