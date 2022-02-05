#pragma once
#include "core/base.h"
#include "math/monoid.h"

//q(u(a[l],x),u(a[l+1],x),...,u(a[r],x))
//=u'(q(a[l],...,a[r]),x) 이러한 분배법칙변형? 이 빠르게 가능해야 한다.
//q(u(a,x),u(b,x)) = u'(q(a,b),x) 이거만 성립하면 될듯. u'은 u와 다를 수 있다. 즉, 함수 3개필요
//u'이 많은 경우(++, +=, min=, max+ 등) MU::f(tr[c],MQ::fn(lz[c],ce-cs))이다. 아닌경우도(1395 스위치) 있음
//propagate = u(u(a,x),y)=u(a,z)
//읽어볼것: https://github.com/atcoder/ac-library

template<Monoid Q,Monoid U, class T=decltype(Q::id()),auto fcomb=lamp(U::f(a,Q::fn(b,c)),T a,T b,int c)>
struct SegLazy{
	int n; Arr<T> tr,lz;
	SegLazy(u32 n=0):n(bit_ceil(n)),tr(this->n*2,Q::id()),lz(this->n*2,U::id()){}
	T q(int i){return q(i,i+1);}
	T q(int s,int e){return q(s,e,1,0,n);}
	void upd(int i,T val){upd(i,i+1,val);}
	void upd(int s,int e,T val){upd(s,e,val,1,0,n);}
	void updass(int i,T val){upd<true>(i,i+1,val,1,0,n);}//only point-update-able
	//pred(acc[s,i),i)를 만족하는 최소i
	int liftLR(auto pred,int s=0){T acc=Q::id();return liftLR(1,0,n,s,pred,acc);}
	//pred(acc[i,e),i)를 만족하는 최대i
	int liftRL(auto pred){return liftRL(pred,n);}
	int liftRL(auto pred,int e){T acc=Q::id();return liftRL(1,0,n,e,pred,acc);}
	//ex) kth(boj2243), mex(폴리곤_숲게임_lib.cpp), nextgreateridx(boj2493)
private:
	T q(int s,int e,int c,int cs,int ce){
		propa(c,cs,ce);
		if(s>=ce||e<=cs) return Q::id();
		if(s<=cs&&ce<=e) return tr[c];
		int m=(cs+ce)/2;
		return Q::f(q(s,e,c<<1,cs,m),q(s,e,c<<1|1,m,ce));
	}
	template<bool ass=false>
	T upd(int s,int e,T val,int c,int cs,int ce){
		propa(c,cs,ce);
		if(s>=ce||e<=cs) return tr[c];
		if(s<=cs&&ce<=e){
			if(ass) MUST(e-s==1),tr[c]=val;
			else addlz(c,val),propa(c,cs,ce);
			return tr[c]; 
		}
		int m=(cs+ce)/2;
		return tr[c]=Q::f(upd<ass>(s,e,val,c<<1,cs,m),upd<ass>(s,e,val,c<<1|1,m,ce));
	}
	void propa(int c,int cs,int ce){
		if(lz[c]==U::id()) return;
		tr[c]=fcomb(tr[c],lz[c],ce-cs);
		if(ce-cs>1){
			addlz(c<<1,lz[c]);
			addlz(c<<1|1,lz[c]);
		}
		lz[c]=U::id();
	}
	void addlz(int v,T val){lz[v]=lz[v]==U::id()?val:U::f(lz[v],val);}
	int liftLR(int c,int cs,int ce,int s,auto pred,T& acc){
		int cm=(cs+ce)/2,ret=inf<int>();
		if(ce<=s)
			;
		else if(cs<s)
			assmin(ret,liftLR(c<<1,cs,cm,s,pred,acc))||assmin(ret,liftLR(c<<1|1,cm,ce,s,pred,acc));
		else{
			if(pred(acc,cs)){acc=Q::f(acc,tr[c]);return cs;}
			if(!pred(Q::f(acc,tr[c]),ce)){acc=Q::f(acc,tr[c]);return inf<int>();}
			if(ce-cs==1)return ce;
			assmin(ret,liftLR(c<<1,cs,cm,s,pred,acc))||assmin(ret,liftLR(c<<1|1,cm,ce,s,pred,acc));
		}
		return ret;
	}
	int liftRL(int c,int cs,int ce,int e,auto pred,T& acc){
		int cm=(cs+ce)/2,ret=-1;
		if(e<=cs)
			;
		else if(e<ce)
			assmax(ret,liftRL(c<<1|1,cm,ce,e,pred,acc))||assmax(ret,liftRL(c<<1,cs,cm,e,pred,acc));
		else{
			if(pred(acc,ce)){acc=Q::f(acc,tr[c]);return ce;}
			if(!pred(Q::f(tr[c],acc),cs)){acc=Q::f(tr[c],acc);return -1;}
			if(ce-cs==1)return cs;
			assmax(ret,liftRL(c<<1|1,cm,ce,e,pred,acc))||assmax(ret,liftRL(c<<1,cs,cm,e,pred,acc));
		}
		return ret;
	}
};
