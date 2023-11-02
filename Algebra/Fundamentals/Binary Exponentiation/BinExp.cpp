#include <algorithm>
#include <vector>

#define mod 1000000007
using namespace std;

long long binPowRec(long long a, long long b)
{
	if (b == 0)
		return 1;

	long long res = binPowRec(a, b / 2);

	if (b % 2)
	{
		return (res * res * a) % mod;
	}
	else
	{
		return (res * res) % mod;
	}
}

long long binPowItr(long long a, long long b)
{

	long long res = 1;

	while (b > 0)
	{
		if (b & 1)
		{
			res = (res * a) % mod;
		}

		a = (a * a) % mod;
		b >>= 1;
	}
	return res;
}
