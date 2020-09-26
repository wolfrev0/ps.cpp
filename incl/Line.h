#pragma once
#include "Vec2.h"

class LineException {};
class LineSame :public LineException {};

template<typename T>
struct Line {
	Line() :Line(-Vec2<T>::inf(), Vec2<T>::inf()) {}
	Line(const Vec2<T>& s, const Vec2<T>& e) :sv(s), ev(e) { if(sv > ev) swap(sv, ev); }
	
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
	Segment():Line<T>() {}
	Segment(const Vec2<T>& sv, const Vec2<T>& ev) :Line<T>(sv, ev) {}
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

bool onSegment(pint p, pint q, pint r){
	return q.fi <= max(p.fi, r.fi) && q.fi >= min(p.fi, r.fi) && q.se <= max(p.se, r.se) && q.se >= min(p.se, r.se);
}
int orientation(pint p, pint q, pint r){
	int val = (q.se - p.se) * (r.fi - q.fi) - (q.fi - p.fi) * (r.se - q.se);
	if(!val)return 0;
	return val>0?1:2;
}
bool isCross(pint p1, pint q1, pint p2, pint q2) 
{ 
	int o1 = orientation(p1, q1, p2); 
	int o2 = orientation(p1, q1, q2); 
	int o3 = orientation(p2, q2, p1); 
	int o4 = orientation(p2, q2, q1); 
	if (o1 != o2 && o3 != o4) return true; 
	if (!o1 and onSegment(p1, p2, q1)) return true;
	if (!o2 and onSegment(p1, q2, q1)) return true;
	if (!o3 and onSegment(p2, p1, q2)) return true;
	if (!o4 and onSegment(p2, q1, q2)) return true;
	return false; 
}
