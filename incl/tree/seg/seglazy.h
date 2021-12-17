#pragma once
#include "core/base.h"
#include "math/monoid.h"

//q(u(a[l],x),u(a[l+1],x),...,u(a[r],x))
//=u'(q(a[l],...,a[r]),x) 이러한 분배법칙변형? 이 빠르게 가능해야 한다.
//q(u(a,x),u(b,x)) = u'(q(a,b),x) 이거만 성립하면 될듯. u'은 u와 다를 수 있다. 즉, 함수 3개필요
//u'이 많은 경우(++, +=, min=, max+ 등) mu.f(tr[c],mq.fn(lz[c],ce-cs))이다. 아닌경우도(1395 스위치) 있음
//propagate = u(u(a,x),y)=u(a,z)
//읽어볼것: https://github.com/atcoder/ac-library

template<class T> struct SegLazy {
	SegLazy(
		int n=0,
		Monoid<T> mq=MAdd<T>(),
		Monoid<T> mu=MAss<T>(),
		function<T(T,T,int n)> fcomb=lamp(mu.f(a,mq.fn(b,c)),T a,T b,int c))
		:n(n),mq(mq),mu(mu),fcomb(fcomb),tr(n<<2,mu.id),lz(n<<2,mu.id){}
	T q(int p){return q(p,p+1);}
	T q(int s,int e){return q(1,0,n,s,e);}
	void upd(int p,T val){upd(p,p+1,val);}
	void upd(int s,int e,T val){upd(1,0,n,s,e,val);}
private:
	T q(int c,int cs,int ce,int s,int e){
		propa(c,cs,ce);
		if(s>=ce||e<=cs) return mq.id;
		if(s<=cs&&ce<=e) return tr[c];
		int m=cs+ce>>1;
		return mq.f(q(c<<1,cs,m,s,e),q(c<<1|1,m,ce,s,e));
	}
	void upd(int c,int cs,int ce,int s,int e,T val){
		propa(c,cs,ce);
		if(s>=ce||e<=cs) return;
		if(s<=cs&&ce<=e){
			addlz(c,val);
			propa(c,cs,ce);
			return;
		}
		int m=cs+ce>>1;
		upd(c<<1,cs,m,s,e,val);
		upd(c<<1|1,m,ce,s,e,val);
		tr[c]=mq.f(tr[c<<1],tr[c<<1|1]);
	}
	void propa(int c,int cs,int ce){
		if(lz[c]==mu.id) return;
		tr[c]=fcomb(tr[c],lz[c],ce-cs);
		if(ce-cs>1){
			addlz(c<<1,lz[c]);
			addlz(c<<1|1,lz[c]);
		}
		lz[c]=mu.id;
	}
	void addlz(int v,T val){lz[v]=lz[v]==mu.id?val:mu.f(lz[v],val);}

	int n;
	Monoid<T> mq,mu;
	function<T(T,T,int n)> fcomb;
	Arr<T> tr, lz;
};
