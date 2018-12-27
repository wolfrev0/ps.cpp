#pragma once
#include "Core.h"

template<typename T>
using xset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T>
struct xmultiset{
    xset<pair<T, int>> s;

	auto begin()const{return s.begin();}
    auto end()const{return s.end();}
    auto find(const T& v)const{
        auto it = s.lower_bound({v, 0});
        return it->first == v ? it : s.end();
    }
    void insert(const T& v){ s.insert({v, counter++}); }
    void erase(const typename xset<pair<T, int>>::iterator& it){ s.erase(it); }
    int order_of_key(const T& v)const{ return s.order_of_key({v, counter}); }
    int count(const T& v)const{ return order_of_key(v)-order_of_key(v-1); }
    int size()const{ return s.size(); }
private:
    int counter = 0;
};