#pragma once
#include "core/base.h"

//almost O(logN) due to pow()
template<class T, unsigned pn=2>
struct Hash{
	static_assert(pn<=4);
	static const T p[4];
	T h[pn];
	Hash():Hash(0){}
	Hash(T hv):Hash({hv,hv,hv,hv},1){} //4 because maximum 4 mods
	Hash(initializer_list<T> hil,int cnt):cnt(cnt){
		auto it=hil.begin();
		for(int i=0;i<pn;i++)
			h[i]=*it++;
	}

	//Sequential Hash
	void push_back(Hash x){
		for(int i=0;i<pn;i++)
			h[i]=h[i]*pow(p[i],x.cnt)+x.h[i];
		cnt+=x.cnt;
	}
	void push_front(Hash x){
		for(int i=0;i<pn;i++)
			h[i]=x.h[i]*pow(p[i],cnt)+h[i];
		cnt+=x.cnt;
	}
	void pop_back(Hash x){
		for(int i=0;i<pn;i++)
			h[i]=(h[i]-x.h[i])*inv(pow(p[i],x.cnt));
		cnt-=x.cnt;
	}
	void pop_front(Hash x){
		for(int i=0;i<pn;i++)
			h[i]-=x.h[i]*pow(p[i],cnt);
		cnt-=x.cnt;
	}

	//Set Hash
	void insert(Hash x){
		for(int i=0;i<pn;i++)
			h[i]+=pow(p[i],x.h[i]);
		cnt++;}
	void erase(Hash x){
		for(int i=0;i<pn;i++)
			h[i]-=pow(p[i],x.h[i]);
		cnt--;}

	int size()const{return cnt;}
	Hash operator+(const Hash& r)const{
		auto ret=*this;
		ret.push_back(r);
		return ret;
	}
	Hash operator-(const Hash& r)const{
		auto ret=*this;
		ret.pop_back(r);
		return ret;
	}
	Hash operator+=(const Hash& r){return *this=*this+r;}
	Hash operator-=(const Hash& r){return *this=*this-r;}
	bool operator==(const Hash& r)const{return h[0]==r.h[0] and h[1]==r.h[1];}
	bool operator<(const Hash& r)const{return h[0]==r.h[0]?h[1]<r.h[1]:h[0]<r.h[0];}
private:
	int cnt;
	T pow(T x, u64 p){return x.pow(p);}
	T inv(T x){return x.inv();}
};
//TODO: make it constexpr by Mod<> update
template<class T,unsigned pn>
const T Hash<T,pn>::p[4]={T(3),T(5),T(7),T(11)};
//NOTE: thuemorse sequence can break it
template <>
u64 Hash<u64,2>::pow(u64 x,u64 p){
	if(!p) return 1;
	if(p==1) return x;
	u64 z=pow(x,p/2);
	return z*z*(p%2?x:1);
}
template <>
u64 Hash<u64,2>::inv(u64 x){
	return pow(x,u64(-2));
}
template<class T, unsigned pn>
ostream& operator<<(ostream& s,const Hash<T, pn>& n){
	osprint(s,'(');
	for(int i=0;i<pn;i++)
		osprint(s,(unsigned)n.h[i],',');
	return osprint(s,')');
}

//almost O(1) by pow memoization
//except inv() which is O(logN)
template<class T, unsigned pn=2>
struct HashSeq{
	static_assert(pn<=4);
	static const T p[4];
	static Arr<T> memopow[pn];
	T h[pn];
	HashSeq():HashSeq(0){}
	HashSeq(T hv):HashSeq({hv,hv,hv,hv},1){} //4 because maximum 4 mods
	HashSeq(initializer_list<T> hil,int cnt):cnt(cnt){
		auto it=hil.begin();
		for(int i=0;i<pn;i++)
			h[i]=*it++;
	}
	void push_back(HashSeq x){
		for(int i=0;i<pn;i++)
			h[i]=h[i]*pow(i,x.cnt)+x.h[i];
		cnt+=x.cnt;
	}
	void push_front(HashSeq x){
		for(int i=0;i<pn;i++)
			h[i]=x.h[i]*pow(i,cnt)+h[i];
		cnt+=x.cnt;
	}
	void pop_back(HashSeq x){
		for(int i=0;i<pn;i++)
			h[i]=(h[i]-x.h[i])*inv(pow(i,x.cnt));
		cnt-=x.cnt;
	}
	void pop_front(HashSeq x){
		for(int i=0;i<pn;i++)
			h[i]-=x.h[i]*pow(i,cnt);
		cnt-=x.cnt;
	}
	int size()const{return cnt;}
	HashSeq operator+(const HashSeq& r)const{
		auto ret=*this;
		ret.push_back(r);
		return ret;
	}
	HashSeq operator-(const HashSeq& r)const{
		auto ret=*this;
		ret.pop_back(r);
		return ret;
	}
	HashSeq operator+=(const HashSeq& r){return *this=*this+r;}
	HashSeq operator-=(const HashSeq& r){return *this=*this-r;}
	bool operator==(const HashSeq& r)const{return h[0]==r.h[0] and h[1]==r.h[1];}
	bool operator<(const HashSeq& r)const{return h[0]==r.h[0]?h[1]<r.h[1]:h[0]<r.h[0];}
private:
	int cnt;
	T inv(T x){return x.inv();}
	T pow(T x, int y){
		int pidx = find(p,p+pn,x)-p;
		assert(pidx<pn);
		if(memopow[pidx].empty())
			memopow[pidx].emplace_back(1);
		while(memopow[pidx].size()<y+1)
			memopow[pidx].emplace_back(memopow[pidx].back()*p[pidx]);
		return memopow[pidx][y];
	}
};
//TODO: make it constexpr by Mod<> update
template<class T,unsigned pn>
const T HashSeq<T,pn>::p[4]={T(3),T(5),T(7),T(11)};
template<class T,unsigned pn>
Arr<T> HashSeq<T,pn>::memopow[pn];
//NOTE: thuemorse sequence can break it
template <>
u64 HashSeq<u64,2>::inv(u64 x){
	func(u64,pow,u64 x,int y){
		if(!y) return 1;
		if(y==1) return x;
		u64 z=pow(x,y/2);
		return z*z*(y%2?x:1);
	};
	return pow(x,u64(-2));
}
template<class T, unsigned pn>
ostream& operator<<(ostream& s,const HashSeq<T, pn>& n){
	osprint(s,'(');
	for(int i=0;i<pn;i++)
		osprint(s,(unsigned)n.h[i],',');
	return osprint(s,')');
}
