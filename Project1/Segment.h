#pragma once
#include "Vec2.h"

struct Segment
{
	Vec2 s, e;
	Segment(Vec2 s, Vec2 e) :s(s), e(e) {}
	Vec2 dir() { return e - s; }
};

Vec2 line_intersect(Segment l1, Segment l2)
{
	Vec2::T det = l1.dir().cross(l2.dir());
	if (abs(det) < eps)
		return err;
	return l1.s + l1.dir()*((l2.s - l1.s).cross(l2.dir()) / det);
}

Vec2 paral_seg(Segment s1, Segment s2)
{
	if (s1.e < s1.s) swap(s1.s, s1.e);
	if (s2.e < s2.s) swap(s2.s, s2.e);
	if (s1.dir().ccw(s2.s - s1.s) != 0 || s1.e < s2.s || s2.e < s1.s)
		return err;
	return max(s1.s, s2.s);
}

Vec2 seg_intersect(Segment s1, Segment s2)
{
	auto p = line_intersect(s1, s2);
	if (p == err)
		return paral_seg(s1, s2);
	bool in = bound_rect(s1.s, s1.e, p) && bound_rect(s2.s, s2.e, p);

	return in ? p : err;
}

Vec2::T distm(const Vec2 &pa, const Vec2 &a, const Vec2 &pb, const Vec2 &b)
{
	if (seg_intersect({ pa, a }, { pb, b }) != err)
		return 0;

	Vec2::T ans = inf<Vec2::T>();
	auto v = perpend_foot(b - pb, pa - pb);
	if (v != err)
		ans = min(ans, (v - pa).size());

	v = perpend_foot(b - pb, a - pb);
	if (v != err)
		ans = min(ans, (v - a).size());

	v = perpend_foot(a - pa, b - pa);
	if (v != err)
		ans = min(ans, (v - b).size());

	v = perpend_foot(a - pa, pb - pa);
	if (v != err)
		ans = min(ans, (v - pb).size());

	ans = min(ans, (pa - pb).size());
	ans = min(ans, (pa - b).size());
	ans = min(ans, (a - pb).size());
	ans = min(ans, (a - b).size());

	return ans;
}

Vec2::T distM(const Vec2 &pa, const Vec2 &a, const Vec2 &pb, const Vec2 &b)
{
	Vec2::T ans = inf<Vec2::T>();
	ans = max(ans, (pa - b).size());
	ans = max(ans, (a - pb).size());
	ans = max(ans, (a - b).size());
	return ans;
}
