#pragma once
#include "core/base.h"

using namespace __gnu_pbds;
using namespace __gnu_cxx;

int __RANDOM=i64(new int)^time(0);
struct randomhasher{int operator()(int x)const{return x^__RANDOM;}};
template<class K,class V> using HashMap=gp_hash_table<K,V,randomhasher>;
//MLE or RLE or WA 날땐 cc_hash_table or unordered_map 사용

template<class T,class Policy=pairing_heap_tag>
using XPQMin=__gnu_pbds::priority_queue<T,greater<T>,Policy>;
template<class T,class Policy=pairing_heap_tag>
using XPQMax=__gnu_pbds::priority_queue<T,less<T>,Policy>;

template<class T> struct Xet
:public tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>{
	Xet(){}
	Xet(Xet&& r){this->swap(r);}
	void operator=(Xet&& r){this->swap(r);}
};

template<class K,class V> struct Xmap
:public tree<K,V,less<K>,rb_tree_tag,tree_order_statistics_node_update>{
	Xmap(){}
	Xmap(Xmap&& r){this->swap(r);}
	void operator=(Xmap&& r){this->swap(r);}
};

template<class T> struct Multixet{
	Xet<pair<T,int>> s;
	auto begin()const{return s.begin();}
	auto end()const{return s.end();}
	auto find(const T& v)const{
		auto it=s.lb({v,0});
		return it->fi==v?it:s.end();
	}
	auto insert(const T& v){return s.insert({v,counter++});}
	auto erase(const typename Xet<pair<T,int>>::iterator& it){return s.erase(it);}
	int order_of_key(const T& v,bool ub=true)const{return s.order_of_key({v,ub?counter:0});}
	auto find_by_order(int ord)const{return s.find_by_order(ord);}
	int count(const T& v)const{return order_of_key(v)-order_of_key(v-1);}
	int size()const{return sz(s);}

private:
	int counter = 0;
};
