#include <vector>
#include <string>

using namespace std;

vector<int> rabin_karp(string const& s, string const& t) {
	const int p = 31;
	const int m = 1e9 + 9;
	int sLen = s.length(), tLen = t.length();

	vector<long long> pPow(max(sLen, tLen));
	pPow[0] = 1;

	for (int i = 1; i < (int)pPow.size(); i++)
		pPow[i] = (pPow[i-1] * p) % m;

	vector<long long> h(tLen + 1, 0);
	for (int i = 0; i < tLen; i++)
		h[i+1] = (h[i] + (t[i] - 'a' + 1) * pPow[i]) % m;

	long long h_s = 0;
	for (int i = 0; i < sLen; i++)
		h_s = (h_s + (s[i] - 'a' + 1) * pPow[i]) % m;

	vector<int> occurences;
	for (int i = 0; i + sLen - 1 < tLen; i++) {
		long long cur_h = (h[i+sLen] + m - h[i]) % m;
		if (cur_h == h_s * pPow[i] % m)
			occurences.push_back(i);
	}

	return occurences;
}
