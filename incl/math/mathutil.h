#pragma once
#include "core/base.h"

int flg(i64 n,int base=2) {
	int ret=0;
	while(n) n/=base,ret++;
	return ret-1;
}
int clg(i64 n,int base=2) {
	int ret=0,rem=0;
	while(n) rem+=n%base,n/=base,ret++;
	return ret-(rem<=1);
}

template<class T> Arr<T> factorials(int n) {Arr<T> r(n,1);for(int i=1;i<n;i++)r[i]=r[i-1]*i;return r;}
template<class T,int n,int k> Arr<Arr<T>> binoms(){
	Arr<Arr<T>> r(n,Arr<T>(k));
	for(int i=1;i<n;i++){
		r[i][0]=1;
		for(int j=1;j<k;j++)
			r[i][j]=r[i-1][j-1]+r[i-1][j];
	}
	return r;
}
Arr<i64> divs(i64 n) {
	Arr<i64> r,s;
	for(i64 i=1;i*i<=n;i++)
		if(n%i==0){
			r.emplace_back(i);
			if(i!=n/i)
				s.emplace_back(n/i);
		}
	reverse(s.begin(),s.end());
	r.insert(r.end(),s.begin(),s.end());
	return r;
}
Arr<i64> facts(i64 n) {
	i64 c=n;
	Arr<i64> r;
	for(i64 i=2;i*i<=n;i++)
		while(!(c%i)){
			c/=i;
			r.emplace_back(i);
		}
	if(c>1)r.emplace_back(c);
	return r;
}

#include "math/mod.h"
//not tested
//a(r^0)+a/(r^1)+a/(r^2)+...+a/(r^n)
template<const int m> Mod<m> geom_sum(Mod<m> a,Mod<m> r,int n){
	assert(r!=1);
	if(n==inf<int>())return a/(1-r);
	return a*(1-r.pow(n+1))/(1-r);
}