#include <utility>

using namespace std;

pair<int, int> fiboFastDoubling (int n) {
	if (n == 0)
		return {0, 1};

	auto p = fiboFastDoubling(n >> 1);
	int c = p.first * (2 * p.second - p.first);
	int d = p.first * p.first + p.second * p.second;
	if (n & 1)
		return {d, c + d};
	else
		return {c, d};
}
