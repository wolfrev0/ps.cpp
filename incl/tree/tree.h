#pragma once
#include "core/base.h"

template<class T> struct Tree{
	Tree(int n=0):n(n),g(n){}
	void add_edge(int s,int e,T w){g[s].emplace_back(e,w),g[e].emplace_back(s,w);}
	T diameter()const{
		auto x=furthest(0,0,0).se;
		return furthest(x,x,0).fi;
	}
	pint diameterv()const{
		auto x=furthest(0,0,0).se;
		auto y=furthest(x,x,0).se;
		return {x,y};
	}

	//Usage: https://www.acmicpc.net/problem/13514
	//centroid_tree에 centroid정보만 있는데,
	//부모정점이 어느 자식간선 타는지 정보도 같이 줘야 유용할듯?
	//x,cent[x],y,cent[y] 정보를 다 알 수 있도록 코딩?
	pair<Tree<T>,int> centroid_tree(){
		Arr<char> av(n,true);
		Arr<int> tsz(n);
		func(int,upd_tsz,int x,int p){
			tsz[x]=1;
			for(auto [i,_]:g[x])
				if(av[i] and i!=p)
					tsz[x]+=upd_tsz(i,x);
			return tsz[x];
		};
		func(int,centroid,int x,int p,int sztot){
			for(auto [i,_]:g[x])
				if(av[i] and i!=p and tsz[i]*2>=sztot)
					return centroid(i,x,sztot);
			return x;
		};
		Tree<T> ct(n);
		func(int,f,int x){//ret=centroid
			upd_tsz(x,x);
			x=centroid(x,x,tsz[x]);
			av[x]=false;
			for(auto [i,_]:g[x])
				if(av[i])
					ct.add_edge(x,f(i),0);
			return x;
		};
		int r=f(0);
		return {move(ct),r};
	}

	int n;
	Arr<Arr<pair<int, T>>> g;

private:
	pint furthest(int x,int p,int d)const{
		pint r={d,x};
		for(auto[i,w]:g[x])
			if(i!=p)
				r=max(r,furthest(i,x,d+w));
		return r;
	}
};

template<class T> struct RootedTree{
	RootedTree(){}

	RootedTree(const Tree<T>& t,int r,Arr<T> vw={}):n(t.n),r(r),ch(t.n),p(t.n),tsz(t.n),dpt(t.n),cost(t.n){
		func(int,rootize,int x,int y,int yw,int d,T c){
			p[x]={y,yw},dpt[x]=d,cost[x]=c,tsz[x]=1;
			if(x!=y)ch[y].emplace_back(x,yw);
			for(auto [i,ew]:t.g[x])
				if(i!=y){
					T w=sz(vw)?vw[i]:ew;
					tsz[x]+=rootize(i,x,w,d+1,c+w);
				}
			return tsz[x];
		};
		rootize(r,r,sz(vw)?vw[r]:0,0,0);
	}
	Arr<int> euler(){
		Arr<int> z;
		func(void,f,int x){z.emplace_back(x);for(auto [i,_]:ch[x])f(i),z.emplace_back(x);};
		f(r);return z;
	}
	Arr<int> pre(){
		Arr<int> z;
		func(void,f,int x){z.emplace_back(x);for(auto [i,_]:ch[x])f(i);};
		f(r);return z;
	}
	Arr<int> post(){
		Arr<int> z;
		func(void,f,int x){for(auto [i,_]:ch[x])f(i);z.emplace_back(x);};
		f(r);return z;
	}
	int n, r;
	Arr<Arr<pair<int, T>>> ch;
	Arr<pair<int, T>> p;
	Arr<int> tsz, dpt;
	Arr<T> cost;
};
