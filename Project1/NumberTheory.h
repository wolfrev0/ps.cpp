#pragma once
#include "Core.h"

struct ModNum
{
	using T = ll;
	static const T m = T(1e9 + 7);

	ModNum(T num = 0) :num(num) {}
	T get() { return (num + m) % m; }

	ModNum operator - () const { return (-num + m) % m; }
	ModNum operator + (const ModNum b)const { return (num + b.num) % m; }
	ModNum operator - (const ModNum b)const { return (num + m - b.num) % m; }
	ModNum operator * (const ModNum b)const { return (num * b.num) % m; }
	ModNum operator / (const ModNum b)const { return (num * pow(b.num, m - 2).num) % m; }
	ModNum operator+= (const ModNum b) { return num = (num + b.num) % m; }
	ModNum operator-= (const ModNum b) { return num = (num + m - b.num) % m; }
	ModNum operator*= (const ModNum b) { return num = (num * b.num) % m; }
	ModNum operator/= (const ModNum b) { return num = (num * pow(b.num, m - 2).num) % m; }

	bool operator==(const ModNum &r) const { return num == r.num; }
	bool operator!=(const ModNum &r) const { return !(*this == r); }

	ModNum operator= (const ModNum &r) { return num = r.num; }
private:
	T num;
	//for modinv
	ModNum pow(const ModNum n, int p)const
	{
		if (p == 0)
			return 1;
		auto tmp = pow(n, p / 2);
		return tmp * tmp * (p % 2 ? n : ModNum(1));
	}
};
ModNum operator"" _m(ull n) { return ModNum(n); }

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
		return T::id(a.n());
	T tmp = fastpow(a, p / 2);
	if (p % 2)
		return tmp * tmp*a;
	return tmp * tmp;
}