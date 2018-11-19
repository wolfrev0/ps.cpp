#pragma once
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
#include <fstream>

#define __builtin_ctz(x) ([](int mask) {unsigned long ret=32;_BitScanForward(&ret, mask);return ret;}(x))
#define __builtin_popcount(x) __popcnt(x)
int __builtin_popcountll(long long x){
	int ret=0;
	while (x)
		ret += x & 1, x >>= 1;
	return ret;
}

long long __gcd(long long a, long long b){ return !a?b:__gcd(b%a, a); }
auto gcd = __gcd;
long long lcm(long long a, long long b){ return a/gcd(a,b)*b; }