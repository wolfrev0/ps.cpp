#pragma once
#include "Core.h"

//Not Tested
template<typename T, typename F>
struct SegLazyDynPers{
	struct Node{
		Node *l=0, *r=0;
		T val=F::id();
		T lz=inf<T>();//lz_id=inf
	};
	SegLazyDynPers(int n=0):n(n){}
	
	T q(int p, Node* base){return q(base,p,p+1);}
	T q(int s, int e, Node* base){return q(base,0,n,s,e);}
	Node* upd(int p, T val, Node* base){return upd(p, p+1, val, base);}
	Node* upd(int s, int e, T val, Node* base/*=new Node()*/){
		Node* ret=new Node(*base);
		upd(ret,0,n,s,e,val,base);
		return ret;
	}
protected:
	int n;

	T q(Node* cur, int cs, int ce, int s, int e){
		bool nl=false, nr=false;
		if(!cur->l) cur->l=new Node(), nl=true;
		if(!cur->r) cur->r=new Node(), nr=true;
		if(cur->lz!=inf<T>()){
			cur->val=F::upd()(cur->val,cur->lz,ce-cs);
			if(ce-cs>1){
				addlz(cur->l, cur->lz);
				addlz(cur->r, cur->lz);
			}
			cur->lz=inf<T>();
		}
	
		if (s>=ce||e<=cs){
			if(nl) delete cur->l, cur->l=nullptr;
			if(nr) delete cur->r, cur->r=nullptr;
			return F::id();
		}
		if (s<=cs&&ce<=e){
			if(nl) delete cur->l, cur->l=nullptr;
			if(nr) delete cur->r, cur->r=nullptr;
			return cur->val;
		}
		int m=(cs+ce)/2;
		T ret=F::q()(q(cur->l,cs,m,s,e),q(cur->r,m,ce,s,e));
		if(nl) delete cur->l, cur->l=nullptr;
		if(nr) delete cur->r, cur->r=nullptr;
		return ret;
	}

	void upd(Node* cur, int cs, int ce, int s, int e, T val, Node* base){
		propa(cur, cs, ce);
		propa(base, cs, ce);
		cur->l=new Node(*base->l);
		cur->r=new Node(*base->r);
		if (s>=ce||e<=cs)
			return;
		if (s<=cs&&ce<=e){
			addlz(cur, val);
			propa(cur, cs, ce);
			return;
		}
		int m=(cs+ce)/2;
		upd(cur->l,cs,m,s,e,val,base->l);
		upd(cur->r,m,ce,s,e,val,base->r);
		cur->val=F::q()(cur->l->val,cur->r->val);
	}
	
	void propa(Node* cur, int cs, int ce){
		if(!cur->l)	cur->l=new Node();
		if(!cur->r) cur->r=new Node();
		if(cur->lz!=inf<T>()){
			cur->val=F::upd()(cur->val,cur->lz,ce-cs);
			if(ce-cs>1){
				addlz(cur->l, cur->lz);
				addlz(cur->r, cur->lz);
			}
			cur->lz=inf<T>();
		}
	}
	
	void addlz(Node* v, T val){v->lz=v->lz==inf<T>()?val:F::propa()(v->lz,val);}
};