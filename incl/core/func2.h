//functions after include <arr.h>
#pragma once
#include "core/arr.h"

template<class T>int argmin(const Arr<T>& a){return min_element(a.begin(),a.end())-a.begin();}
template<class T>int argmax(const Arr<T>& a){return max_element(a.begin(),a.end())-a.begin();}
Arr<int> permuinv(const Arr<int>& a){Arr<int> r(sz(a));for(int i=0;i<sz(a);i++)r[a[i]]=i;return r;}
template<class T>map<T,Arr<int>> classify(const Arr<T>& a){
	map<T,Arr<int>> r;
	for(int i=0;i<sz(a);i++)
		r[a[i]].push_back(i);
	return r;
}