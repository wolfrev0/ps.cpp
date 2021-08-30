#pragma once
#include "core/base.h"

template<class T> struct Tree{
	Tree(int n=0):n(n),g(n){}
	void add_edge(int s,int e,T w){g[s].pushb(e,w),g[e].pushb(s,w);}
	T diameter()const{
		auto x=furthest(0,0,0).se;
		return furthest(x,x,0).fi;
	}
	pint diameterv()const{
		auto x=furthest(0,0,0).se;
		auto y=furthest(x,x,0).se;
		return {x,y};
	}
	Arr<pair<int,T>> rootize(int r)const{
		Arr<pair<int,T>> res(n,{r,inf<int>()});
		func(void,dfs,int r,int p){
			for(auto [i,w]:g[r])
				if(i!=p)
					res[i]={r,w},dfs(i,r);
		};
		dfs(r,r);
		return res;
	}
	Arr<pair<int,T>> rootize(int r,const Arr<T>& vtxw)const{
		Arr<pair<int,T>> res(n,{r,vtxw[r]});
		func(void,dfs,int r,int p){
			for(auto [i,_]:g[r])
				if(i!=p)
					res[i]={r,vtxw[i]},dfs(i,r);
		};
		dfs(r,r);
		return res;
	}

	//Usage: https://www.acmicpc.net/submit/22360/31799657
	Arr<int> centroid_ord()const{
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
		Arr<int> ret;
		func(void,f,int x){
			upd_tsz(x,x);
			x=centroid(x,x,tsz[x]);
			ret.pushb(x);
			av[x]=false;
			for(auto [i,_]:g[x])
				if(av[i])
					f(i);
		};
		f(0);
		return ret;
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