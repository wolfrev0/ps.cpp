#pragma once
#include "Core.h"
#include "Frac.h"

struct Vec2 {
	using T = ld;
	T x, y;
	explicit Vec2() :Vec2(0, 0) {}
	explicit Vec2(T x, T y) :x(x), y(y) {}
	inline Vec2 operator+ (const Vec2& r)const { return Vec2(x + r.x, y + r.y); }
	inline Vec2 operator- ()const { return Vec2(-x, -y); }
	inline Vec2 operator- (const Vec2& r)const { return *this + -r; }
	inline Vec2 operator* (T r)const { return Vec2(x*r, y*r); }
	inline bool operator==(const Vec2& r)const { return x == r.x && y == r.y; }
	inline bool operator!=(const Vec2& r)const { return !(*this == r); }
	inline bool operator<(const Vec2& r)const { return x == r.x ? y < r.y : x < r.x; }
	inline bool operator<=(const Vec2& r)const { return *this == r || *this < r; }
	inline bool operator>(const Vec2& r)const { return x == r.x ? y > r.y : x > r.x; }
	inline bool operator>=(const Vec2& r)const { return *this == r || *this > r; }
	inline Vec2 operator+= (const Vec2& r) { return *this = *this + r; }
	inline Vec2 operator-= (const Vec2& r) { return *this = *this - r; }
	inline Vec2 operator*= (T r) { return *this = *this * r; }
	inline T size()const { return hypot(x, y); }
	inline T sizesq()const { return dot(*this); }
	inline Vec2 normalize()const { return Vec2(x / size(), y / size()); }
	inline T dot(const Vec2& r) const { return x * r.x + y * r.y; }
	inline T dot(const Vec2& a, const Vec2& b) const { return (a - *this).dot(b - *this); }
	inline T cross(const Vec2& r)const { return x * r.y - y * r.x; }
	inline T cross(const Vec2& a, const Vec2& b) const { return (a - *this).cross(b - *this); }
	inline T ccw(const Vec2& a, const Vec2& b) const { return cross(a, b) ? cross(a, b) / abs(cross(a, b)) : 0; }
	inline T angle()const { auto ret = atan2(y, x); return fmod(ret + 2 * pi, 2 * pi); }
	inline Frac tan()const { return Frac(y, x); }
	inline Vec2 project(const Vec2& p)const { Vec2 base = normalize(); return base * base.dot(p); }
} zero, err = Vec2(inf<Vec2::T>(), inf<Vec2::T>()), epsv = Vec2(eps, eps);

inline bool cmpccw(const Vec2& l, const Vec2& r, const Vec2& base) {
	Vec2::T val = base.ccw(l, r);
	assert(base <= l && base <= r);
	if (val == 0)
		//need some thinking but ok. because base should be left-bottom element.
		return l < r;
	return val > 0;
}