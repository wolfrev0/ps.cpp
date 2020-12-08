#pragma once
#include "Core.h"
#include "Monoid.h"

template<class T, class Q, class U, int n>
struct PST{
	PST(T v):v(v),l(id()),r(id()){}
	PST(PST *l, PST *r):v(Q::f(l->v,r->v)),l(l),r(r){}
	PST* upd(int i, T val){ return upd(0,n,i,val); }
	T q(int s, int e){ return q(0,n,s,e); }
	static PST* id(){ static PST* a; if(!a)a=new PST(),a->l=a->r=a; return a; }
private:
	PST():v(Q::id()){};
	PST* upd(int cs, int ce, int i, T val){
		int cm=(cs+ce)>>1;
		if(i<=cs and ce<=i+1) return new PST(U::f(v,val));
		if(ce<=i or i+1<=cs) return this;
		return new PST(l->upd(cs,cm,i,val),r->upd(cm,ce,i,val));
	}
	T q(int cs, int ce, int s, int e){
		int cm=(cs+ce)>>1;
		if(s<=cs and ce<=e) return v;
		if(ce<=s or e<=cs) return Q::id();
		return Q::f(l->q(cs,cm,s,e),r->q(cm,ce,s,e));
	}
	T v; PST *l, *r;
};
//USAGE: https://codeforces.com/contest/961/submission/100705507