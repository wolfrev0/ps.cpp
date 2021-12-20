#pragma once
#include "core/base.h"
#include "math/monoid.h"

//q(u(a[l],x),u(a[l+1],x),...,u(a[r],x))
//=u'(q(a[l],...,a[r]),x) 이러한 분배법칙변형? 이 빠르게 가능해야 한다.
//q(u(a,x),u(b,x)) = u'(q(a,b),x) 이거만 성립하면 될듯. u'은 u와 다를 수 있다. 즉, 함수 3개필요
//u'이 많은 경우(++, +=, min=, max+ 등) MU::f(tr[c],MQ::fn(lz[c],ce-cs))이다. 아닌경우도(1395 스위치) 있음
//propagate = u(u(a,x),y)=u(a,z)
//읽어볼것: https://github.com/atcoder/ac-library

template<class MQ,class MU, auto fcomb=lamp(MU::f(a,MQ::fn(b,c)),MQ::T a,MU::T b,int c)>
struct SegLazy{
	using T=MQ::T;
	SegLazy(int n=0):n(n),tr(n<<2,MU::id()),lz(n<<2,MU::id()){}
	T q(int p){return q(p,p+1);}
	T q(int s,int e){return q(s,e,1,0,n);}
	void upd(int p,T val){upd(p,p+1,val);}
	void upd(int s,int e,T val){upd(s,e,val,1,0,n);}
private:
	T q(int s,int e,int c,int cs,int ce){
		propa(c,cs,ce);
		if(s>=ce||e<=cs) return MQ::id();
		if(s<=cs&&ce<=e) return tr[c];
		int m=(cs+ce)/2;
		return MQ::f(q(s,e,c<<1,cs,m),q(s,e,c<<1|1,m,ce));
	}
	T upd(int s,int e,T val,int c,int cs,int ce){
		propa(c,cs,ce);
		if(s>=ce||e<=cs) return tr[c];
		if(s<=cs&&ce<=e){ addlz(c,val),propa(c,cs,ce);return tr[c]; }
		int m=(cs+ce)/2;
		return tr[c]=MQ::f(upd(s,e,val,c<<1,cs,m),upd(s,e,val,c<<1|1,m,ce));
	}
	void propa(int c,int cs,int ce){
		if(lz[c]==MU::id()) return;
		tr[c]=fcomb(tr[c],lz[c],ce-cs);
		if(ce-cs>1){
			addlz(c<<1,lz[c]);
			addlz(c<<1|1,lz[c]);
		}
		lz[c]=MU::id();
	}
	void addlz(int v,T val){lz[v]=lz[v]==MU::id()?val:MU::f(lz[v],val);}

	int n;
	Arr<T> tr, lz;
};
