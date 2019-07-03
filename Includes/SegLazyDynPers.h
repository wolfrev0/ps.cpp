#pragma once
#include "Core.h"

//Not Tested
template<typename T, typename U, int n, T id=T()>
struct SegLazyDynPers{
	struct Node{
		Node *l=0, *r=0;
		T val=id;
		//inf=id, shortened_dirty_flag_pattern
		U lazy=inf<U>();
	};
	T q(int p, Node* base){return q(base,p,p+1);}
	T q(int s, int e, Node* base){return q(base,0,n,s,e);}
	Node* upd(int p, U val, Node* base){return upd(p, p+1, val, base);}
	Node* upd(int s, int e, U val, Node* base/*=new Node()*/){
		Node* ret=new Node(*base);
		upd(ret,0,n,s,e,val,base);
		return ret;
	}
protected:
	virtual T fq(const T& a, const T& b)=0;
	virtual T fupd(const T& a, const U& b, signed c)=0;
	virtual U fpropa(const U& a, const U& b)=0;

	T q(Node* cur, int cs, int ce, int s, int e){
		bool nl=false, nr=false;
		if(!cur->l) cur->l=new Node(), nl=true;
		if(!cur->r) cur->r=new Node(), nr=true;
		if(cur->lazy!=inf<U>()){
			cur->val=fupd(cur->val,cur->lazy,ce-cs);
			if(ce-cs>1){
				addlazy(cur->l, cur->lazy);
				addlazy(cur->r, cur->lazy);
			}
			cur->lazy=inf<U>();
		}
	
		if (s>=ce||e<=cs){
			if(nl) delete cur->l, cur->l=nullptr;
			if(nr) delete cur->r, cur->r=nullptr;
			return id;
		}
		if (s<=cs&&ce<=e){
			if(nl) delete cur->l, cur->l=nullptr;
			if(nr) delete cur->r, cur->r=nullptr;
			return cur->val;
		}
		int m=(cs+ce)/2;
		T ret=fq(q(cur->l,cs,m,s,e),q(cur->r,m,ce,s,e));
		if(nl) delete cur->l, cur->l=nullptr;
		if(nr) delete cur->r, cur->r=nullptr;
		return ret;
	}

	void upd(Node* cur, int cs, int ce, int s, int e, U val, Node* base){
		propa(cur, cs, ce);
		propa(base, cs, ce);
		cur->l=new Node(*base->l);
		cur->r=new Node(*base->r);
		if (s>=ce||e<=cs)
			return;
		if (s<=cs&&ce<=e){
			addlazy(cur, val);
			propa(cur, cs, ce);
			return;
		}
		int m=(cs+ce)/2;
		upd(cur->l,cs,m,s,e,val,base->l);
		upd(cur->r,m,ce,s,e,val,base->r);
		cur->val=fq(cur->l->val,cur->r->val);
	}
	
	void propa(Node* cur, int cs, int ce){
		if(!cur->l)	cur->l=new Node();
		if(!cur->r) cur->r=new Node();
		if(cur->lazy!=inf<U>()){
			cur->val=fupd(cur->val,cur->lazy,ce-cs);
			if(ce-cs>1){
				addlazy(cur->l, cur->lazy);
				addlazy(cur->r, cur->lazy);
			}
			cur->lazy=inf<U>();
		}
	}
	
	void addlazy(Node* v, U val){v->lazy=v->lazy==inf<U>()?val:fpropa(v->lazy,val);}
};

template<typename T, typename U, int n>
struct SegLazyDynPersSumAdd:public SegLazyDynPers<T,U,n>{
	T fq(const T& a, const T& b)override{return a+b;}
	T fupd(const T& a, const U& b, signed c)override{return a+b*c;}
	U fpropa(const U& a, const U& b)override{return a+b;}
};
template<typename T, typename U, int n>
struct SegLazyDynPersMaxAdd:public SegLazyDynPers<T,U,n,-inf<T>()>{
	T fq(const T& a, const T& b)override{return max(a,b);}
	T fupd(const T& a, const U& b, signed c)override{return a+b;}
	U fpropa(const U& a, const U& b)override{return a+b;}
};
template<typename T, typename U, int n>
struct SegLazyDynPersMinAss:public SegLazyDynPers<T,U,n,inf<T>()>{
	T fq(const T& a, const T& b)override{return min(a,b);}
	T fupd(const T& a, const U& b, signed c)override{return b;}
	U fpropa(const U& a, const U& b)override{return b;}
};