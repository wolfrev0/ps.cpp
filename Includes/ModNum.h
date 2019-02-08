#pragma once
#include "NumberTheory.h"

class NoModInv {};

//Do not use when Rabin Karp hashing(too weak, instead use ull).
struct ModNum {
	ModNum(i64 n=0) :n((n%mod+mod)%mod){}
	i64 val()const { return n; }

	ModNum operator - () const { return {-n}; }
	ModNum operator + (const ModNum& b)const { return n + b.val(); }
	ModNum operator - (const ModNum& b)const { return n - b.val() + mod; }
	ModNum operator * (const ModNum& b)const { return n * b.val(); }
	ModNum operator / (const ModNum& b)const { return *this * inv(b); }
	ModNum operator+= (const ModNum& b) { return *this = *this + b; }
	ModNum operator-= (const ModNum& b) { return *this = *this - b; }
	ModNum operator*= (const ModNum& b) { return *this = *this * b; }
	ModNum operator/= (const ModNum& b) { return *this = *this / b; }

	ModNum& operator++ () { *this += 1ll; return *this; }
	ModNum& operator-- () { *this -= 1ll; return *this; }
	ModNum operator++(int) { auto ret = *this; ++*this; return ret; }
	ModNum operator--(int) { auto ret = *this; --*this; return ret; }

	bool operator==(const ModNum& r) const { return n == r.n; }
	bool operator!=(const ModNum& r) const { return !(*this == r); }
	bool operator<(const ModNum& r) const { return n < r.n; }
	bool operator<=(const ModNum& r) const { return n <= r.n; }
	bool operator>(const ModNum& r) const { return n > r.n; }
	bool operator>=(const ModNum& r) const { return n >= r.n; }

	static ModNum zero(){ return 0; }
	static ModNum one(){ return 1; }
	static ModNum inf(){ return -1; }
private:
	i64 n;

	ModNum inv(const ModNum &b)const {
		auto res = xgcd(b.val(), -mod);
		if (1 % res.g)
			throw NoModInv();
		res.x *= 1 / res.g;
		while (res.x < 0)
			res.x += -mod / res.g;
		return res.x;
	}
};

ostream& operator<<(ostream& s, const ModNum& n) { return s << n.val(); }