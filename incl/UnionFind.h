#pragma once
#include "Bag.h"

struct UF {
	Arr<int> p;
	Arr<Bag<int>> fm;

	UF(int n=0): p(n),fm(n){
		hfor(i,0,n)
			p[i]=i,fm[i].add(i);
	}

	void uni(int a, int b){
		a=find(a), b=find(b);
		if(a==b)
			return;
		//union by size
		if(fm[a].size()<fm[b].size())
			swap(a,b);
		p[b]=a;
		fm[a].merge(fm[b]);
	}

	int find(int a){return p[a]==a?a:p[a]=find(p[a]);}

	int size(int a){return fm[find(a)].size();}

	Bag<int> family(int a){return fm[find(a)];}
};
