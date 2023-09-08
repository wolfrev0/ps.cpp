#pragma once
#include "core/base.h"
#include "math/struct/frac.h"

//기하 디버그 팁: 완전이상하게 동작하면 T=f64로 해봐라
template<class T> struct Vec2{
	T x,y;
	Vec2():Vec2(0,0){}
	Vec2(T x,T y):x(x),y(y){}
	Vec2 operator+(const Vec2& r)const{return {x+r.x,y+r.y};}
	Vec2 operator-()const{return {-x,-y};}
	Vec2 operator-(const Vec2& r)const{return *this+-r;}
	Vec2 operator*(T r)const{return {x*r,y*r};}
	Vec2 operator/(T r)const{return {x/r,y/r};}
	Vec2 operator+=(const Vec2& r){return *this=*this+r;}
	Vec2 operator-=(const Vec2& r){return *this=*this-r;}
	Vec2 operator*=(T r){return *this=*this*r;}
	Vec2 operator/=(T r){return *this=*this/r;}
	friend strong_ordering operator<=>(const Vec2&, const Vec2&)=default;
	fp len()const{return hypot(x,y);}
	T lensq()const{return dot(*this);}
	T taxi()const{return abs(x)+abs(y);}
	Vec2 normalized()const{return *this/len();}
	T dot(const Vec2& r)const{return x*r.x+y*r.y;}
	T dot(const Vec2& a,const Vec2& b)const{return (a-*this).dot(b-*this);}
	T cross(const Vec2& r)const{return x*r.y-y*r.x;}
	T cross(const Vec2& a,const Vec2& b)const{return (a-*this).cross(b-*this);}
	T ccw(const Vec2& a,const Vec2& b)const{return cross(a,b)?cross(a,b)/abs(cross(a,b)):0;}
	fp angle()const{return atan2(-y,-x)+pi;}
	Frac<T> tan()const{return x==0?Frac<T>{1,0}:Frac<T>{y,x};}
	Vec2 project(const Vec2& p)const{Vec2 base=normalized();return base*base.dot(p);}
	Vec2 ortho()const{return Vec2(y,-x);}
	Vec2 rot(double rad)const{return {cos(rad)*x-sin(rad)*y,sin(rad)*x+cos(rad)*y};}
	Vec2 rot(double s,double c)const{return{c*x-s*y,s*x+c*y};}
	Vec2 rot90()const{return {y,-x};}
	static Vec2 inf(){return{::inf<T>(),::inf<T>()};}
	static bool cmpccw(const Vec2& base, const Vec2& l,const Vec2& r){
		T val=base.ccw(l,r);
		// base should be left-bottom or bottom-left.
		// More precisely, It doesn't matter if base is on convex hull.
		// If it isn't, for some order a[0]<a[1]<...<a[n-1], a[n-1]<a[0] is also true.
		// To prevent it, degree of (a[0]-base) to (a[-1]-base) should be less than 180.
		assert(
			base<=l&&base<=r or
			mkp(base.y,base.x)<=mkp(l.y,l.x)&&mkp(base.y,base.x)<=mkp(r.y,r.x));
		if(!val)
			return (l-base).lensq()<(r-base).lensq();
		return val>0;
	}
};

template<typename T>
istream& operator>>(istream& s,Vec2<T>& v){return s>>v.x>>v.y;}
template<typename T>
ostream& operator<<(ostream& s,const Vec2<T>& v){return osprint(s,'(',v.x,',',v.y,')');}
template<typename T>
T cross(const Vec2<T>& a,const Vec2<T>& b,const Vec2<T>& c){return a.cross(b,c);}
template<typename T>
T boxed(const pair<Vec2<T>,Vec2<T>>& box,const Vec2<T>& p){
	return min(box.fi.x,box.se.x)<=p.x&&p.x<=max(box.fi.x,box.se.x)
			&&min(box.fi.y,box.se.y)<=p.y&&p.y<=max(box.fi.y,box.se.y);
}
