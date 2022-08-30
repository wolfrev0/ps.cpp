#pragma once
#include "core/base.h"

// ff[i] = longest proper (prefix==suffix) length of s[0,i]
template<class T> Arr<int> failure_function(const Str<T> &p) {
	Arr<int> ff(sz(p));
	for(int i = 0, j = 1; j < sz(p); j++) {
		while(i > 0 and p[j] != p[i]) i = ff[i - 1];
		if(p[j] == p[i]) ff[j] = ++i;
	}
	return ff;
}

// return: partial matched length of that index
template<class T> Arr<int> kmp(const Str<T> &s, const Str<T> &p) {
	auto ff = failure_function(p);
	Arr<int> ret(sz(s));
	for(int i = 0, j = 0; j < sz(s); j++) {
		while(i > 0 and s[j] != p[i]) i = ff[i - 1];
		if(s[j] == p[i]) ret[j] = ++i;
		if(i == sz(p)) i = ff[i - 1];
	}
	return ret;
}

//z[i]=match length of a[0,n-1] and a[i,n-1]
//[s,e): rightest range such that a[0..e-s)==a[s,e)
//if i>=e then naive
//else
//  a[0..e-s)==a[s,e) => a[i-s,e-s)==a[i,e) => z[i]>=z[i-s]
//  if(z[i-s] <= e-i) z[i]=z[i-s]
//  else z[i]=z[i-s] && naive start from e
template<class T> Arr<int> z(const Str<T> &a) {
	Arr<int> z(sz(a));
	z[0]=sz(a);
	int s=0,e=1;
	for(int i=1;i<sz(a);i++) {
		if(i<e and z[i-s] < e-i) z[i]=z[i-s];
		else{
			if((s=i)>=e)e=i;
			while(e<sz(a) and a[e-s]==a[e])e++;
			z[i]=e-s;
		}
	}
	return z;
}

//z[i]=match length start from i
template<class T> Arr<int> z(const Str<T> &s, const Str<T>& p) {
	auto za=z(p+"|"+s);
	return {za.begin()+sz(p)+1,za.end()};
}
