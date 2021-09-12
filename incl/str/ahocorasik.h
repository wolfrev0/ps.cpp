#pragma once
#include "core/base.h"

//메모리 적당히 절약: 배열대신 map, 포인터대신 index
//메모리 갈아엎는 절약: 1.RadixTree
template<int n=26> struct AhoCorasick{
	using A=AhoCorasick;
	A(char c=0,A* p=0):c(c),p(p?p:this){}
	~A(){for(auto i:a)if(i)delete i;}
	A* add(auto s,auto e){
		if(!a[*s])a[*s]=new A<n>(c,this);
		return s^e?a[*s]->add(s+1,e):(w=1,this);
	}
	void calc_failure(){
		f=this;
		queue<A*> q;
		
	}
	char c,w=0;
	A *p,*f,*o,*a[n]{};
};