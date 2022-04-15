# include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAXN 100005

vector<int> adj[MAXN];  // adjacency list representation
int n; // number of vertices

vector<bool> visited(MAXN, false);

void dfs(int v) {
	visited[v] = true;
	for (int u : adj[v]) {
		if (!visited[u])
			dfs(u);
	}
}

vector<int> color;

vector<int> time_in(MAXN, false), time_out(MAXN, false);
int dfs_timer = 0;

void dfsBicolor(int v) {
	time_in[v] = dfs_timer++;
	color[v] = 1;
	for (int u : adj[v])
		if (color[u] == 0)
			dfsBicolor(u);
	color[v] = 2;
	time_out[v] = dfs_timer++;
}
