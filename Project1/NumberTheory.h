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

struct ModNum
{
	using T = ll;
	explicit ModNum(T m = mod, T num = 0) :m(m), num((num%m + m) % m) {}
	operator T() const { return num; }
	inline ModNum mulid() const { return ModNum(m, 1); }

	inline ModNum operator - () const { return ModNum(m, -num); }
	inline ModNum operator + (const T b)const { return ModNum(m, num + b); }
	inline ModNum operator - (const T b)const { return ModNum(m, num + m - b); }
	inline ModNum operator * (const T b)const { return ModNum(m, num * b); }
	inline ModNum operator / (const T b)const { return ModNum(m, num * fastpow(ModNum(m, b), m - 2).num); }
	inline ModNum operator+= (const T b) { return *this = *this + b; }
	inline ModNum operator-= (const T b) { return *this = *this - b; }
	inline ModNum operator*= (const T b) { return *this = *this * b; }
	inline ModNum operator/= (const T b) { return *this = *this / b; }

	inline ModNum &operator++ () { *this += 1; return *this; }
	inline ModNum &operator-- () { *this -= 1; return *this; }
	inline ModNum operator++(int) { auto ret = *this; ++*this; return ret; }
	inline ModNum operator--(int) { auto ret = *this; --*this; return ret; }

	inline bool operator==(const ModNum &r) const { return num == r.num; }
	inline bool operator!=(const ModNum &r) const { return !(*this == r); }
	inline bool operator<(const ModNum &r) const { return num < r.num; }
	inline bool operator<=(const ModNum &r) const { return num <= r.num; }
	inline bool operator>(const ModNum &r) const { return num > r.num; }
	inline bool operator>=(const ModNum &r) const { return num >= r.num; }

	inline ModNum &operator= (const ModNum &r) { num = r.num; return *this; }
private:
	T num;
	const T m;
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