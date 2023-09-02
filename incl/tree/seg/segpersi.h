#pragma once
#include "core/base.h"
#include "math/struct/monoid.h"

//example https://www.acmicpc.net/source/59898625
template<Monoid Q,auto fupd> struct SegPersi{
	using T=decltype(Q::id());
	const static int xlo=-inf<int>();
	const static int xhi=inf<int>();
	struct Node{
		T v=Q::id();
		i32 l=-1,r=-1;
	};
	Arr<Node> a;
	i32 alloc(T v=Q::id()){a.emplace_back(Node{v});return sz(a)-1;}
	i32 upd(i32 ver, int i,T x,int cs=xlo,int ce=xhi){
		if(ce<=i or i+1<=cs) return ver;
		if(i<=cs and ce<=i+1) return alloc(fupd(a[ver].v,x));
		int cm=(cs+ce)/2;
		auto ret=alloc();
		a[ret].l=upd(a[ver].l,i,x,cs,cm);
		a[ret].r=upd(a[ver].r,i,x,cm,ce);
		T lv=Q::id(), rv=Q::id();
		if(a[ret].l!=-1) lv=a[a[ret].l].v;
		if(a[ret].r!=-1) rv=a[a[ret].r].v;
		a[ret].v=Q::f(lv,rv);
		return ret;
	}
	T q(i32 ver, int s,int e, int cs=xlo, int ce=xhi){
		if(ver==-1 or ce<=s or e<=cs) return Q::id();
		if(s<=cs and ce<=e) return a[ver].v;
		int cm=(cs+ce)/2;
		return Q::f(q(a[ver].l,s,e,cs,cm),q(a[ver].r,s,e,cm,ce));
	}
};
//USAGE: boj.kr/14898
//USAGE: https://codeforces.com/contest/961/submission/100706299
