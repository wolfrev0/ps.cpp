#pragma once
#include "core/base.h"

template<class T> struct RootedTree{
	RootedTree(){}
	RootedTree(const Arr<pair<int,T>>& p):n(sz(p)),r(0),ch(n),p(p),tsz(n),dpt(n),cost(n){
		while(p[r].fi!=r)r=p[r].fi;
		for(int i=0;i<n;i++)
			if(i!=r)
				ch[p[i].fi].pushb(i,p[i].se);
		func(int,f,int x,int d,T c){
			dpt[x]=d,cost[x]=c,tsz[x]=1;
			for(auto [i,w]:ch[x])tsz[x]+=f(i,d+1,c+w);
			return tsz[x];
		};
		f(r,0,0);
	}
	Arr<int> euler(){
		Arr<int> z;
		func(void,f,int x){z.pushb(x);for(auto [i,_]:ch[x])f(i),z.pushb(x);};
		f(r);return z;
	}
	Arr<int> pre(){
		Arr<int> z;
		func(void,f,int x){z.pushb(x);for(auto [i,_]:ch[x])f(i);};
		f(r);return z;
	}
	Arr<int> post(){
		Arr<int> z;
		func(void,f,int x){for(auto [i,_]:ch[x])f(i);z.pushb(x);};
		f(r);return z;
	}
	int n, r;
	Arr<Arr<pair<int, T>>> ch;
	Arr<pair<int, T>> p;
	Arr<int> tsz, dpt;
	Arr<T> cost;
};