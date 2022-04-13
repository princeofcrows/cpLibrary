# include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int> > adj;  // adjacency list representation
int n; // number of nodes
int s; // source vertex

queue<int> q;
vector<bool> used(n); // visited nodes
vector<int> d(n), p(n); // distance & parent

void bfs() {
	q.push(s);
	used[s] = true;
	p[s] = -1;

	while (!q.empty()) {
		int v = q.front();
		q.pop();

		for (int u : adj[v]) {
			if (!used[u]) {
				used[u] = true;
				q.push(u);

				d[u] = d[v] + 1;
				p[u] = v;
			}
		}
	}
}

void printPath(int u) {
	if (!used[u]) {
		cout << "No path!";
	} else {
		vector<int> path;
		for (int v = u; v != -1; v = p[v])
			path.push_back(v);
		reverse(path.begin(), path.end());
		cout << "Path: ";
		for (int v : path)
			cout << v << " ";
	}
}
