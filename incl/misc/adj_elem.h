#pragma once
#include "core.h"

template<class T>
pair<Arr<int>,Arr<int>> adj_eq(const Arr<T>& a){
	int n=sz(a);
	map<T,int> b;
	Arr<int> r(n,n),l(n,-1);
	for(int i=0;i<n;i++){
		if(b.count(a[i])){
			l[i]=b[a[i]];
			r[b[a[i]]]=i;
		}
		b[a[i]]=i;
	}
	return {move(l),move(r)};
}

template<class T, class CMP=less_equal<T>>
pair<Arr<int>,Arr<int>> adj_cmp(const Arr<T>& a){
	int n=sz(a);
	auto cmp=CMP();
	stack<int> stk;
	Arr<int> r(n,n),l(n,-1);
	for(int i=0;i<n;i++){
		while(sz(stk) and cmp(a[stk.top()],a[i]))
			r[stk.top()]=i,stk.pop();
		stk.push(i);
	}
	stk={};
	for(int i=n-1;i>=0;i--){
		while(sz(stk) and cmp(a[i],a[stk.top()]))
			l[stk.top()]=i,stk.pop();
		stk.push(i);
	}
	return {move(l),move(r)};
}