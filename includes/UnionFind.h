#pragma once
#include "Core.h"

struct UF {
	Arr<int> p;
	Arr<int> s;

	UF(int n=0, bool f=false): p(n),s(n,1){
		hfor(i,0,n)
			p[i]=i;
	}

	void uni(int a, int b){
		a=find(a), b=find(b);
		if(a==b)
			return;
		//union by size
		if(s[a]<s[b])
			swap(a,b);
		p[b]=a;
		s[a]+=s[b];
	}

	int find(int a){return p[a]==a?a:p[a]=find(p[a]);}

	int size(int a){return s[find(a)];}
};
