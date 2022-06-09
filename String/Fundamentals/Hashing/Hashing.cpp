#include <string>
using namespace std;


long long computeHash(string const& s) {
	const int p = 31;
	const int m = 1e9 + 9;

	long long hashValue = 0;
	long long pPow = 1;

	for (char c : s) {
		hashValue = (hashValue + (c - 'a' + 1) * pPow) % m;
		pPow = (pPow * p) % m;
	}
	return hashValue;
}
