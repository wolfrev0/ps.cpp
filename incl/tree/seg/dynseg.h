#pragma once
#include "core/base.h"
#include "math/monoid.h"

// template<class T,int xmin,int xmax>
// struct DynSeg{
// 	DynSeg(Monoid<T> mq=MAdd<T>(),Monoid<T> mu=MAss<T>()):mq(mq),mu(mu){}
// 	Monoid<T> mq,mu;
// 	struct Node{
// 		T v=mu.id;
// 		Node *l{},*r{};

// 		int upd(int cs, int ce, int s, int e, int x){
// 			if(ce<=s or e<=cs)return mq.id;
// 			///??? 생각해보니 레이지 필요하네 레이지부터 처리하자. 레이지없는 DynSeg짜고 레이지Dyn을 따로 짜는게 나을듯?
// 			if(s<=cs and ce<=e)return v=mu.f(v,=x*(ce-cs);
// 			int cm=(cs+ce)/2;
// 			if(!l)l=new Node;
// 			if(!r)r=new Node;
// 			return v=l->upd(cs,cm,s,e,x)+r->upd(cm,ce,s,e,x);
// 		}
// 		int q(int cs, int ce, int s,int e){
// 			if(ce<=s or e<=cs)return 0;
// 			if(s<=cs and ce<=e) return v;
// 			int cm=(cs+ce)/2;
// 			if(!l)l=new Node;
// 			if(!r)r=new Node;
// 			return l->q(cs,cm,s,e)+r->q(cm,ce,s,e);
// 		}
// 	}root;
// };