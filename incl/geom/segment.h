#pragma once
#include "geom/vec2.h"

//기하 디버그 팁: 완전이상하게 동작하면 T=f64로 해봐라
template<class T> struct LineLegacy {
	LineLegacy():LineLegacy(-Vec2<T>::inf(), Vec2<T>::inf()) {}
	LineLegacy(const Vec2<T>& s, const Vec2<T>& e):sv(s),ev(e){
		if(sv>ev)swap(sv,ev);
	}

	bool operator==(const LineLegacy& r) const { return tan()=r.tan() && s == r.s; }

	Frac tan() const { return dir().tan(); }
	Vec2<T> dir() const { return ev - sv; }
	Vec2<T> s() const { return sv; }
	Vec2<T> e() const { return ev; }
	void s(Vec2<T>& v) {
		if((sv=v) > ev) swap(sv, ev);
	}
	void e(Vec2<T>& v) {
		if(sv > (ev=v)) swap(sv, ev);
	}

	bool intersect(const LineLegacy& r, Vec2<T>& res) const {
		T det=dir().cross(r.dir());
		if(abs(det) < eps) {
			if(abs((r.sv - sv).cross(ev - sv)) < eps){
				return line_same_handler(r,res);
			}else
				return false;
		}
		res=sv + dir() * ((r.sv - sv).cross(r.dir()) / det);
		return valid_intersect(res) && r.valid_intersect(res);
	}

	bool intersect_det(const LineLegacy& r) const {
		T det1=sv.ccw(ev, r.sv) * sv.ccw(ev, r.ev);
		T det2=r.sv.ccw(r.ev, sv) * r.sv.ccw(r.ev, ev);
		if(!det1 && !det2) return ev >= r.sv && r.ev >= sv;
		return det1 <= 0 && det2 <= 0;
	}

	bool perpend_foot(const Vec2<T>& p, Vec2<T>& res) const {
		return valid_foot(res=sv + dir().project(p - sv));
	}
	bool contains(const Vec2<T>& v) const {
		return valid_contains(v) && v.ccw(sv, ev) == 0;
	}

	T dist(const Vec2<T>& p) const {
		return abs((ev - p).cross(sv - p) / (ev - sv).len());
	}
	Vec2<T> sv, ev;

private:
	virtual bool valid_intersect(const Vec2<T>& p) const { return true; }
	virtual bool valid_foot(const Vec2<T>& p) const { return true; }
	virtual bool valid_contains(const Vec2<T>& p) const { return true; }
	virtual bool line_same_handler(const LineLegacy& a,Vec2<T>&res)const{throw LineSame();}
};

template<class T> struct Segment : public LineLegacy<T> {
	using LineLegacy<T>::sv, LineLegacy<T>::ev;
	Segment() : LineLegacy<T>() {}
	Segment(const Vec2<T>& sv, const Vec2<T>& ev) : LineLegacy<T>(sv, ev) {}
	f64 len()const{return (sv-ev).len();}
	bool is_valid(const Vec2<T>& p) const {
		return sv.x-eps <= p.x && p.x <= ev.x+eps && min(sv.y, ev.y)-eps <= p.y &&
		       p.y <= max(sv.y, ev.y)+eps;
	}
	virtual bool valid_intersect(const Vec2<T>& p) const override {
		if(abs(sv.x - ev.x) < eps)
			return min(sv.y, ev.y) -eps<= p.y && p.y <= max(sv.y, ev.y)+eps;
		if(abs(sv.y - ev.y) < eps)
			return sv.x-eps <= p.x && p.x <= ev.x+eps;
		return is_valid(p);
	}
	virtual bool valid_foot(const Vec2<T>& p) const override {
		return is_valid(p);
	}
	virtual bool valid_contains(const Vec2<T>& p) const override {
		return is_valid(p);
	}
	virtual bool LineLegacy_same_handler(const LineLegacy<T>& a, Vec2<T>& res)const override{
		Segment<T> seg1=*this,seg2={a.sv,a.ev};
		if(seg1.len()<seg2.len())swap(seg1,seg2);
		if(seg1.sv==seg2.sv and !seg1.is_valid(seg2.ev) or seg1.sv==seg2.ev and !seg1.is_valid(seg2.sv)){res=sv;return true;}
		if(seg1.ev==seg2.sv and !seg1.is_valid(seg2.ev) or seg1.ev==seg2.ev and !seg1.is_valid(seg2.sv)){res=ev;return true;}
		if(!seg1.is_valid(seg2.sv) and !seg1.is_valid(seg2.ev)) return false;
		throw LineSame();
	}
};

//https://www.geeksforgeeks.org/check-if-two-given-LineLegacy-segments-intersect/
bool onSegment(pint p, pint q, pint r){return q.fi<=max(p.fi,r.fi)&&q.fi>=min(p.fi,r.fi)&&q.se<=max(p.se,r.se)&&q.se>=min(p.se,r.se);}
int orientation(pint p, pint q, pint r){
	int val=(q.se-p.se)*(r.fi-q.fi)-(q.fi-p.fi)*(r.se-q.se);
	return !val?0:(val>0?1:-1);
}
bool isCross(pint p1, pint q1, pint p2, pint q2){
	int o1=orientation(p1, q1, p2);
	int o2=orientation(p1, q1, q2);
	int o3=orientation(p2, q2, p1);
	int o4=orientation(p2, q2, q1);
	if(o1!=o2 and o3!=o4) return true;
	if(!o1 and onSegment(p1, p2, q1)) return true;
	if(!o2 and onSegment(p1, q2, q1)) return true;
	if(!o3 and onSegment(p2, p1, q2)) return true;
	if(!o4 and onSegment(p2, q1, q2)) return true;
	return false;
}
