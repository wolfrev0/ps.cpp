#pragma once 
#include "core/base.h"

template<class T>T dupl(const T& x, int n) {T r;while(n--)r.insert(r.end(), x.begin(),x.end());return r;}
Arr<int> range(int n){Arr<int> r;while(n--)r.emplb(sz(r));return r;}
template<class T>Arr<pair<int,T>> enumerate(Arr<T>& a){Arr<pair<int,T>> r;for(auto&i:a)r.emplb(sz(r),i);return r;}

template<class T> Str<T> itos(int i) {
	if(!i) return "0";
	Str<T> ret;
	while(i) ret.push_back(i % 10 + '0'), i /= 10;
	reverse(ret.begin(), ret.end());
	return ret;
}
auto split(auto s, auto p) {
	Arr<decltype(s)> ret;
	auto it1 = s.begin();
	for(auto it2 = it1; (it2 = find(it1, s.end(), p)) != s.end(); it1 = it2 + 1)
		ret.pushb({it1, it2});
	ret.pushb({it1, s.end()});
	return ret;
}
template<class T>
Arr<Arr<T>> transpose(const Arr<Arr<T>>& a){
	auto r=ARR(sz(a[0]),sz(a),T());
	for(int i=0;i<sz(a);i++)
		for(int j=0;j<sz(a[0]);j++)
			r[j][i]=a[i][j];
	return r;
}