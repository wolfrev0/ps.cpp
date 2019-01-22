#pragma once
#include "Core.h"

template<typename T>
T fastpow(const T& a, int p) {
	if (p == 0)
		return a.one();
	T tmp = fastpow(a, p / 2);
	if (p % 2)
		return tmp * tmp*a;
	return tmp * tmp;
}

struct XGCD{i64 g; i64 x; i64 y;};
XGCD xgcd(i64 a, i64 b) {
    if (b == 0)
        return {a, 1, 0};
    auto res = xgcd(b, a%b);
    return {res.g, res.y, res.x-(a/b)*res.y};
}

vector<i64> factorization(i64 n)
{
	i64 cur = n;
	vector<i64> ret;
	trav (i, 2, i*i <= n)
		while (!(cur%i))
		{
			cur /= i;
			ret.push_back(i);
		}
	if (cur > 1)
		ret.push_back(cur);
	return ret;
}

vector<i64> divisors(i64 n)
{
	vector<i64> ret, tmp;
	trav(i, 1, i*i <= n){
		if (n%i == 0)
		{
			ret.push_back(i);
			if (i != n / i)
				tmp.push_back(n / i);
		}
	}
	reverse(tmp.begin(), tmp.end());
	ret.insert(ret.end(), tmp.begin(), tmp.end());
	return ret;
}

//n*invackermann(n)
template<int n>
bitset<n> sieve_prime()
{
	bitset<n> ret(3);
	for (i64 i = 2; i*i<=n; i++) {
		if (ret[i])
			continue;
		for (i64 j = i * i; j < n; j += i)
			ret[j] = true;
	}
	return ret.flip();
}

//harmony series: nlogn
vector<vector<int>> sieve_divs(int n)
{
	vector<vector<int>> ret(n);
	for (i64 i = 2; i*i<=n; i++) {
		for (i64 j = i + i; j < n; j += i)
			ret[j].push_back(i);
	}
	return ret;
}

//floor(log(n))
int log_f(i64 n){
	int ret = 0;
	while (n)
		n/=2, ret++;
	return ret-1;
}

//ceil(log(n))
int log_c(i64 n) {
	int ret = 0;
	int rem=0;
	while (n)
		rem+=n%2, n/=2, ret++;
	return ret-(rem<=1);
}

i64 sqrt_f(i64 n){
	travo(i, 1, i*i<=n)
		;
	return i-1;
}

i64 sqrt_c(i64 n){
	travo(i, 1, i*i<n)
		;
	return i;
}