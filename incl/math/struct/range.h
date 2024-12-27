#pragma once
#include "core.h"

struct Range{
	int s,e;
	auto operator<=>(const Range& o)const{ return mkp(s,-e)<=>mkp(o.s,-o.e);}

	Range operator+(const Range& r)const{return {min(s,r.s),max(e,r.e)};}//union
	Range operator*(const Range& r)const{return {max(s,r.s),min(e,r.e)};}//join
	Range operator+=(const Range& r){return *this=*this+r;}
	Range operator*=(const Range& r){return *this=*this*r;}
	i64 len()const{return e-s;}
};
ostream& operator<<(ostream&os,Range x){return osprint(os,'[',x.s,',',x.e,')');}

//NOTE: [a,b)+[b,c) => not intersect
//https://codeforces.com/contest/1630/submission/144473300
Arr<Range> ranges_cover(Arr<Range> a){
	if(a.empty())return {};
	sort(a.begin(),a.end());
	Arr<Range> b;
	b.emplace_back(a[0]);
	for(int i=1;i<sz(a);){
		int j=i,k=j;
		for(;j<sz(a) and a[j].s<b[-1].e;j++)
			if(a[k].e<a[j].e)
				k=j;
		if(a[k].e>b[-1].e)
			b.emplace_back(a[k]);
		i=j;}
	return b;}

//NOTE: [a,b)+[b,c) = [a,c)
Arr<Range> ranges_union(Arr<Range> a){
	sort(a.begin(),a.end());
	Arr<Range> b;
	for(int i=0;i<sz(a);){
		b.emplace_back(a[i]);
		int j=i,k=i;
		for(;j<sz(a) and a[j].s<=a[k].e;j++)
			if(a[k].e<a[j].e)
				k=j;
		b[-1].e=a[k].e;
		i=j;
	}
	return b;
}

//parklife (반열린구간 맞는거같다? 아마도?)
pair<Arr<Arr<int>>,Arr<int>> ranges2forest(const Arr<Range>& a){
	int n=sz(a);
	Arr<int> b(n); iota(b.begin(),b.end(),0);
	sort(b.begin(),b.end(),lam(a[i]<a[j],int i,int j));
	//b is prefix order
	Arr<Arr<int>> g(n);
	Arr<int> roots;
	stack<int> s;
	for(auto i:b){
		while(sz(s) and a[s.top()].e<=a[i].s)
			s.pop();
		if(s.empty()){
			roots.emplace_back(i);
			s.push(i);
		}else{
			if(a[s.top()].e<a[i].e)
				throw "not tree?";
			g[s.top()].emplace_back(i);
			g[i].emplace_back(s.top());
			s.push(i);}}
	return {g,roots};}

//NOTE: non-overlapping inverval에서 사용가능
//NOTE: closed Range
//Problem: Kick Start 2021 Round D Problem C: Final Exam
struct RangeSet{
	struct A{
		int l,r;
		bool operator<(const A& x)const{return l<x.l;}
		int dist(int x)const{return l<=x and x<=r?0:min(abs(x-r),abs(x-l));}
		Arr<A> split(int x,int& ans){//NOTE: x"제거"한거 양 옆 구간들 반환
			if(l==r){ans=l;return {};}
			if(x<=l){ans=l;return {A{l+1,r}};}
			if(x>=r){ans=r;return {A{l,r-1}};}
			ans=x; return {A{l,x-1},A{x+1,r}};}
	};
	set<A> a;
	void add(int l,int r){a.insert(A{l,r});}
	void del(A z){a.erase(z);}
	A find(int x){
		auto it=a.lb({x,0});
		if(it==a.end() or x<it->l or x>it->r)
			throw "Not Found";
		return *it;}
	A nearest(int x){
		auto it=a.lb({x,0});
		if(it==a.end())
			return *prev(it);
		else if(it==a.begin())
			return *it;
		else
			return prev(it)->dist(x)<=it->dist(x)?*prev(it):*it;}
};
