#pragma once
#include "core/base.h"

struct Frac {
	i64 a, b;
	Frac(i64 a = 0, i64 b = 1) : a(a), b(b) { normalize(); }
	bool operator<(const Frac& r) const {
		// NaN < -inf < ... < inf (for using set conveniently)
		//!(a>b) && !(a<b) <=> a==b
		if(r.is_nan()) return false;
		if(is_nan()) return true;
		return a * r.b < r.a * b;
	}
	bool operator>(const Frac& r) const { return r < *this; }
	bool operator==(const Frac& r) const { return !(*this < r) && !(*this > r); }
	bool operator!=(const Frac& r) const { return !(*this == r); }
	bool operator<=(const Frac& r) const { return *this < r || *this == r; }
	bool operator>=(const Frac& r) const { return *this > r || *this == r; }
	Frac operator+(const Frac& r) const { return {a * r.b + r.a * b, b * r.b}; }
	Frac operator*(const Frac& r) const { return {a * r.a, b * r.b}; }
	Frac operator/(const Frac& r) const { return (*this) * Frac(r.b, r.a); }
	bool is_singular() const { return !b; }
	bool is_infpos() const { return a > 0 && !b; }
	bool is_infneg() const { return a < 0 && !b; }
	bool is_nan() const { return !a && !b; }
	bool is_int() const { return b && !(a % b); }
	i64 to_integer() const { return a / b; }
	f64 to_f64() { return (f64)a / b; }
	i64 ceil() const { return a / b + (a * b > 0) * !!(a % b); }
	i64 floor() const { return a / b - (a * b < 0) * !!(a % b); }
	i64 smaller_int() const { return is_int() ? to_integer() - 1 : floor(); }
	i64 larger_int() const { return is_int() ? to_integer() + 1 : ceil(); }
	void normalize() {
		if(is_singular()) {
			if(a) a /= abs(a);
			return;
		}

		i64 g = gcd(a, b);
		a /= g;
		b /= g;
		if(b < 0) a *= -1, b *= -1;
	}
};

template<> Frac inf() { return {1, 0}; }

template<typename T> ostream& operator<<(ostream& s, const Frac& n) {
	return s << n.a << '/' << n.b;
}