#pragma once
#include "core/base.h"
#include "math/monoid.h"

template<class T,int xlo=0,int xhi=inf<int>()>
struct DynSeg{
	DynSeg(Monoid<T> mq=MAdd<T>(),Monoid<T> mu=MAss<T>()):mq(mq),mu(mu){}
	Monoid<T> mq,mu;

	void upd(int i,T x){root.upd(xlo,xhi,i,x);}
	T q(int s,int e){return root.q(xlo,xhi,s,e);}

	struct Node{
		T v=mu.id;
		Node *l{},*r{};

		T upd(int cs, int ce, int i, T x){
			if(ce<=i or i+1<=cs)return mq.id;
			if(i<=cs and ce<=i+1)return v=mu.f(v,x);
			int cm=(cs+ce)/2;
			if(!l)l=new Node;
			if(!r)r=new Node;
			return v=mq.f(l->upd(cs,cm,s,e,x)+r->upd(cm,ce,s,e,x));
		}
		T q(int cs, int ce, int s,int e){
			if(ce<=s or e<=cs)return mq.id;
			if(s<=cs and ce<=e) return v;
			int cm=(cs+ce)/2;
			if(!l)l=new Node;
			if(!r)r=new Node;
			return mq.f(l->q(cs,cm,s,e),r->q(cm,ce,s,e));
		}
	}root;
};