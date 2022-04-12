#include <algorithm>
#include <vector>
using namespace std;

int gcd (int a, int b) {
	return b ? gcd (b, a % b) : a;
}

int gcdItr (int a, int b) {
	while (b) {
		a %= b;
		swap(a, b);
	}
	return a;
}


int lcm (int a, int b) {
	return a / gcd(a, b) * b;
}

int lcmArray (vector<int> v) {
	int lcm = 1;

	for(auto u: v) {
		lcm = (lcm * u) / gcd(lcm, u);
	}

	return lcm;
}

int gcdFast(int a, int b) {
	if (!a || !b)
		return a | b;

	unsigned shift = __builtin_ctz(a | b);
	a >>= __builtin_ctz(a);

	do {
		b >>= __builtin_ctz(b);
		if (a > b)
			swap(a, b);
		b -= a;
	} while (b);

	return a << shift;
}
