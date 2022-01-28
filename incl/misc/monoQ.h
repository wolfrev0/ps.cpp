#pragma once
#include "core/base.h"

template<class T> struct MonoQ {
	MonoQ(bool ismax=false):ismax(ismax){}
	int size()const{return e-s;}
	void push(T val){
		val-=bias;
		while(sz(q) && ((val<q.back().fi)^ismax))q.popb();
		q.emplace_back({val,e++});}
	void pop(){
		if(q.front().se==s++)
			q.pop_front();}
	T get()const{return q.front().fi+bias;}

	bool ismax;
	deque<pair<T,int>> q;
	int s=0,e=0,bias=0;
};