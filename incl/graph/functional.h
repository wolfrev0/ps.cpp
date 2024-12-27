#pragma once
#include "core.h"

struct FunctionalGraph{
	FunctionalGraph(i32 n):n(n),a(n,-1){}
	FunctionalGraph(const Arr<int>& a):n(a.size()),a(a.begin(),a.end()){}

	i32& operator[](i32 idx){return a[idx<0?idx+n:idx];}
	const i32& operator[](i32 idx)const{return a[idx<0?idx+n:idx];}

	//https://atcoder.jp/contests/abc256/editorial/4145
	//return: Arr<pair<cycle,other>>
	Arr<pair<Arr<i32>,Arr<i32>>> functional_decompose()const{
		i32 n=sz(a);
		Arr<pair<Arr<i32>,Arr<i32>>> ret;
		Arr<i32> dpt(n,-1);
		Arr<i32> idx(n,-1);
		Arr<char> cyc(n);
		for(i32 i=0;i<n;i++){
			if(~dpt[i])continue;
			Arr<i32> stk;
			func(i32,dfs,i32 x,i32 d){
				if(~dpt[x]){
					if(!~idx[x]){
						idx[x]=sz(ret),ret.push_back({});
						for(i32 i=sz(stk)-(d-dpt[x]); i<sz(stk); i++)
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

	i32 n;
	Arr<i32> a;
};