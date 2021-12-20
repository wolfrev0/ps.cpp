#pragma once
#include "core/base.h"
#include "math/monoid.h"

template<class MQ, class MU, int xlo=0,int xhi=inf<signed>()>
struct DynSeg{
		using T=MQ::T;
		T v=MQ::id();//그냥 세그는 MU::id로 되있는데 어떻게할까? 일관성맞춰야하는데 흠.
		//그냥 세그에 MU::id쓰는 이유: 금광세그같은거 Upd전에 Q::id로 되있으면 업뎃잘 안되는 경우 있던거로 기억함.
		//나중에 좀 더 생각해서 결정하자.
		DynSeg *l{},*r{};

		T upd(int i, T x, int cs=xlo, int ce=xhi){
			if(ce<=i or i+1<=cs)return v;
			if(i<=cs and ce<=i+1)return v=MU::f(v,x);
			int cm=(cs+ce)/2;
			if(!l)l=new DynSeg;
			if(!r)r=new DynSeg;
			return v=MQ::f(l->upd(i,x,cs,cm),r->upd(i,x,cm,ce));
		}
		T q(int s,int e, int cs=xlo, int ce=xhi){
			if(ce<=s or e<=cs)return MQ::id();
			if(s<=cs and ce<=e) return v;
			int cm=(cs+ce)/2;
			if(!l)l=new DynSeg;
			if(!r)r=new DynSeg;
			return MQ::f(l->q(s,e,cs,cm),r->q(s,e,cm,ce));
		}
	};