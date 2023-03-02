#include <vector>
#include <string>

using namespace std;

vector<int> prefixFunction(string s) {
	int n = (int)s.length();

	vector<int> pi(n);

	for (int i = 1; i < n; i++) {
		int j = pi[i-1];

		while (j > 0 && s[i] != s[j])
			j = pi[j-1];

		if (s[i] == s[j])
			j++;

		pi[i] = j;
	}

	return pi;
}

vector<int> kmpPatternSearch(string p, string s){
	int m = p.length();
	int n = s.length();

	vector<int> pi = prefixFunction(p);
	vector<int> res;

	int i = 0;
	int j = 0;

	while (i < n) {
		if (p[j] == s[i]) {
			j++; i++;
		}

		if (j == m) {
			res.push_back(i - j);
			j = pi[j - 1];
		} else if (i < n && p[j] != s[i]) {
			if (j != 0)
				j = pi[j - 1];
			else
				i = i + 1;
		}
	}

	return res;
}

vector<vector<int> > computeAutomaton(string s) {
	s += '#';
	int n = s.size();

	vector<int> pi = prefixFunction(s);

	vector<vector<int> > aut;
	aut.assign(n, vector<int>(26));

	for (int i = 0; i < n; i++) {
		for (int c = 0; c < 26; c++) {
			if (i > 0 && 'a' + c != s[i])
				aut[i][c] = aut[pi[i-1]][c];
			else
				aut[i][c] = i + ('a' + c == s[i]);
		}
	}

	return aut;
}
