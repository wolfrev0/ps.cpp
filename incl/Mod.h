#pragma once
#include "Core.h"

//클래스 Mod는 생각보다 느리지 않다. 16325 제출기록 참고
template<int m> struct Mod {
	Mod(i64 n = 0) : n((n % m + m) % m) {}
	explicit operator int() const { return n; }
	explicit operator bool() const { return !!n; }
	i64 val() const { return n; }

	Mod operator-() const { return -n; }
	Mod operator+(const Mod& b) const { return n + b.val(); }
	Mod operator-(const Mod& b) const { return n - b.val() + m; }
	Mod operator*(const Mod& b) const { return n * b.val(); }
	Mod operator/(const Mod& b) const { return *this * inv(b); }
	Mod operator+=(const Mod& b) { return *this = *this + b; }
	Mod operator-=(const Mod& b) { return *this = *this - b; }
	Mod operator*=(const Mod& b) { return *this = *this * b; }
	Mod operator/=(const Mod& b) { return *this = *this / b; }

	Mod& operator++() {
		*this += 1ll;
		return *this;
	}
	Mod& operator--() {
		*this -= 1ll;
		return *this;
	}
	Mod operator++(signed) {
		auto ret = *this;
		++*this;
		return ret;
	}
	Mod operator--(signed) {
		auto ret = *this;
		--*this;
		return ret;
	}

	bool operator!() { return !n; }
	bool operator==(const Mod& r) const { return n == r.n; }
	bool operator!=(const Mod& r) const { return !(*this == r); }
	bool operator<(const Mod& r) const { return n < r.n; }

private:
	i64 n;

	Mod inv(const Mod& b) const {
		auto [g,x,y] = xgcd(b.val(), -m);
		if(1 % g) throw "No Mod Inv";
		x *= 1 / g;
		while(x < 0) x += -m / g;
		return x;
	}
	tint xgcd(i64 a, i64 b)const{
		if(b == 0) return {a, 1, 0};
		auto [g, x, y] = xgcd(b, a % b);
		return {g, y, x - (a / b) * y};
	}
};

template<int m> ostream& operator<<(ostream& s, const Mod<m>& n) {
	return s << n.val();
}