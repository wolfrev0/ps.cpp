#pragma once
#include "Core.h"

struct UF {
	Arr<int> par;
	Arr<int> sz;

	UF(int n): par(n),sz(n,1){
		hfor(i,0,n)
			par[i]=i;
	}

	void uni(int a, int b){
		a=find(a), b=find(b);
		if(a==b)
			return;
		//union by size
		if(sz[a]<sz[b])
			swap(a,b);
		par[b]=a;
		sz[a]+=sz[b];
	}

	int find(int a){
		if(par[a]==a)
			return a;
		//path compression
		return par[a]=find(par[a]);
	}

	int size(int a){return sz[find(a)];}
};