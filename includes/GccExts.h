#pragma once
#include "Core.h"

#include <bits/extc++.h>

using namespace __gnu_pbds;
using namespace __gnu_cxx;

template<typename T>
using Xet=tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T>
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