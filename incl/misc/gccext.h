#pragma once
#include "core/base.h"

using namespace __gnu_pbds;
using namespace __gnu_cxx;

int __RANDOM=i64(new int)^time(0);
struct randomhasher{int operator()(int x)const{return x^__RANDOM;}};
template<class K,class V> using HashMap=gp_hash_table<K,V,randomhasher>;
//MLE or RLE or WA 날땐 cc_hash_table or unordered_map 사용

template<class T,class CMP=less<>,class Policy=pairing_heap_tag>
struct pbds_pq
:public __gnu_pbds::priority_queue<T,CMP,Policy>{
	pbds_pq(){}
	pbds_pq(pbds_pq&& r){this->swap(r);}
	void operator=(pbds_pq&& r){this->swap(r);}
};

//NOTE: pbds_tree.join은 중복키 있으면 join_error 예외발생
template<class T>
struct pbds_set
:public tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>{
	pbds_set(){}
	pbds_set(pbds_set&& r){this->swap(r);}
	void operator=(pbds_set&& r){this->swap(r);}
};
template<class K,class V>
struct pbds_map
:public tree<K,V,less<K>,rb_tree_tag,tree_order_statistics_node_update>{
	pbds_map(){}
	pbds_map(pbds_map&& r){this->swap(r);}
	void operator=(pbds_map&& r){this->swap(r);}
};
template<class T> struct pbds_multiset{
	pbds_set<pair<T,int>> s;
	auto begin()const{return s.begin();}
	auto end()const{return s.end();}
	auto find(const T& v)const{
		auto it=s.lb({v,0});
		return it->fi==v?it:s.end();}
	auto insert(const T& v){return s.insert({v,counter++});}
	auto erase(const typename pbds_set<pair<T,int>>::iterator& it){return s.erase(it);}
	int order_of_key(const T& v,bool ub=true)const{return s.order_of_key({v,ub?counter:0});}
	auto find_by_order(int ord)const{return s.find_by_order(ord);}
	int count(const T& v)const{return order_of_key(v)-order_of_key(v-1);}
	int size()const{return sz(s);}
private:
	int counter=0;
};
