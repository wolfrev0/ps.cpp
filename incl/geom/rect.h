#pragma once
#include "core.h"

template<class T> struct Rect{
	T x1,y1,x2,y2;
	Rect(T x1,T y1,T x2,T y2):x1(x1),y1(y1),x2(x2),y2(y2){}

	T width()const{return x2-x1/*+1*/;}
	T height()const{return y2-y1/*+1*/;}

	//if not intersected, ret.valid()==false
	Rect intersect(const Rect &r)const{
		return Rect(max(x1,r.x1),max(y1,r.y1),min(x2,r.x2),min(y2,r.y2));
	}
	bool valid()const{return x1<=x2 and y1<=y2;}
	Rect expand(T r){return{x1-r,y1-r,x1+r,y1+r};}
};
