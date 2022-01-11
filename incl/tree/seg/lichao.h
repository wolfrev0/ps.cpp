#pragma once
#include "core/base.h"

//TODO: concept로 인터페이스 추상화(서로 교점 하나인 그래프면 관리가능하다 함)시키고,cht.L과 lichao.LL도 geom.Line으로 통합시키자.
struct LL{
	static LL id(){return {0,0.-inf<int>()};}
	f64 a,b;
	f64 f(f64 x){return a*x+b;}
};

//max lichao임. min필요하면 add(-a,-b),-q(x)
//TODO: 정수lichao추가.
//지금당장은 f64=longdouble, eps=1e-0, ans=round(f(x))로 쓰면 되긴함.
template<class T,int xlo=-inf<int>(),int xhi=inf<int>()>
struct LiChao{
	T v=T::id();
	LiChao *l{},*r{};

	void add(T x,f64 cs=xlo,f64 ce=xhi){
		if(ce-cs<eps)return;
		f64 cm=(cs+ce)/2;
		if(!l)l=new LiChao;
		if(!r)r=new LiChao;
		LL flo=v,fhi=x;//x=cs기준 직선의 lo,hi
		if(fhi.f(cs)<flo.f(cs)) swap(flo,fhi);
		if(flo.f(ce)<=fhi.f(ce)) v=fhi;
		else if(flo.f(cm)<=fhi.f(cm)) v=fhi,r->add(flo,cm,ce);
		else v=flo,l->add(fhi,cs,cm);
		//NOTE: flo를 저장할땐 fhi를 넘기고, fhi를 저장할땐 flo를 넘기는건 나중에 쿼리할때 저장한거 외에 더 내려갈때 다른쪽꺼 체크되게 하기 위함인듯. 이부분이 제일 이해하기 tricky한 부분인거같다...
	}

	f64 q(f64 x,f64 cs=xlo,f64 ce=xhi){
		f64 cm=(cs+ce)/2;
		f64 ret=v.f(x);
		if(x<cm and l)ret=max(ret,l->q(x,cs,cm));
		if(x>=cm and r)ret=max(ret,r->q(x,cm,ce));
		return ret;
	}
};