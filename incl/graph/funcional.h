#pragma once
#include "core/base.h"

//https://atcoder.jp/contests/abc256/editorial/4145
//return: Arr<pair<cycle,other>>
Arr<pair<Arr<int>,Arr<int>>> functional_decompose(const Arr<int>& a){
	int n=sz(a);
	Arr<pair<Arr<int>,Arr<int>>> ret;
	Arr<int> dpt(n,-1);
	Arr<int> idx(n,-1);
	Arr<char> cyc(n);
	for(int i=0;i<n;i++){
		if(~dpt[i])continue;
		Arr<int> stk;
		func(int,dfs,int x,int d){
			if(~dpt[x]){
				if(!~idx[x]){
					idx[x]=sz(ret),ret.push_back({});
					for(int i=sz(stk)-(d-dpt[x]); i<sz(stk); i++)
						cyc[stk[i]]=true;
				}
				return idx[x];
			}
			stk.push_back(x);
			dpt[x]=d;
			idx[x]=dfs(a[x],d+1);
			(cyc[x]?ret[idx[x]].fi:ret[idx[x]].se).push_back(x);
			stk.pop_back();
			return idx[x];
		};
		dfs(i,0);
	}
	return ret;
}