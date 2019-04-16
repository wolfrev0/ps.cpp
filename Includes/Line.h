#pragma once
#include "Vec2.h"

class LineException {};
class LineSame :public LineException {};

template<typename T>
struct Line {
	explicit Line() :Line(-Vec2<T>::inf(), Vec2<T>::inf()) {}
	explicit Line(const Vec2<T>& s, const Vec2<T>& e) :_s(s), _e(e) { if(_s > _e) swap(_s, _e); }
	Vec2<T> dir()const { return _e - _s; }

	Vec2<T> s()const{return _s;}
	Vec2<T> e()const{return _e;}
	void s(Vec2<T>& v){ if ((_s=v) > _e) swap(_s, _e); }
	void e(Vec2<T>& v){ if (_s > (_e=v)) swap(_s, _e); }

	bool intersect(const Line& r, Vec2<T>& res) const {
		T det = dir().cross(r.dir());
		if (abs(det) < eps){
			if (abs((r._s - _s).cross(_e - _s)) < eps)
				throw LineSame();
			else
				return false;
		}
		res = _s + dir()*((r._s - _s).cross(r.dir()) / det);
		return valid_intersect(res) && r.valid_intersect(res);
	}

	bool intersect_det(const Line& r) const {
		T det1 = _s.ccw(_e, r._s) * _s.ccw(_e, r._e);
		T det2 = r._s.ccw(r._e, _s) * r._s.ccw(r._e, _e);
		if (!det1 && !det2)
			return _e >= r._s && r._e >= _s;
		return det1 <= 0 && det2 <= 0;
	}

	bool perpend_foot(const Vec2<T>& p, Vec2<T>& res) const {
		return valid_foot(res=_s+dir().project(p - _s));
	}

	bool contains(const Vec2<T>& v) const {
		return valid_contains(v) && v.ccw(_s, _e) == 0;
	}
protected:
	Vec2<T> _s, _e;
private:
	virtual bool valid_intersect(const Vec2<T>& p) const { return true; }
	virtual bool valid_foot(const Vec2<T>& p) const { return true; }
	virtual bool valid_contains(const Vec2<T>& p) const { return true; }
};

template<typename T>
struct Segment :public Line<T> {
	using Line<T>::_s;
	using Line<T>::_e;
	explicit Segment():Line<T>() {}
	explicit Segment(const Vec2<T>& _s, const Vec2<T>& _e) :Line<T>(_s, _e) {}
	virtual bool valid_intersect(const Vec2<T>& p)const override {
		if (abs(_s.x - _e.x) < eps && abs(p.x - _s.x) < eps)
			return _s.y <= p.y && p.y <= _e.y;
		if (abs(_s.y - _e.y) < eps && abs(p.y - _s.y) < eps)
			return _s.x <= p.x && p.x <= _e.x;
		return _s <= p && p <= _e;
	}
	virtual bool valid_foot(const Vec2<T>& p)const override { return _s <= p && p <= _e; }
	virtual bool valid_contains(const Vec2<T>& p) const override { return _s <= p && p <= _e; }
};