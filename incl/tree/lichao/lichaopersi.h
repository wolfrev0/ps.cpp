#pragma once
#include "tree/lichao/lichao_common.h"

template<LiChaoType T, auto id, auto cmp>
struct LiChaoPersi{
	static constexpr int xlo=-inf<int>(), xhi=inf<int>();
	struct Node{
		T v;
		signed l, r;
		Node(const T v, signed l, signed r):v(v),l(l),r(r){}
	};
	Arr<Node> a;
	signed alloc(T x=id(), signed l=-1, signed r=-1){
		a.emplace_back(x,l,r);
		return sz(a)-1;
	}
	signed insert(signed idx, T x){return insert(idx, xlo, xhi, x);}
	signed insert(signed idx, int cs, int ce, T x){
		if(idx==-1)
			return alloc(x);
		if(ce-cs==1)
			return cmp(a[idx].v,x,cs)?alloc(x):idx;
		int cm=(cs+ce)/2;
		T flo=a[idx].v, fhi=x;
		//x=cs기준 직선의 lo,hi
		if(!cmp(flo,fhi,cs))
			swap(flo,fhi);
		signed ret;
		if(cmp(flo,fhi,ce)){
			ret=alloc(fhi,a[idx].l,a[idx].r);
		}else if(cmp(flo,fhi,cm)){
			ret=alloc(fhi,a[idx].l,a[idx].r);
			a[ret].r=insert(a[idx].r,cm,ce,flo);
		}else{
			ret=alloc(flo,a[idx].l,a[idx].r);
			a[ret].l=insert(a[idx].l,cs,cm,fhi);
		}
		return ret;
	}

	T q(signed idx, int x){return q(idx,xlo,xhi,x);}
	T q(signed idx, int cs, int ce, int x){
		if(idx<0 or idx>=sz(a))
			return id();
		int cm=(cs+ce)/2;
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