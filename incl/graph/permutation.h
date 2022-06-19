#pragma once
#include "core/base.h"

//https://codeforces.com/contest/1690/submission/159807563 (순열 순서 중요)
//순서상관없으면 union find로 그룹짓는게 더 편함
Arr<Arr<int>> permutation_decompose(const Arr<int>& a, const Arr<int>& b){
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
//TODO: 순열 하나만 받아서 그 인덱스와 값으로 처리하는함수 만들기