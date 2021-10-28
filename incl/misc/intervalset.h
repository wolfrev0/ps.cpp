#pragma once
#include "core/base.h"

//NOTE: non-overlapping inverval에서 사용가능
//NOTE: closed range
//Problem: Kick Start 2021 Round D Problem C: Final Exam
struct IntervalSet{
	struct A{
		int l,r;
		bool operator<(const A& x)const{return l<x.l;}
		int dist(int x)const{return l<=x and x<=r?0:min(abs(x-r),abs(x-l));}
		Arr<A> split(int x,int& ans){//NOTE: x"제거"한거 양 옆 구간들 반환
			if(l==r){ans=l;return {};}
			if(x<=l){ans=l;return {A{l+1,r}};}
			if(x>=r){ans=r;return {A{l,r-1}};}
			ans=x; return {A{l,x-1},A{x+1,r}};
		}
	};
	set<A> a;

	void add(int l,int r){a.insert(A{l,r});}
	void del(A z){a.erase(z);}
	A find(int x){
		auto it=a.lb({x,0});
		if(it==a.end() or x<it->l or x>it->r)
			throw "Not Found";
		return *it;
	}
	A nearest(int x){
		auto it=a.lb({x,0});
		if(it==a.end())
			return *prev(it);
		else if(it==a.begin())
			return *it;
		else
			return prev(it)->dist(x)<=it->dist(x)?*prev(it):*it;
	}
};