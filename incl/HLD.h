#pragma once
#include "RootedTree.h"

template<class T>
struct HLD: public RootedTree<T>{
	using RT=RootedTree<T>; using RT::n; using RT::r; using RT::p; using RT::ch; using RT::dpt;
	HLD(){}
	HLD(const Arr<pair<int,T>>& pi)
	:RT(pi), cn(n), top(n){
		int ccn=0;
		dfs_hld(r, ccn);
		top[0]=r;
	}

	int lca(int a, int b){
		while(cn[a]!=cn[b]){
			if(dpt[top[cn[a]]]<dpt[top[cn[b]]]) b=p[top[cn[b]]].fi;
			else a=p[top[cn[a]]].fi;
		}
		return dpt[a]<dpt[b]?a:b;
	}
protected:
	Arr<int> cn,top;//chain number, top of the chain

	void dfs_hld(int cur, int& ccn){
		if(sz(ch[cur]))
			swap(ch[cur].front(), *max_element(all(ch[cur]),[this](auto a, auto b){return this->tsz[a.fi]<this->tsz[b.fi];}));
		cn[cur]=ccn;
		rep(i,sz(ch[cur])){
			if(i)
				top[++ccn]=ch[cur][i].fi;
			dfs_hld(ch[cur][i].fi, ccn);
		}
	}
};

//See Also: https://codeforces.com/group/q4aFsZ9De9/contest/288125/submission/99012892