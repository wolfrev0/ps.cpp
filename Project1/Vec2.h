#pragma once
#include "Core.h"

struct Vec2
{
	using T = double;
	T x, y;
	Vec2() :x(0), y(0) {}
	Vec2(T x, T y) :x(x), y(y) {}
	inline bool operator==(const Vec2 &r)const { return x == r.x && y == r.y; }
	inline bool operator!=(const Vec2 &r)const { return !(*this == r); }
	inline bool operator<(const Vec2 &r)const { return x == r.x ? y < r.y : x < r.x; }
	inline bool operator<=(const Vec2 &r)const { return *this == r || *this < r; }
	inline bool operator>(const Vec2 &r)const { return x == r.x ? y > r.y : x > r.x; }
	inline bool operator>=(const Vec2 &r)const { return *this == r || *this > r; }
	inline Vec2 operator+ (const Vec2 &r)const { return { x + r.x, y + r.y }; }
	inline Vec2 operator-()const { return { -x, -y }; }
	inline Vec2 operator- (const Vec2 &r)const { return *this + -r; }
	inline Vec2 operator* (T r)const { return { x*r, y*r }; }
	inline T size()const { return hypot(x, y); }
	inline Vec2 normalize()const { return { x / size(), y / size() }; }
	inline T dot(const Vec2 &r) const { return x * r.x + y * r.y; }
	inline T cross(const Vec2 &r)const { return x * r.y - y * r.x; }
	inline T ccw(const Vec2 &r) { return cross(r); }
	inline T angle()const { return atan2(y, x); }
	inline Vec2 project(const Vec2 &base)const { Vec2 b = base.normalize(); return b * b.dot(*this); }
	inline Vec2 operator+= (const Vec2 &r) { return *this = *this + r; }
	inline Vec2 operator-= (const Vec2 &r) { return *this = *this - r; }
	inline Vec2 operator*= (T r) { return *this = *this * r; }
} err = { inf<Vec2::T>(), inf<Vec2::T>() };

bool bound_rect(Vec2 a, Vec2 b, Vec2 p)
{
	if (a > b)
		swap(a, b);
	return a <= p && p <= b;
}

Vec2 perpend_foot(Vec2 a, Vec2 p)
{
	auto res = p.project(a);
	return bound_rect(Vec2(), a, res) ? res : err;
}