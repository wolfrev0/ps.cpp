#pragma once
#include "Core.h"
template<typename T>
struct Bag{
	struct N{
		T d=T();
		N* n=nullptr;
	};
	N *h=new N, *t=h;
	void add(T x){t=t->n=new N{x};}
	void merge(Bag a){t->n=a.h->n; t=a.t; a.h->n=nullptr; a.t=a.h;}
    void iter(func<void(T)> f){
        N* c=h->n;
        while(c)
            f(c->d), c=c->n;
    }
    Arr<T> toArr(){Arr<T> ret; iter([&ret](T x){ret.pushb(x);}); return ret;}
    bool operator<(Bag a)const{return false;}//for pair compare
};