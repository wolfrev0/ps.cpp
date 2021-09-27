#pragma once
#include "core/base.h"

class LineException{};
class LineSame:public LineException{};
class LineParallel:public LineException{};

//NOTE: 직선의 방정식과 2by2연립solver
struct Line{
	//ax+by+c=0
	int a,b,c;
	Line(int a,int b,int c):a(a),b(b),c(c){}
	Line(pint a,pint b):Line(a.se-b.se,b.fi-a.fi,-a.se*(b.fi-a.fi)+a.fi*(b.se-a.se)){}
	Line(pint tangent, pint pt):Line(pt,mkp(pt.fi+tangent.fi,pt.se-tangent.se)){}
	bool operator==(const Line&r)const{return mkt(a,b,c)==mkt(r.a,r.b,r.c) or mkt(-a,-b,-c)==mkt(r.a,r.b,r.c);}
	pint tan()const{return !b?pint{1,0}:(b>=0?pint{-a,b}:pint{a,-b});}//기울기=[0]/[1]
	tint intersect(const Line& r)const{
		int det=a*r.b-b*r.a;
		if(det==0){//det=0
			if(a*r.c==r.a*c) throw LineSame();//a/r.a==c/r.c
			else throw LineParallel();
		}
		return {(b*r.c-r.b*c),(c*r.a-r.c*a),det};//교점=([0]/[2],[1]/[2])
	}
	tint foot(pint v){return {b*(b*v.fi-a*v.se)-a*c,a*(-b*v.fi+a*v.se)-b*c,a*a+b*b};}//점=([0]/[2],[1]/[2])
	pint calY(int x){return {-a*x-c,b};}//val=[0]/[1]
};

ostream& operator<<(ostream& s,const Line& x){return s<<showpos<<x.a<<"x"<<x.b<<"y"<<x.c<<"=0";}