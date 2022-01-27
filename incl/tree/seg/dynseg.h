#pragma once
#include "core/base.h"
#include "math/monoid.h"

template<Monoid Q, Monoid U, int xlo=0,int xhi=inf<signed>()>
struct DynSeg{
	using T=decltype(Q::id());
	T v=Q::id();
	DynSeg *l{},*r{};
	~DynSeg(){if(l)delete l; if(r)delete r;}

	T upd(int i, T x, int cs=xlo, int ce=xhi){
		if(ce<=i or i+1<=cs)return v;
		if(i<=cs and ce<=i+1)return v=U::f(v,x);
		int cm=(cs+ce)/2;
		if(!l)l=new DynSeg;
		if(!r)r=new DynSeg;
		return v=Q::f(l->upd(i,x,cs,cm),r->upd(i,x,cm,ce));
	}
	T q(int s,int e, int cs=xlo, int ce=xhi){
		if(ce<=s or e<=cs)return Q::id();
		if(s<=cs and ce<=e) return v;
		int cm=(cs+ce)/2;
		if(!l)l=new DynSeg;
		if(!r)r=new DynSeg;
		return Q::f(l->q(s,e,cs,cm),r->q(s,e,cm,ce));
	}
};