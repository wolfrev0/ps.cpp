#pragma once
#include "tree/lichao/lichao_common.h"

template<LiChaoType T, auto id, auto cmp>
struct LiChao{
	static constexpr fp eps=1.1;
	static constexpr int xlo=-inf<int>(), xhi=inf<int>();
	struct Node{
		T v;
		i32 l=-1, r=-1;
		Node(const T v=id()):v(v){}
	};
	Arr<Node> a;
	LiChao(){alloc();}
	int alloc(T v=id()){a.emplace_back(v); return sz(a)-1;}
	void insert(T x){insert(0, xlo, xhi, x);}
	i32 insert(i32 ci, int cs, int ce, T x){
		if(ci==-1)
			return alloc(x);
		if(ce-cs<=eps){
			if(cmp(a[ci].v,x,cs))
				a[ci].v=x;
			return ci;
		}
		int cm=(cs+ce)/2;
		T flo=a[ci].v, fhi=x;
		//x=cs기준 직선의 lo,hi
		if(!cmp(flo,fhi,cs))
			swap(flo,fhi);
		if(cmp(flo,fhi,ce)){
			a[ci].v=fhi;
		}else if(cmp(flo,fhi,cm)){
			a[ci].v=fhi;
			a[ci].r=insert(a[ci].r,cm,ce,flo);
		}else{
			a[ci].v=flo;
			a[ci].l=insert(a[ci].l,cs,cm,fhi);
		}
		return ci;
		//NOTE: flo를 저장할땐 fhi를 넘기고, fhi를 저장할땐 flo를 넘기는 이유는
		//나중에 쿼리할때, v에 저장된것은 현재 노드에서 체크하고, 남은건 아래로 내려가서 체크해야 하기 때문.
		//즉, 쿼리방식을 잘 이해하고 보면 update방식도 쉽게 이해할 수 있다.
		//이부분이 제일 이해하기 tricky한 부분인거같다.
	}

	T q(int x){return q(0,xlo,xhi,x);}
	T q(i32 ci, int cs, int ce, int x){
		if(ci<0 or ci>=sz(a))
			return id();
		int cm=(cs+ce)/2;
		auto ret=a[ci].v;
		if(x<cm){
			auto cur = q(a[ci].l,cs,cm,x);
			if(cmp(ret,cur,x))
				ret=cur;
		}else{
			auto cur = q(a[ci].r,cm,ce,x);
			if(cmp(ret,cur,x))
				ret=cur;
		}
		return ret;
	}
};