#pragma once
#include "tree/lichao/lichao_common.h"

template<LiChaoType T, auto id, auto cmp>
struct LiChaoPersi{
	static constexpr int xlo=-inf<int>(), xhi=inf<int>();
	struct Node{
		T v;
		i32 l, r;
		Node(const T v, i32 l, i32 r):v(v),l(l),r(r){}
	};
	Arr<Node> a;
	i32 alloc(T x=id(), i32 l=-1, i32 r=-1){
		a.emplace_back(x,l,r);
		return sz(a)-1;
	}
	i32 insert(i32 ci, T x){return insert(ci, xlo, xhi, x);}
	i32 insert(i32 ci, int cs, int ce, T x){
		if(ci==-1)
			return alloc(x);
		if(ce-cs==1)
			return cmp(a[ci].v,x,cs)?alloc(x):ci;
		int cm=(cs+ce)/2;
		T flo=a[ci].v, fhi=x;
		//x=cs기준 직선의 lo,hi
		if(!cmp(flo,fhi,cs))
			swap(flo,fhi);
		i32 ret;
		if(cmp(flo,fhi,ce)){
			ret=alloc(fhi,a[ci].l,a[ci].r);
		}else if(cmp(flo,fhi,cm)){
			ret=alloc(fhi,a[ci].l,a[ci].r);
			a[ret].r=insert(a[ci].r,cm,ce,flo);
		}else{
			ret=alloc(flo,a[ci].l,a[ci].r);
			a[ret].l=insert(a[ci].l,cs,cm,fhi);
		}
		return ret;
	}

	T q(i32 ci, int x){return q(ci,xlo,xhi,x);}
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