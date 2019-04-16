#pragma once
#include "Core.h"

template<typename T>
struct MonotonicQ{
	MonotonicQ():MonotonicQ([](const T& a, const T& b){return a<b;}){}
	MonotonicQ(const function<bool(const T&, const T&)>& cmp):cmp(cmp){}

	int size(){return e-s;}

	void push(const T& val){
		while(q.size() && cmp(val,q.back().first))
			q.pop_back();
		q.push_back({val, e++});
	}

	void pop(){
		if(q.front().second==s++)
			q.pop_front();
	}

	T get()const{return q.front().first;}
private:
	deque<pair<T,int>> q;
	int s=0, e=0;
	function<bool(const T&,const T&)> cmp;
};