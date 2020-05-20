#pragma once
#include "Core.h"

template<typename T, typename F>
struct SegLazyDyn{
	struct Node{
		Node *l=0, *r=0;
		T val=F::id();
		T lz=inf<T>();//lz_id=inf
	};
	SegLazyDyn(int n):n(n){}
	T q(int p){return q(p,p+1);}
	T q(int s, int e){return q(r,0,n,s,e);}
	void upd(int p, T val){upd(p, p+1, val);}
	void upd(int s, int e, T val){upd(r,0,n,s,e,val);}
protected:
	int n;
	Node* r=new Node();

	T q(Node* cur, int cs, int ce, int s, int e){
		propa(cur, cs, ce);
		if (s>=ce||e<=cs)
			return F::id();
		if (s<=cs&&ce<=e)
			return cur->val;
		int m=(cs+ce)/2;
		return F::q(q(cur->l,cs,m,s,e),q(cur->r,m,ce,s,e));
	}

	void upd(Node* cur, int cs, int ce, int s, int e, T val){
		propa(cur, cs, ce);
		if (s>=ce||e<=cs)
			return;
		if (s<=cs&&ce<=e){
			addlz(cur, val);
			propa(cur, cs, ce);
			return;
		}
		int m=(cs+ce)/2;
		upd(cur->l,cs,m,s,e,val);
		upd(cur->r,m,ce,s,e,val);
		cur->val=F::q(cur->l->val,cur->r->val);
	}
	
	void propa(Node* cur, int cs, int ce){
		if(!cur->l)	cur->l=new Node();
		if(!cur->r) cur->r=new Node();
		if(cur->lz!=inf<T>()){
			cur->val=F::upd(cur->val,cur->lz,ce-cs);
			if(ce-cs>1){
				addlz(cur->l, cur->lz);
				addlz(cur->r, cur->lz);
			}
			cur->lz=inf<T>();
		}
	}
	
	void addlz(Node* v, T val){v->lz=v->lz==inf<T>()?val:F::propa(v->lz,val);}
};