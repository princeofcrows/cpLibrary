#include <bits/stdc++.h>

using namespace std;

struct suffix {
	int idx;
	int rank[2];
};

int comp(suffix a, suffix b) {
	return (a.rank[0] == b.rank[0]) ?
	       (a.rank[1] < b.rank[1] ? 1 : 0) :
	       (a.rank[0] < b.rank[0] ? 1 : 0);
}

vector <int> buildSuffixArray(string str) {
	int n = str.length();
	suffix suffixes[n];

	for (int i = 0; i < n; i++) {
		suffixes[i].idx = i;
		suffixes[i].rank[0] = str[i] - 'a';
		suffixes[i].rank[1] = ((i + 1) < n) ? (str[i + 1] - 'a') : -1;
	}

	sort(suffixes, suffixes + n, comp);

	int ind[n];
	for (int j = 4; j < 2 * n; j = j * 2) {
		int rank = 0;
		int prevR = suffixes[0].rank[0];

		suffixes[0].rank[0] = rank;
		ind[suffixes[0].idx] = 0;

		for (int i = 1; i < n; i++) {
			if (suffixes[i].rank[0] == prevR &&
			    suffixes[i].rank[1] == suffixes[i - 1].rank[1]
			    ) {
				prevR = suffixes[i].rank[0];
				suffixes[i].rank[0] = rank;
			} else {
				prevR = suffixes[i].rank[0];
				suffixes[i].rank[0] = ++rank;
			}

			ind[suffixes[i].idx] = i;
		}

		for (int i = 0; i < n; i++) {
			int nextIdx = suffixes[i].idx + j / 2;
			suffixes[i].rank[1] = (nextIdx < n) ?
			                      suffixes[ind[nextIdx]].rank[0] : -1;
		}

		sort(suffixes, suffixes + n, comp);
	}

	vector <int> sa;
	for (int i = 0; i < n; i++)
		sa.push_back(suffixes[i].idx);

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
