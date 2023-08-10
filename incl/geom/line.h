#pragma once
#include "core/base.h"
#include "geom/vec2.h"
#include "math/numth.h"

class LineException{};
class LineSame:public LineException{};
class LineParallel:public LineException{};

//NOTE: 직선의 방정식과 2by2연립solver
//normalized(),operator==,operator<는 아직 테스트 안된듯?
//Frac<T> 사용 권장
template<class T>
struct Line{
	//ax+by+c=0
	T a,b,c;
	Line(T a,T b,T c):a(a),b(b),c(c){normalize();}
	Line(Vec2<T> a,Vec2<T> b):Line(a.y-b.y,b.x-a.x,-a.y*(b.x-a.x)+a.x*(b.y-a.y)){normalize();}
	Line(T tangent,T yic):Line({0,yic},{0+1,yic+tangent}){normalize();}
	void normalize(){
		int g=gcd(gcd(a,b),c);
		if(mkt(a/g,b/g,c/g)>mkt(-a/g,-b/g,-c/g))
			g*=-1;//더 작은쪽으로 부호 설정
		a/=g,b/=g,c/=g;
	}
	friend strong_ordering operator<=>(const Line&, const Line&)=default;
	bool operator<(const Line& r)const{return mkt(a,b,c)<mkt(r.a,r.b,r.c);}
	T tan()const{return -a/b;}
	T calcY(int x)const{return (-a*x-c)/b;}
	T calcX(int y)const{return (-b*y-c)/a;}
	Vec2<T> foot(Vec2<T> v)const{return {(b*(b*v.x-a*v.y)-a*c)/a*a+b*b,(a*(-b*v.x+a*v.y)-b*c)/a*a+b*b};}
	Vec2<T> project(Vec2<T> v)const{return foot(v);}
	Vec2<T> point(int offset=0)const{return {offset,calcY(offset)};}
	bool contains(Vec2<T> p)const{return p.cross(point(0),point(1))<eps;}
	Vec2<T> intersect(const Line& r)const{
		int det=a*r.b-b*r.a;
		if(det==0){
			if(a*r.c==r.a*c) throw LineSame();
			else throw LineParallel();
		}
		return {(b*r.c-r.b*c)/det,(c*r.a-r.c*a)/det};
	}
};
template<>
Vec2<int> Line<int>::point(int offset)const{
	auto [g,x,y]=xgcd(a,b);
	if(c%g) throw "No integer point";
	return {(x+offset*b/g)*-c/g,(y-offset*a/g)*-c/g};
}
