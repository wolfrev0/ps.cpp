#pragma once
#include "core.h"

Arr<int> permu_inv(const Arr<int>& a){
	Arr<int> r(sz(a));
	for(int i=0;i<sz(a);i++)
		r[a[i]]=i;
	return r;
}

//https://codeforces.com/contest/1690/submission/201727170
template<class T>
Arr<int> to_permutation(const Arr<T>& a, const Arr<T>& b){
	int n=sz(a); assert(sz(a)==sz(b));
	Arr<int> ret(n);
	map<int,Arr<int>> c;
	for(int i=0;i<n;i++)
		c[b[i]].push_back(i);
	for(auto&i:c)
		reverse(i.se.begin(),i.se.end());
	for(int i=0;i<n;i++){
		ret[i]=c[a[i]].back();
		c[a[i]].pop_back();
	}
	return ret;
}
Arr<Arr<int>> permu_decompose(const Arr<int>& p){
	int n=sz(p);
	Arr<Arr<int>> ret;
	Arr<char> vis(n);
	func(void,f,int x,Arr<int>& group){
		if(vis[x]) return;
		vis[x]=true;
		group.push_back(x);
		f(p[x],group);
	};
	for(int i=0;i<n;i++){
		if(vis[i]) continue;
		Arr<int> group;
		f(i,group);
		ret.push_back(group);
	}
	return ret;
}
#include "tree/seg/fenwick.h"
int inversion_count(const Arr<int>& a){
	int n=sz(a),cnt=0;
	Fenwick fw(n);
	for(int i=0;i<n;i++){
		cnt+=i-fw.q(0,a[i]);
		fw.upd(a[i],+1);
	}
	return cnt;
}
