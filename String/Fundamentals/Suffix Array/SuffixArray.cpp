#include <bits/stdc++.h>
#define MAXN 100005
#define K 22

using namespace std;

struct suffix {
	int idx;
	int rank[2];
};

suffix suffixes[K][MAXN];

int comp(suffix a, suffix b) {
	return (a.rank[0] == b.rank[0]) ?
	       (a.rank[1] < b.rank[1] ? 1 : 0) :
	       (a.rank[0] < b.rank[0] ? 1 : 0);
}

vector <int> buildSuffixArray(string str) {
	int n = str.length();

	for (int i = 0; i < n; i++) {
		suffixes[0][i].idx = i;
		suffixes[0][i].rank[0] = str[i] - 'a';
		suffixes[0][i].rank[1] = ((i + 1) < n) ? (str[i + 1] - 'a') : -1;
	}

	sort(suffixes[0], suffixes[0] + n, comp);

	int ind[n], k = 1;
	for (int j = 4 ; j < 2 * n; j = j * 2) {
		int rank = 0;
		int prevR = suffixes[k-1][0].rank[0];

		suffixes[k][0].rank[0] = rank;
		suffixes[k][0].idx = suffixes[k-1][0].idx;

		ind[suffixes[k][0].idx] = 0;

		for (int i = 1; i < n; i++) {
			if (suffixes[k-1][i].rank[0] == prevR &&
			    suffixes[k-1][i].rank[1] == suffixes[k-1][i - 1].rank[1]
			    ) {
				prevR = suffixes[k-1][i].rank[0];
				suffixes[k][i].rank[0] = rank;
			} else {
				prevR = suffixes[k-1][i].rank[0];
				suffixes[k][i].rank[0] = ++rank;
			}

			suffixes[k][i].idx = suffixes[k-1][i].idx;
			ind[suffixes[k][i].idx] = i;
		}

		for (int i = 0; i < n; i++) {
			int nextIdx = suffixes[k][i].idx + j / 2;
			suffixes[k][i].rank[1] = (nextIdx < n) ?
			                         suffixes[k][ind[nextIdx]].rank[0] : -1;
		}

		sort(suffixes[k], suffixes[k] + n, comp);

		k++;
	}

	vector <int> sa;
	for (int i = 0; i < n; i++)
		sa.push_back(suffixes[k-1][i].idx);

	return sa;
}

vector <int> kasai(string txt, vector <int> sa) {
	int n = sa.size();
	vector <int> lcp(n, 0);
	vector <int> inverseSuff(n, 0);

	for (int i = 0; i < n; i++)
		inverseSuff[sa[i]] = i;

	int k = 0;

	for (int i = 0; i < n; i++) {
		if (inverseSuff[i] == n - 1) {
			k = 0;
			continue;
		}

		int j = sa[inverseSuff[i] + 1];

		while (i + k < n && j + k < n && txt[i + k] == txt[j + k])
			k++;

		lcp[inverseSuff[i]] = k;

		if (k > 0)
			k--;
	}

	return lcp;
}

int longestRepeatingSubstring(string txt) {
	vector <int> sa = buildSuffixArray(txt);
	vector <int> lcp = kasai(txt, sa);

	int result = 0;

	for (int i = 0; i < lcp.size(); i++)
		result = max(result, lcp[i]);

	return result;
}

int countUniqueSubstring(string txt) {
	int n = txt.length();

	vector <int> sa = buildSuffixArray(txt);
	vector <int> lcp = kasai(txt, sa);

	int result = n - sa[0];

	for (int i = 1; i < lcp.size(); i++)
		result += (n - sa[i]) - lcp[i - 1];

	result++;
	return result;
}
