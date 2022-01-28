#pragma once
#include "core/base.h"

bool ispow2(int n){return (n&-n)==n and n;}
u64 to_mask(int i){return 1ULL<<i;}
int to_num(u64 mask){assert(ispow2(mask));return flg2(mask);}
void subsetk(int n,int k,const function<void(int)>&f){
	for(int i=(1<<k)-1;i and i<(1<<n);){
		int a=i&-i,b=i+a;
		// cout<<bitset<32>(i)<<endl;
		f(i);
		i=((i^b)>>2)/a|b;
	}
}
//not tested
Arr<int> sos(const Arr<int>&a){
	int n=sz(a);
	Arr<int> r(1<<n);
	for(int i=1;i<(1<<n);i++)
		r[i]=r[i&(i-1)]+a[flg2(i&-i)];
	return r;
}