#pragma once
#include "Core.h"

struct UF {
	Arr<int> p;
	Arr<int> sz;

	UF(int n=0, bool f=false): p(n),sz(n,1){
		hfor(i,0,n)
			p[i]=i;
	}

	void uni(int a, int b){
		a=find(a), b=find(b);
		if(a==b)
			return;
		//union by size
		if(sz[a]<sz[b])
			swap(a,b);
		p[b]=a;
		sz[a]+=sz[b];
	}

	int find(int a){return p[a]==a?a:p[a]=find(p[a]);}

	int size(int a){return sz[find(a)];}
};