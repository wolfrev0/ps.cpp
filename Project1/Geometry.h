#pragma once
#include "Core.h"

using T = ld;
struct Vec2
{
	T x, y;
	Vec2(T x, T y) :x(x), y(y) {}
	bool operator==(const Vec2 &r)const { return x == r.x && y == r.y; }
	bool operator!=(const Vec2 &r)const { return !(*this == r); }
	bool operator<(const Vec2 &r)const { return x == r.x ? y < r.y : x < r.x; }
	bool operator<=(const Vec2 &r)const { return *this == r || *this < r; }
	bool operator>(const Vec2 &r)const { return x == r.x ? y > r.y : x > r.x; }
	bool operator>=(const Vec2 &r)const { return *this == r || *this > r; }
	Vec2 operator+ (const Vec2 &r)const { return { x + r.x, y + r.y }; }
	Vec2 operator-()const { return { -x, -y }; }
	Vec2 operator- (const Vec2 &r)const { return *this + -r; }
	Vec2 operator* (T r)const { return { x*r, y*r }; }
	T size()const { return hypotl(x, y); }
	Vec2 normalize()const { return { x / size(), y / size() }; }
	T dot(const Vec2 &r) const { return x * r.x + y * r.y; }
	T cross(const Vec2 &r)const { return x * r.y - y * r.x; }
	T polar()const { return fmodl(atan2l(y, x) + 2 * pi, 2 * pi); }
	Vec2 project(const Vec2 &base)const { Vec2 b = base.normalize(); return b * b.dot(*this); }
	Vec2 operator+= (const Vec2 &r) { return *this = *this + r; }
	Vec2 operator-= (const Vec2 &r) { return *this = *this - r; }
	Vec2 operator*= (T r) { return *this = *this * r; }
} err = { inf<T>(), inf<T>() };
T ccw(Vec2 a, Vec2 b) { return a.cross(b); }

Vec2 line_intersect(Vec2 a, Vec2 b, Vec2 c, Vec2 d)
{
	T det = (b - a).cross(d - c);
	if (abs(det) < eps)
		return err;
	return a + (b - a)*((c - a).cross(d - c) / det);
}

Vec2 paral_seg(Vec2 a, Vec2 b, Vec2 c, Vec2 d)
{
	if (b < a) swap(a, b);
	if (d < c) swap(c, d);
	if (ccw(b - a, c - a) != 0 || b < c || d < a)
		return err;
	return max(a, c);
}

bool bound_rect(Vec2 a, Vec2 b, Vec2 p)
{
	if (a > b)
		swap(a, b);
	return a <= p && p <= b;
}

Vec2 seg_intersect(Vec2 a, Vec2 b, Vec2 c, Vec2 d)
{
	auto p = line_intersect(a, b, c, d);
	if (p == err)
		return paral_seg(a, b, c, d);
	bool in = bound_rect(a, b, p) && bound_rect(c, d, p);

	return in ? p : err;
}

Vec2 perpendFoot(Vec2 a, Vec2 b, Vec2 p)
{
	Vec2 res = a + (p - a).project(b - a);
	return bound_rect(a, b, res) ? res : err;
}

T distm(const Vec2 &pa, const Vec2 &a, const Vec2 &pb, const Vec2 &b)
{
	if (seg_intersect(pa, a, pb, b) != err)
		return 0;

	T ans = inf<T>();
	auto v = perpendFoot(pb, b, pa);
	if (v != err)
		ans = min(ans, (v - pa).size());

	v = perpendFoot(pb, b, a);
	if (v != err)
		ans = min(ans, (v - a).size());

	v = perpendFoot(pa, a, b);
	if (v != err)
		ans = min(ans, (v - b).size());

	v = perpendFoot(pa, a, pb);
	if (v != err)
		ans = min(ans, (v - pb).size());

	ans = min(ans, (pa - pb).size());
	ans = min(ans, (pa - b).size());
	ans = min(ans, (a - pb).size());
	ans = min(ans, (a - b).size());

	return ans;
}

T distM(const Vec2 &pa, const Vec2 &a, const Vec2 &pb, const Vec2 &b)
{
	T ans = inf<T>();
	ans = max(ans, (pa - b).size());
	ans = max(ans, (a - pb).size());
	ans = max(ans, (a - b).size());
	return ans;
}
