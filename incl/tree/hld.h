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
	//NOTE: reta는 전체순서는 맞지만 개별구간이 뒤집혀있음, 개별구간.rev()
	//NOTE: retb는 개별구간은 맞지만 전체순서가 뒤집혀있음, reverse(retb)
	pair<Arr<pint>,Arr<pint>> q(int a, int b, bool vtxw, int* plca=0){
		Arr<pint> reta,retb;
		while(c[a]!=c[b])
			if(dpt[top[c[a]]]<dpt[top[c[b]]])
				retb.emplace_back(idx[top[c[b]]],idx[b]+1),b=p[top[c[b]]].fi;
			else
				reta.emplace_back(idx[top[c[a]]],idx[a]+1),a=p[top[c[a]]].fi;
		if(dpt[a]>dpt[b])
			reta.emplace_back(idx[b]+!vtxw,idx[a]+1);
		else
			retb.emplace_back(idx[a]+!vtxw,idx[b]+1);
		if(plca)*plca=dpt[a]<dpt[b]?a:b;
		return {move(reta),move(retb)};
	}
	int lca(int a, int b) { int ret; q(a,b,0,&ret); return ret; }

	Arr<int> c,top,idx;  // chain number, top of the chain, vtx to preidx
	using RT = RootedTree<T>;using RT::ch;using RT::dpt;using RT::n;using RT::p;using RT::r;using RT::tsz;
};

//<See Also>
//https://atcoder.jp/contests/abc235/submissions/28577099
//commutative vertex HLD: BOJ23566
