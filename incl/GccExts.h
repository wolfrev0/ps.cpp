#pragma once
#include "Core.h"

#if INT64
	#undef int
#endif
#include <bits/extc++.h>
#if INT64
	#define int i64
#endif

using namespace __gnu_pbds;
using namespace __gnu_cxx;

template<class T>
struct Xet: public tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>{
	Xet(){}
	Xet(Xet&& r){this->swap(r);}
	void operator=(Xet&& r){this->swap(r);}
};

template<class K, class V>
struct Xmap: public tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>{
	Xmap(){}
	Xmap(Xmap&& r){this->swap(r);}
	void operator=(Xmap&& r){this->swap(r);}
};

template<class T>
struct Multixet{
	Xet<pair<T, int>> s;

	auto begin()const{return s.begin();}
	auto end()const{return s.end();}
	auto find(const T& v)const{
		auto it = s.lower_bound({v, 0});
		return it->fi == v ? it : s.end();
	}
	void insert(const T& v){ s.insert({v, counter++}); }
	void erase(const typename Xet<pair<T, int>>::iterator& it){ s.erase(it); }
	int order_of_key(const T& v)const{ return s.order_of_key({v, counter}); }
	auto find_by_order(int ord)const{ return s.find_by_order(ord); }
	int count(const T& v)const{ return order_of_key(v)-order_of_key(v-1); }
	int size()const{ return sz(s); }
private:
	int counter = 0;
};
