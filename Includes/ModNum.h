#pragma once
#include "NumberTheory.h"

class NoModInv {};

//Do not use when Rabin Karp hashing(too weak, instead use ull).
struct ModNum {
	using T = ll;
	ModNum(T n = 0, T m = mod) :n((n%m + m) % m), m(m) {}
	inline T val()const { return n; }
	inline ModNum mulid() const { return { 1, m }; }

	inline ModNum operator - () const { return { -n, m }; }
	inline ModNum operator + (const ModNum& b)const { return { n + b.val(), m }; }
	inline ModNum operator - (const ModNum& b)const { return { n - b.val() + m, m }; }
	inline ModNum operator * (const ModNum& b)const { return { n * b.val(), m }; }
	inline ModNum operator / (const ModNum& b)const { return *this * inv(b); }
	inline ModNum operator+= (const ModNum& b) { return *this = *this + b; }
	inline ModNum operator-= (const ModNum& b) { return *this = *this - b; }
	inline ModNum operator*= (const ModNum& b) { return *this = *this * b; }
	inline ModNum operator/= (const ModNum& b) { return *this = *this / b; }

	inline ModNum& operator++ () { *this += 1; return *this; }
	inline ModNum& operator-- () { *this -= 1; return *this; }
	inline ModNum operator++(int) { auto ret = *this; ++*this; return ret; }
	inline ModNum operator--(int) { auto ret = *this; --*this; return ret; }

	inline bool operator==(const ModNum& r) const { return n == r.n; }
	inline bool operator!=(const ModNum& r) const { return !(*this == r); }
	inline bool operator<(const ModNum& r) const { return n < r.n; }
	inline bool operator<=(const ModNum& r) const { return n <= r.n; }
	inline bool operator>(const ModNum& r) const { return n > r.n; }
	inline bool operator>=(const ModNum& r) const { return n >= r.n; }

	inline ModNum inv(const ModNum &b)const {
		ll x, y;
		ll g = xgcd(b.val(), -m, x, y);
		if (1 % g)
			throw NoModInv();
		x *= 1 / g;
		while (x < 0)
			x += -m / g;
		return { x, m };
		//extended gcd is better than fastpow.
		//return fastpow(ModNum(m, b.val()), m - 2)*n; 
	}

	//operator T() const { return n; }
	ModNum(const ModNum& r) : n(r.n),m(r.m) {}
	inline ModNum& operator= (const ModNum& r) { n = r.n; return *this; }
private:
	T n;
	const T m;
};

ostream& operator<<(ostream& s, const ModNum& n) { return s << n.val(); }