#pragma once
#include "core/base.h"

struct Interval {
	i64 s,e;
	Interval(i64 s,i64 e):s(s),e(e){}
	Interval operator+(const Interval& r)const{return {min(s,r.s),max(e,r.e)};}//union
	Interval operator*(const Interval& r)const{return {max(s,r.s),min(e,r.e)};}//join
	Interval operator+=(const Interval& r){return *this=*this+r;}
	Interval operator*=(const Interval& r){return *this=*this*r;}
	i64 size()const{return e-s;}
	bool operator<(const Interval& o)const{return mkp(s,-e)<mkp(o.s,-o.e);}//sort = prefix_order
};

//NOTE: non-overlapping inverval에서 사용가능
//NOTE: closed Interval
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

pair<Arr<Arr<int>>,Arr<int>> intervals2forest(const Arr<pint>& a){
	int n=sz(a);
	Arr<int> b(n); iota(b.begin(),b.end(),0);
	sort(b.begin(),b.end(),[&](int i,int j){return pint{a[i].fi,-a[i].se}<pint{a[j].fi,-a[j].se};});
	//b is prefix order

	Arr<Arr<int>> g(n);
	Arr<int> roots;
	stack<int> s;
	for(auto i:b){
		while(sz(s) and a[s.top()].se<=a[i].fi)
			s.pop();
		if(s.empty()){
			roots.pushb(i);
			s.push(i);
		}else{
			if(a[s.top()].se<a[i].se)
				throw "not tree?";
			g[s.top()].pushb(i);
			g[i].pushb(s.top());
			s.push(i);
		}
	}
	return {g,roots};
}