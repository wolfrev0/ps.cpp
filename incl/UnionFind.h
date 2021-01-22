#pragma once
#include "Core.h"

struct UF {
	Arr<int> p,s;
	UF(int n=0): p(n),s(n,1){for(int i=0;i<n;i++)p[i]=i;}
	void uni(int a, int b){
		a=find(a), b=find(b);
		if(a==b)return;
		//union by size
		if(s[a]<s[b])swap(a,b);
		p[b]=a;
		s[a]+=s[b],s[b]=0;
	}
	int find(int a){return p[a]==a?a:p[a]=find(p[a]);}
	int size(int a){return s[find(a)];}
};
