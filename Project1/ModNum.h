#pragma once
#include "NumberTheory.h"

class NoModInv {};

struct ModNum {
	using T = ll;
	ModNum(T n = 0, T m = mod) :n((n%m + m) % m), m(m) {}
	inline T val()const { return n; }
	inline ModNum mulid() const { return 1; }

	inline ModNum operator - () const { return -n; }
	inline ModNum operator + (const ModNum b)const { return n + b.val(); }
	inline ModNum operator - (const ModNum b)const { return n - b.val() + m; }
	inline ModNum operator * (const ModNum b)const { return n * b.val(); }
	inline ModNum operator / (const ModNum b)const {
		ll x, y;
		ll g = xgcd(b.val(), -m, x, y);
		if (1 % g)
			throw NoModInv();
		x *= 1 / g;
		while (x < 0)
			x += -m / g;
		return x;
		//extended gcd is better than fastpow.
		//return fastpow(ModNum(m, b.val()), m - 2)*n; 
	}
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

	//operator T() const { return n; }
	inline ModNum &operator= (const ModNum &r) { n = r.n; return *this; }
private:
	T n;
	const T m;
};