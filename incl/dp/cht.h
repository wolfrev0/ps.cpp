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



//Between for any of two different function, the number of intersection is no more than 1.
//T: callable data type, Line<long double> recommended
//T id(): identity element of T
//bool cmp(T l, T r, fp x): Node will choose larger one by comparing l(x) and r(x).
//max lichao: id=Line(0,-inf), cmp(l,r,x)=l(x)<r(x)
//min lichao: id=Line(0,inf), cmp(l,r,x)=r(x)<l(x)

// NOTE: Integer lichao is bad idea. It requires i128 in most cases and perform bad.
// 반평면땅따먹기(12795)는 i128로 풀수도 없음. 아래는 나무자르기(13263)결과
// i128(664ms): https://www.acmicpc.net/source/64946225
// long double(212ms): https://www.acmicpc.net/source/64946268
template<typename T> concept LiChaoType=requires(T t){
	t(1);
};
template<LiChaoType T, class I, auto id, auto cmp>
struct LiChao{
	static constexpr fp eps=1.1;
	static constexpr I xlo=-inf<int>(), xhi=inf<int>();
	struct Node{
		T v;
		signed l=-1, r=-1;
		Node(const T v=id()):v(v){}
	};
	Arr<Node> a={Node()};
	void add(T x){add(0, xlo, xhi, x);}
	void add(signed idx, I cs, I ce, T x){
		if(ce-cs<=eps){
			if(cmp(a[idx].v,x,cs))
				a[idx].v=x;
			return;
		}
		I cm=(cs+ce)/2;
		if(a[idx].l==-1)a[idx].l=sz(a),a.emplace_back(a[idx].v);
		if(a[idx].r==-1)a[idx].r=sz(a),a.emplace_back(a[idx].v);
		T flo=a[idx].v, fhi=x;
		//x=cs기준 직선의 lo,hi
		if(!cmp(flo,fhi,cs))
			swap(flo,fhi);
		if(cmp(flo,fhi,ce)) a[idx].v=fhi;
		else if(cmp(flo,fhi,cm)) a[idx].v=fhi,add(a[idx].r,cm,ce,flo);
		else a[idx].v=flo,add(a[idx].l,cs,cm,fhi);
		//NOTE: flo를 저장할땐 fhi를 넘기고, fhi를 저장할땐 flo를 넘기는 이유는
		//나중에 쿼리할때, v에 저장된것은 현재 노드에서 체크하고, 남은건 아래로 내려가서 체크해야 하기 때문.
		//즉, 쿼리방식을 잘 이해하고 보면 update방식도 쉽게 이해할 수 있다.
		//이부분이 제일 이해하기 tricky한 부분인거같다.
	}

	T q(I x){return q(0,xlo,xhi,x);}
	T q(signed idx, I cs, I ce, I x){
		if(idx<0 or idx>=sz(a))
			return id();
		I cm=(cs+ce)/2;
		auto ret=a[idx].v;
		if(x<cm){
			auto cur = q(a[idx].l,cs,cm,x);
			if(cmp(ret,cur,x))
				ret=cur;
		}else{
			auto cur = q(a[idx].r,cm,ce,x);
			if(cmp(ret,cur,x))
				ret=cur;
		}
		return ret;
	}
};