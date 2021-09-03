#pragma once
#include "tree/tree.h"

template<class T> struct HLD:public RootedTree<T>{
	HLD(){}
	HLD(const Tree<T>& t,int r,Arr<T> vw={}):RT(t,r,vw),c(n),top(n){
		int cc=0;
		func(void,dfs,int x){
			if(sz(ch[x]))
				swap(ch[x].front(), *max_element(ch[x].begin(),ch[x].end(), lam(tsz[a.fi]<tsz[b.fi],auto a,auto b)));
			c[x]=cc;
			for(int i=0;i<sz(ch[x]);i++){
				if(i) top[++cc]=ch[x][i].fi;
				dfs(ch[x][i].fi);
			}
		};
		dfs(r);
		idx=permuinv(RT::pre()),top[0]=r;
	}
	Arr<pint> q(int a, int b, bool vtxw, int* plca=0){
		Arr<pint> ret;
		while(c[a]!=c[b])
			if(dpt[top[c[a]]]<dpt[top[c[b]]])
				ret.pushb(idx[top[c[b]]],idx[b]+1),b=p[top[c[b]]].fi;
			else
				ret.pushb(idx[top[c[a]]],idx[a]+1),a=p[top[c[a]]].fi;
		if(dpt[a]>dpt[b]) swap(a,b);
		ret.pushb(idx[a]+!vtxw,idx[b]+1);
		if(plca)*plca=a;
		return ret;
	}
	int lca(int a, int b) { int ret; q(a,b,0,&ret); return ret; }

	Arr<int> c,top,idx;  // chain number, top of the chain, vtx to preidx
	using RT = RootedTree<T>;using RT::ch;using RT::dpt;using RT::n;using RT::p;using RT::r;using RT::tsz;
};

//<See Also>
// https://www.acmicpc.net/source/32842689
// https://codeforces.com/group/q4aFsZ9De9/contest/288125/submission/99012892
