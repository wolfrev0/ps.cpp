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
#if CPP20
template<class T=int> requires (!Iterable<T>) T input(){T x;cin>>x;return x;}
template<class T> requires Iterable<T> T input(){
	T a;
	for(auto&i:a)
		i=input<typename remove_reference<decltype(i)>::type>();
	return a;
}
template<class T=int,int n>std::array<T,n> input(){
	std::array<T,n> a;
	for(auto&i:a)
		i=input<T>();
	return a;
}
template<class T=Arr<int>> requires Iterable<T> T input(int n){
	T a(n);
	for(auto&i:a)
		i=input<typename remove_reference<decltype(i)>::type>();
	return a;
}
#endif