#pragma once
#include "core/base.h"

struct Circle{
	int x,y,r;
	Circle():Circle(0,0,0){}
	Circle(int x,int y,int r):x(x),y(y),r(r){}
	bool intersect(const Circle& a){
		int dsq=sq(x-a.x)+sq(y-a.y);
		return sq(max(r,a.r)-min(r,a.r))<=dsq and dsq<=sq(r+a.r);
	}
};