#pragma once
#include "Core.h"

template<typename T>
struct MonotonicQ{
	struct WNI{T w; int i;};

	MonotonicQ():MonotonicQ([](const T& a, const T& b){return a<b;}){}
	MonotonicQ(const function<bool(const T&, const T&)>& cmp):cmp(cmp){}

	int size(){return e-s;}

	void push(const T& val){
		while(q.size() && cmp(val,q.back().w))
			q.pop_back();
		q.push_back({val, e++});
	}

	void pop(){
		if(q.front().i==s++)
			q.pop_front();
	}

	T get()const{return q.front().w;}
private:
	deque<WNI> q;
	int s=0, e=0;
	function<bool(const T&,const T&)> cmp;
};