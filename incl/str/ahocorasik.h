#pragma once
#include "core/base.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wchar-subscripts"
#pragma GCC diagnostic ignored "-Wparentheses"
//메모리 적당히 절약: 배열대신 map or vector<pair<char,A*>>(2809참고), 포인터대신 index(64bit환경)
//메모리 갈아엎는 절약: 1.RadixTree
template<int n=26> struct AhoCorasick{
	using A=AhoCorasick;
	AhoCorasick(char c=0,A* p=0):c(c),p(p?p:this){}
	~AhoCorasick(){for(auto i:a)if(i)delete i;}
	void add(auto s,auto e){
		if(s==e){w=1;o=this;return;}
		if(!a[*s])a[*s]=new A(*s,this);
		a[*s]->add(s+1,e);
	}
	A* go(char x){
		if(a[x])return a[x];
		if(p==this)return this;
		return getfail()->go(x);
	}
	A* getfail(){
		if(p==this or p==p->p)return p;
		if(!f)f=p->getfail()->go(c);
		if(f->w)o=f;
		else o=f->o;
		return f;
	}
	A* getout(){
		if(p==this)return this;
		if(w)return this;
		if(o)return o;
		return o=getfail()->getout();
	}
	char c,w=0;
	A *p,*f=0,*o=0,*a[n]{};
};
#pragma GCC diagnostic pop