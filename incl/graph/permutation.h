#pragma once
#include "core/base.h"

Arr<int> permu_inv(const Arr<int>& a){
	Arr<int> r(sz(a));
	for(int i=0;i<sz(a);i++)
		r[a[i]]=i;
	return r;
}

//https://codeforces.com/contest/1690/submission/159807563 (순열 순서 중요)
//순서상관없으면 union find로 그룹짓는게 더 편함
Arr<Arr<int>> permu_decompose(const Arr<int>& a, const Arr<int>& b){
	int n=sz(a);
	Arr<Arr<int>> ret;
	Arr<char> vis(n);
	map<int,int> ib;
	for(int i=0;i<n;i++)
		ib[b[i]]=i;
	func(void,f,int idx,Arr<int>& group){
		if(vis[idx]) return;
		vis[idx]=true;
		group.push_back(idx);
		f(ib[a[idx]],group);
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
	Fenwick<int> fw(n);
	for(int i=0;i<n;i++){
		cnt+=i-fw.q(0,a[i]);
		fw.upd(a[i],+1);
	}
	return cnt;
}
