#pragma once
#include "Vec2.h"

class LineException {};
class LineSame :public LineException {};

struct Line {
	Vec2 s, e;
	explicit Line() :Line(zero, zero) {}
	explicit Line(Vec2 s, Vec2 e) :s(s), e(e) { }
	inline Vec2 dir()const { return e - s; }

	Vec2 intersect(Line &r) {
		if (s > e)
			swap(s, e);
		if (r.s > r.e)
			swap(r.s, r.e);

		Vec2::T det = dir().cross(r.dir());
		if (abs(det) < eps)
			if (abs((r.s - s).cross(e - s)) < eps)
				throw LineSame();
			else
				return err;
		auto res = s + dir()*((r.s - s).cross(r.dir()) / det);
		return valid_intersect(res) && r.valid_intersect(res) ? res : err;
	}

	bool intersect_det(Line &r) {
		if (s > e)
			swap(s, e);
		if (r.s > r.e)
			swap(r.s, r.e);

		Vec2::T det1 = s.ccw(e, r.s) * s.ccw(e, r.e);
		Vec2::T det2 = r.s.ccw(r.e, s) * r.s.ccw(r.e, e);
		if (!det1 && !det2)
			return e >= r.s && r.e >= s;
		return det1 <= 0 && det2 <= 0;
	}

	Vec2 perpend_foot(const Vec2 &p) {
		if (s > e)
			swap(s, e);
		auto res = s + dir().project(p - s);
		return valid_foot(res) ? res : err;
	}

	bool contains(const Vec2 &v) {
		if (s > e)
			swap(s, e);
		return valid_contains(v) && v.ccw(s, e) == 0;
	}

private:
	virtual bool valid_intersect(const Vec2 &p) const { return true; }
	virtual bool valid_foot(const Vec2 &p) const { return true; }
	virtual bool valid_contains(const Vec2 &p) const { return true; }
};

struct Segment :public Line
{
	explicit Segment() :Segment(zero, zero) {}
	explicit Segment(Vec2 s, Vec2 e) :Line(s, e) {}
	virtual bool valid_intersect(const Vec2 &p)const override {
		if (abs(s.x - e.x) < eps && abs(p.x - s.x) < eps)
			return s.y <= p.y && p.y <= e.y;
		if (abs(s.y - e.y) < eps && abs(p.y - s.y) < eps)
			return s.x <= p.x && p.x <= e.x;
		return s <= p && p <= e;
	}
	virtual bool valid_foot(const Vec2& p)const override { return s <= p && p <= e; }
	virtual bool valid_contains(const Vec2 &p) const override { return s <= p && p <= e; }
};