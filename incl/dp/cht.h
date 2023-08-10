#pragma once

#include "geom/line.h"
#include "misc/i128.h"

// if max, increasing tangent, increasing x query
// if min, decreasing tangent, increasing x query
template<bool isMin>
struct CHTint{
	Arr<Line<i64>> stk;
	//3x3 determinant로 교점안구하고 cht가능
	//https://www.geeksforgeeks.org/check-three-straight-lines-concurrent-not/
	//point-line duality로 y=ax+b==(a,-b)형태 변환하고 ccw사용하는것도 가능
	i128 det(Line<i64> x,Line<i64> y,Line<i64> z){
		return (i128)x.a*y.b*z.c+(i128)x.b*y.c*z.a+(i128)x.c*y.a*z.b
			-(i128)x.c*y.b*z.a-(i128)x.b*y.a*z.c-(i128)x.a*y.c*z.b;
	}
	void add(Line<i64> a){
		if constexpr(isMin)
			assert(stk.empty() or stk.back().tan()>=a.tan());
		else
			assert(stk.empty() or stk.back().tan()<=a.tan());
		while(sz(stk)>=2 and det(stk[-2],stk[-1],a)*(isMin?-1:1)>=0)
			stk.pop_back();
		if(sz(stk)and stk.back().tan()==a.tan()){
			if(stk.back().calcY(0)<a.calcY(0))
				stk.back()=a;
			return;
		}
		stk.emplace_back(a);
	}
	int i=0,px=-inf<int>();
	int q(int x){
		assert(px<=x), px=x;
		while(i+1<sz(stk)){
			if(x<stk[i].intersect(stk[i+1]).x)
				break;
			i++;
		};
		return stk[i].calcY(x);
	}
};