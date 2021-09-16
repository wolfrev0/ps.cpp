#pragma once
#include "core/base.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wchar-subscripts"
#pragma GCC diagnostic ignored "-Wparentheses"
//메모리 적당히 절약: 배열대신 map, 포인터대신 index
//메모리 갈아엎는 절약: 1.RadixTree
template<int n=26> struct AhoCorasick{
	using A=AhoCorasick;
	AhoCorasick(char c=0,A* p=0):c(c),w(0),p(p?p:this),f(0),o(0){}
	// ~AhoCorasick(){for(auto i:a)if(i)delete i;}
	A* add(auto s,auto e){
		if(!a[*s])a[*s]=new A(*s,this);
		return s!=e?a[*s]->add(s+1,e):(w=1,o=this);
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
		if(p==this)return 0;
		return w?this:getfail()->getout();
	}
	A* getpar(){return p;}
private:
	char c,w;
	A *p,*a[n]{},*f,*o;
};
#pragma GCC diagnostic pop