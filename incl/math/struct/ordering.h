#pragma once
#include "core.h"

//지금 ordering이 unique하지 않으면 5896에서 문제가 있는데, 이유가 multiset에서 지울때,,, 왜틀리는지 모르겠다..
//usecase: BOJ5896
template<class T, class CMP, class ...Rest> struct Ordering{
	static const int cmpcnt=1+sizeof...(Rest);
	multiset<T,CMP> a;
	Ordering<T,Rest...> b;
	Ordering(CMP cmp, Rest... rest):a(cmp),b(rest...){}
	int size()const{return sz(a);}
	void add(const T& x){a.insert(x);b.add(x);}
	void del(const T& x){a.erase(a.find(x));b.del(x);}
	T front(int idx, int cur=0){return cur==idx?*head(a):b.front(idx,cur+1);}
	T back(int idx, int cur=0){return cur==idx?*tail(a):b.back(idx,cur+1);}
	optional<T> lb(int idx, const T& x, int cur=0){
		if(cur!=idx)
			return b.lb(idx,x,cur+1);
		auto it=a.lb(x);
		return it==a.end()?optional<T>():*it;
	}
	optional<T> ub(int idx, const T& x, int cur=0){
		if(cur!=idx)
			return b.ub(idx,x,cur+1);
		auto it=a.ub(x);
		return it==a.end()?optional<T>():*it;
	}
	auto cmptor(int idx,int cur=0){
		return cur==idx
			?function<T(const T&,const T&)>(a.key_comp())
			:b.cmptor(idx,cur+1);
	}
};
template<class T, class CMP> struct Ordering<T,CMP>{
	static const int cmpcnt=1;
	multiset<T,CMP> a;
	Ordering(CMP cmp):a(cmp){}
	int size()const{return sz(a);}
	void add(const T& x){a.insert(x);}
	void del(const T& x){a.erase(a.find(x));}
	T front(int idx, int cur=0){return *head(a);}
	T back(int idx, int cur=0){return *tail(a);}
	optional<T> lb(int idx, const T& x, int cur=0){
		auto it=a.lb(x);
		return it==a.end()?optional<T>():*it;
	}
	optional<T> ub(int idx, const T& x, int cur=0){
		auto it=a.ub(x);
		return it==a.end()?optional<T>():*it;
	}
	auto cmptor(int idx,int cur=0){return a.key_comp();}
};


#include "misc/heapset.h"
//optimized ordering
//limit: can get only back() element
template<class T, class CMP, class ...Rest> struct OrderingOpt{
	static const int cmpcnt=1+sizeof...(Rest);
	HeapSet<T,CMP> a;
	OrderingOpt<T,Rest...> b;
	OrderingOpt(CMP cmp, Rest... rest):a(cmp),b(rest...){}
	inline int size()const{return sz(a);}
	inline void add(const T& x){a.add(x);b.add(x);}
	inline void del(const T& x){a.del(x);b.del(x);}
	inline T back(int idx, int cur=0){return cur==idx?a.get():b.back(idx,cur+1);}
	auto cmptor(int idx,int cur=0){
		return cur==idx
			?function<T(const T&,const T&)>(a.key_comp())
			:b.cmptor(idx,cur+1);
	}
};
template<class T, class CMP> struct OrderingOpt<T,CMP>{
	static const int cmpcnt=1;
	HeapSet<T,CMP> a;
	OrderingOpt(CMP cmp):a(cmp){}
	inline int size()const{return sz(a);}
	inline void add(const T& x){a.add(x);}
	inline void del(const T& x){a.del(x);}
	inline T back(int idx, int cur=0){return a.get();}
	auto cmptor(int idx,int cur=0){return a.key_comp();}
};
