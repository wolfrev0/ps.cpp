#pragma once
#include "Core.h"

template<typename T>
typename enable_if<std::is_fundamental<T>::value, T>::type fastpow(const T &a, int p)
{
	if (p == 0)
		return 1;
	T tmp = fastpow(a, p / 2);
	if (p % 2)
		return tmp * tmp*a;
	return tmp * tmp;
}

template<typename T>
typename enable_if<!is_fundamental<T>::value, T>::type fastpow(const T &a, int p)
{
	if (p == 0)
		return a.mulid();
	T tmp = fastpow(a, p / 2);
	if (p % 2)
		return tmp * tmp*a;
	return tmp * tmp;
}

template<int m>
struct ModNum
{
	using T = ll;
	ModNum(T n) :n((n%m + m) % m) {}
	//operator T() const { return n; }
	inline T val()const { return n; }
	inline ModNum mulid() const { return 1; }

	inline ModNum operator - () const { return -n; }
	inline ModNum operator + (const ModNum b)const { return n + b.val(); }
	inline ModNum operator - (const ModNum b)const { return n - b.val() + m; }
	inline ModNum operator * (const ModNum b)const { return n * b.val(); }
	inline ModNum operator / (const ModNum b)const { return n * fastpow(ModNum(m, b.val()), m - 2).num; }
	inline ModNum operator+= (const ModNum b) { return *this = *this + b.val(); }
	inline ModNum operator-= (const ModNum b) { return *this = *this - b.val(); }
	inline ModNum operator*= (const ModNum b) { return *this = *this * b.val(); }
	inline ModNum operator/= (const ModNum b) { return *this = *this / b.val(); }

	inline ModNum &operator++ () { *this += 1; return *this; }
	inline ModNum &operator-- () { *this -= 1; return *this; }
	inline ModNum operator++(int) { auto ret = *this; ++*this; return ret; }
	inline ModNum operator--(int) { auto ret = *this; --*this; return ret; }

	inline bool operator==(const ModNum &r) const { return n == r.n; }
	inline bool operator!=(const ModNum &r) const { return !(*this == r); }
	inline bool operator<(const ModNum &r) const { return n < r.n; }
	inline bool operator<=(const ModNum &r) const { return n <= r.n; }
	inline bool operator>(const ModNum &r) const { return n > r.n; }
	inline bool operator>=(const ModNum &r) const { return n >= r.n; }

	inline ModNum &operator= (const ModNum &r) { n = r.n; return *this; }
private:
	T n;
};

ll fibo(int n)
{
	static ll memo[100];

	if (n <= 1)
		return 1;
	auto &ret = memo[n];
	if (ret)
		return ret;
	return ret = fibo(n - 1) + fibo(n - 2);
}