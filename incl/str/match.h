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

//z[i]=match length of s[0,n-1] and s[i,n-1]
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