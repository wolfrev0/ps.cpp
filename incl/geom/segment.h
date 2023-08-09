#pragma once
#include "geom/vec2.h"
#include "geom/line.h"

//Segment=Line with constraint s.t. s[x]<=x<=e[x]&&s[y]<=y<=e[y]
template<class T> struct Segment:public Line<T>{
	Vec2<T> s,e;
	Segment(Vec2<T> s,Vec2<T> e):
		Line<T>(s,e),
		s(min(s.x,e.x),min(s.y,e.y)),
		e(max(s.x,e.x),max(s.y,e.y)){}
	
	fp len()const{return (s-e).len();}
	bool contains(Vec2<T> v)const{return Line<T>::contains(v) and boxed({s,e},v);}
	Vec2<T> intersect(const Segment& r)const{
		auto ret=Line<T>::intersect(r);
		if(!boxed({s,e},ret))
			throw "No cross";
		return ret;
	}
	//https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
	bool isIntersect(const Segment& r)const{
		auto p1=s, q1=e, p2=r.s, q2=r.e;
		T o1=cross(p1,q1,p2);
		T o2=cross(p1,q1,q2);
		T o3=cross(p2,q2,p1);
		T o4=cross(p2,q2,q1);
		if(o1!=o2 and o3!=o4)return true;
		if(!o1 and boxed({p1,q1},p2))return true;
		if(!o2 and boxed({p1,q1},q2))return true;
		if(!o3 and boxed({p2,q2},p1))return true;
		if(!o4 and boxed({p2,q2},q1))return true;
		return false;
	}
};
