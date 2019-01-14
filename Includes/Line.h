#pragma once
#include "Vec2.h"

class LineException {};
class LineSame :public LineException {};

struct Line {
	explicit Line() :Line(-Vec2(inf<int>(), inf<int>()), Vec2(inf<int>(), inf<int>())) {}
	explicit Line(const Vec2& s, const Vec2& e) :_s(s), _e(e) { if(_s > _e) swap(_s, _e); }
	inline Vec2 dir()const { return _e - _s; }

	inline Vec2 s()const{return _s;}
	inline Vec2 e()const{return _e;}
	inline void s(Vec2& v){ if ((_s=v) > _e) swap(_s, _e); }
	inline void e(Vec2& v){ if (_s > (_e=v)) swap(_s, _e); }

	bool intersect(const Line &r, Vec2& res) const {
		Vec2::T det = dir().cross(r.dir());
		if (abs(det) < eps){
			if (abs((r._s - _s).cross(_e - _s)) < eps)
				throw LineSame();
			else
				return false;
		}
		res = _s + dir()*((r._s - _s).cross(r.dir()) / det);
		return valid_intersect(res) && r.valid_intersect(res);
	}

	bool intersect_det(const Line &r) const {
		Vec2::T det1 = _s.ccw(_e, r._s) * _s.ccw(_e, r._e);
		Vec2::T det2 = r._s.ccw(r._e, _s) * r._s.ccw(r._e, _e);
		if (!det1 && !det2)
			return _e >= r._s && r._e >= _s;
		return det1 <= 0 && det2 <= 0;
	}

	bool perpend_foot(const Vec2& p, Vec2& res) const {
		return valid_foot(res=_s+dir().project(p - _s));
	}

	bool contains(const Vec2& v) const {
		return valid_contains(v) && v.ccw(_s, _e) == 0;
	}
protected:
	Vec2 _s, _e;
private:
	virtual bool valid_intersect(const Vec2& p) const { return true; }
	virtual bool valid_foot(const Vec2& p) const { return true; }
	virtual bool valid_contains(const Vec2& p) const { return true; }
};

struct Segment :public Line {
	explicit Segment():Line() {}
	explicit Segment(const Vec2& _s, const Vec2& _e) :Line(_s, _e) {}
	virtual bool valid_intersect(const Vec2& p)const override {
		if (abs(_s.x - _e.x) < eps && abs(p.x - _s.x) < eps)
			return _s.y <= p.y && p.y <= _e.y;
		if (abs(_s.y - _e.y) < eps && abs(p.y - _s.y) < eps)
			return _s.x <= p.x && p.x <= _e.x;
		return _s <= p && p <= _e;
	}
	virtual bool valid_foot(const Vec2& p)const override { return _s <= p && p <= _e; }
	virtual bool valid_contains(const Vec2& p) const override { return _s <= p && p <= _e; }
};