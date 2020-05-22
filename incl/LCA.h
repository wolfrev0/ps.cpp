#pragma once
#include "RootedTree.h"

template<typename T>
struct LCA:public RootedTree<T>{
	using P = RootedTree<T>;
	using P::n; using P::p; using P::dpt; using P::cost;

	LCA(const Arr<pair<int,T>>& p):P(p),logn(32-__builtin_clz(n-1)),pp(n,Arr<int>(logn,-1)){
		rep(i,n)
			pp[i][0]=p[i].fi;
	}

	//(2^n)th ancestor of v
	int panc(int v, int n){
		int& ret=pp[v][n];
		return ret!=-1?ret:ret=panc(panc(v,n-1),n-1);
	}

	//nth ancestor or v
	int anc(int v, int n){
		for(;k;k-=1<<lgf(k))
			v=panc(v,i);
		return v;
	}

	int lca(int a, int b){
		if(dpt[a]>dpt[b])
			swap(a,b);
		repi(i,logn)
			if(dpt[panc(b,i)]>=dpt[a])
				b=panc(b,i);
		if(a==b)
			return a;
		repi(i,logn)
			if(panc(a,i)!=panc(b,i))
				a=panc(a,i), b=panc(b,i);
		return panc(a,0);
	}

	int logn;
	Arr<Arr<int>> pp;
};
