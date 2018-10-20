#pragma once
#include "Core.h"

struct Vec2
{
	using T = double;
	T x, y;
	explicit Vec2() :Vec2(0, 0) {}
	explicit Vec2(T x, T y) :x(x), y(y) {}
	inline bool operator==(const Vec2 &r)const { return x == r.x && y == r.y; }
	inline bool operator!=(const Vec2 &r)const { return !(*this == r); }
	inline bool operator<(const Vec2 &r)const { return x == r.x ? y < r.y : x < r.x; }
	inline bool operator<=(const Vec2 &r)const { return *this == r || *this < r; }
	inline bool operator>(const Vec2 &r)const { return x == r.x ? y > r.y : x > r.x; }
	inline bool operator>=(const Vec2 &r)const { return *this == r || *this > r; }
	inline Vec2 operator+ (const Vec2 &r)const { return Vec2(x + r.x, y + r.y); }
	inline Vec2 operator-()const { return Vec2(-x, -y); }
	inline Vec2 operator- (const Vec2 &r)const { return *this + -r; }
	inline Vec2 operator* (T r)const { return Vec2(x*r, y*r); }
	inline T size()const { return hypot(x, y); }
	inline Vec2 normalize()const { return Vec2(x / size(), y / size()); }
	inline T dot(const Vec2 &r) const { return x * r.x + y * r.y; }
	inline T cross(const Vec2 &r)const { return x * r.y - y * r.x; }
	inline T ccw(const Vec2 &a, const Vec2 &b) { return (a - *this).cross(b - *this); }
	inline T angle()const { return atan2(y, x); }
	inline Vec2 project(const Vec2 &p)const { Vec2 base = normalize(); return base * base.dot(p); }
	inline Vec2 operator+= (const Vec2 &r) { return *this = *this + r; }
	inline Vec2 operator-= (const Vec2 &r) { return *this = *this - r; }
	inline Vec2 operator*= (T r) { return *this = *this * r; }
} zero, err = Vec2(inf<Vec2::T>(), inf<Vec2::T>());