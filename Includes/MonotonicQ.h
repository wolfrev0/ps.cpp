#pragma once
#include "Core.h"

template<typename T>
struct MonotonicQ{
	struct WNI{T w; int i;};
	MonotonicQ(bool ismax=false):ismax(ismax){}

	int size(){return e-s;}

	void push(const T& val){
		while(q.size() && ((val<q.back().w) ^ ismax))
			q.pop_back();
		q.push_back({val, e++});
	}

	void pop(){
		if(q.front().i==s++)
			q.pop_front();
	}

	T get()const{return q.front().w;}
private:
	bool ismax;
	deque<WNI> q;
	int s=0, e=0;
};