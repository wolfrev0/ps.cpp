#include <iostream>
#include <memory.h>
#include <cmath>
#include <limits>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <sstream>
#include <numeric>
#include <ctime>
#include <random>
#include <intrin.h>
#include <iomanip>
#include <bitset>
#include <assert.h>

#define __builtin_ctz(x) ([](int mask) {unsigned long ret=32;_BitScanForward(&ret, mask);return ret;}(x))
#define __builtin_popcount(x) __popcnt(x)
int __builtin_popcountll(long long x)
{
	int ret=0;
	while(x)
		x<<=1,ret++;
	return ret;
}

long long __gcd(long long a, long long b)
{
	if(!a)
		return b;
	return __gcd(b%a, a);
}