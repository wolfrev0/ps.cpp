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
void transpose(Arr<Arr<T>>& a){
	int n=sz(a),m=sz(a[0]);
	for(int i=0;i<min(n,m);i++)
		for(int j=i+1;j<min(n,m);j++)
			swap(a[i][j],a[j][i]);
	if(n<m){
		a.resize(m);
		for(int i=0;i<n;i++){
			for(int j=n;j<m;j++)
				a[j].emplb(a[i][j]);
			a[i].resize(n),a[i].shrink_to_fit();
		}
	}else{
		for(int i=m;i<n;i++){
			for(int j=0;j<m;j++)
				a[j].emplb(a[i][j]);
			a[i].clear(),a[i].shrink_to_fit();
		}
		a.resize(m);
	}
}