#pragma once
#include "core/base.h"
#include "math/monoid.h"

template<class MQ, class MU, int xlo=0,int xhi=inf<signed>()>
struct DynSeg{
	using T=MQ::T;
	void upd(int i,T x){root.upd(xlo,xhi,i,x);}
	T q(int s,int e){return root.q(xlo,xhi,s,e);}

	struct Node{
		T v=MQ::id();//그냥 세그는 MU::id로 되있는데 어떻게할까? 일관성맞춰야하는데 흠.
		//그냥 세그에 MU::id쓰는 이유: 금광세그같은거 Upd전에 Q::id로 되있으면 업뎃잘 안되는 경우 있던거로 기억함.
		//나중에 좀 더 생각해서 결정하자.
		Node *l{},*r{};

		T upd(int cs, int ce, int i, T x){
			if(ce<=i or i+1<=cs)return v;
			if(i<=cs and ce<=i+1)return v=MU::f(v,x);
			int cm=(cs+ce)/2;
			if(!l)l=new Node;
			if(!r)r=new Node;
			return v=MQ::f(l->upd(cs,cm,i,x),r->upd(cm,ce,i,x));
		}
		T q(int cs, int ce, int s,int e){
			if(ce<=s or e<=cs)return MQ::id();
			if(s<=cs and ce<=e) return v;
			int cm=(cs+ce)/2;
			if(!l)l=new Node;
			if(!r)r=new Node;
			return MQ::f(l->q(cs,cm,s,e),r->q(cm,ce,s,e));
		}
	}root;
};