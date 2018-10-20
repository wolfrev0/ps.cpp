#pragma once
#include "Vec2.h"

class LineException {};
class LineSame :public LineException {};

struct Line
{
	Vec2 s, e;
	explicit Line() :Line(zero, zero) {}
	explicit Line(Vec2 s, Vec2 e) :s(s), e(e) { if (s > e)swap(this->s, this->e); }
	inline Vec2 dir()const { return e - s; }

	Vec2 intersect(const Line &r)const
	{
		Vec2::T det = dir().cross(r.dir());
		if (abs(det) < eps)
			if ((s - r.s).size() < eps)
				throw LineSame();
			else
				return err;
		auto res = s + dir()*((r.s - s).cross(r.dir()) / det);
		return valid_intersect(res) && r.valid_intersect(res) ? res : err;
	}

	virtual Vec2 perpend_foot(Vec2 p) const {
		auto res = s + dir().project(p - s);
		return valid_foot(res) ? res : err;
	}

private:
	virtual bool valid_intersect(const Vec2 &p) const { return true; }
	virtual bool valid_foot(const Vec2 &p) const { return true; }
};

struct Segment :public Line
{
	explicit Segment() :Segment(zero, zero) {}
	explicit Segment(Vec2 s, Vec2 e) :Line(s, e) {}
	virtual bool valid_intersect(const Vec2 &p)const override { return s <= p && p <= e; }
	virtual bool valid_foot(const Vec2& p)const override { return s <= p && p <= e; }
};