#pragma once
#include "Core.h"

template<typename T>
typename enable_if<std::is_fundamental<T>::value, T>::type fastpow(const T& a, int p) {
	if (p == 0)
		return 1;
	T tmp = fastpow(a, p / 2);
	if (p % 2)
		return tmp * tmp*a;
	return tmp * tmp;
}

template<typename T>
typename enable_if<!is_fundamental<T>::value, T>::type fastpow(const T& a, int p) {
	if (p == 0)
		return a.mulid();
	T tmp = fastpow(a, p / 2);
	if (p % 2)
		return tmp * tmp*a;
	return tmp * tmp;
}

ll fibo(int n) {
	static ll memo[100];

	if (n <= 1)
		return 1;
	auto& ret = memo[n];
	if (ret)
		return ret;
	return ret = fibo(n - 1) + fibo(n - 2);
}

ll xgcd(ll a, ll b, ll& x, ll& y) {
	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}

	ll xtmp, ytmp;
	ll g = xgcd(b%a, a, xtmp, ytmp);
	x = ytmp - (b / a) * xtmp;
	y = xtmp;
	return g;
}

pair<ll, ll> xgcd2(ll a, ll b) {
	if (b == 0)
		return { 1,0 };
	auto t = xgcd2(b, a%b);
	return { t.second,t.first - t.second*(a / b) };
}

vector<ll> factorization(ll n)
{
	ll cur = n;
	vector<ll> ret;
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

vector<ll> divisors(ll n)
{
	vector<ll> ret, tmp;
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
	for (ll i = 2; i*i<=n; i++) {
		if (ret[i])
			continue;
		for (ll j = i * i; j < n; j += i)
			ret[j] = true;
	}
	return ret.flip();
}

//harmony series: nlogn
vector<vector<int>> sieve_divs(int n)
{
	vector<vector<int>> ret(n);
	for (ll i = 2; i*i<=n; i++) {
		for (ll j = i + i; j < n; j += i)
			ret[j].push_back(i);
	}
	return ret;
}

//More accurate than floor(log(n))
int lgf(ll n)
{
	assert(n > 0);
	int ret = -1;
	while (n)
		n /= 2, ret++;
	return ret;
}

//More accurate than ceil(log(n))
int lgc(ll n) {
	return lgf(n) + __builtin_popcountll(n) != 1;
}