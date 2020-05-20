#pragma once
#include "Vec2.h"

class LineException {};
class LineSame :public LineException {};

template<typename T>
struct Line {
	explicit Line() :Line(-Vec2<T>::inf(), Vec2<T>::inf()) {}
	explicit Line(const Vec2<T>& s, const Vec2<T>& e) :sv(s), ev(e) { if(sv > ev) swap(sv, ev); }
	
	bool operator==(const Line& r)const{return tan()=r.tan() && s==r.s;}

	Frac tan()const{return dir().tan();}
	Vec2<T> dir()const { return ev - sv; }
	Vec2<T> s()const{return sv;}
	Vec2<T> e()const{return ev;}
	void s(Vec2<T>& v){ if ((sv=v) > ev) swap(sv, ev); }
	void e(Vec2<T>& v){ if (sv > (ev=v)) swap(sv, ev); }

	bool intersect(const Line& r, Vec2<T>& res) const {
		T det = dir().cross(r.dir());
		if (abs(det) < eps){
			if (abs((r.sv - sv).cross(ev - sv)) < eps)
				return false;//throw LineSame();
			else
				return false;
		}
		res = sv + dir()*((r.sv - sv).cross(r.dir()) / det);
		return valid_intersect(res) && r.valid_intersect(res);
	}

	bool intersect_det(const Line& r) const {
		T det1 = sv.ccw(ev, r.sv) * sv.ccw(ev, r.ev);
		T det2 = r.sv.ccw(r.ev, sv) * r.sv.ccw(r.ev, ev);
		if (!det1 && !det2)
			return ev >= r.sv && r.ev >= sv;
		return det1 <= 0 && det2 <= 0;
	}

	bool perpend_foot(const Vec2<T>& p, Vec2<T>& res) const { return valid_foot(res=sv+dir().project(p - sv)); }
	bool contains(const Vec2<T>& v) const { return valid_contains(v) && v.ccw(sv, ev) == 0; }
	
	T dist(const Vec2<T>& p)const{return abs((ev-p).cross(sv-p)/(ev-sv).len());}
protected:
	Vec2<T> sv, ev;
private:
	virtual bool valid_intersect(const Vec2<T>& p) const { return true; }
	virtual bool valid_foot(const Vec2<T>& p) const { return true; }
	virtual bool valid_contains(const Vec2<T>& p) const { return true; }
};

template<typename T>
struct Segment :public Line<T> {
	using Line<T>::sv, Line<T>::ev;
	explicit Segment():Line<T>() {}
	explicit Segment(const Vec2<T>& sv, const Vec2<T>& ev) :Line<T>(sv, ev) {}
	bool is_valid(const Vec2<T>& p)const{ return sv.x<=p.x&&p.x<=ev.x && min(sv.y,ev.y)<=p.y&&p.y<=max(sv.y,ev.y); }
	virtual bool valid_intersect(const Vec2<T>& p)const override {
		if (abs(sv.x - ev.x) < eps)
			return min(sv.y,ev.y)<=p.y && p.y<=max(sv.y,ev.y);
		if (abs(sv.y - ev.y) < eps)
			return sv.x <= p.x && p.x <= ev.x;
		return is_valid(p);
	}
	virtual bool valid_foot(const Vec2<T>& p)const override { return is_valid(p); }
	virtual bool valid_contains(const Vec2<T>& p) const override { return is_valid(p); }
};