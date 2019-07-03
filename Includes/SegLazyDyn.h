#pragma once
#include "Core.h"

template<typename T, typename U, int n, T id=T()>
struct SegLazyDyn{
	struct Node{
		Node *l=0, *r=0;
		T val=id;
		//inf=id, shortened_dirty_flag_pattern
		U lazy=inf<U>();
	};
	T q(int p){return q(p,p+1);}
	T q(int s, int e){return q(root,0,n,s,e);}
	void upd(int p, U val){upd(p, p+1, val);}
	void upd(int s, int e, U val){upd(root,0,n,s,e,val);}
protected:
	virtual T fq(const T& a, const T& b)=0;
	virtual T fupd(const T& a, const U& b, signed c)=0;
	virtual U fpropa(const U& a, const U& b)=0;

	T q(Node* cur, int cs, int ce, int s, int e){
		propa(cur, cs, ce);
		if (s>=ce||e<=cs)
			return id;
		if (s<=cs&&ce<=e)
			return cur->val;
		int m=(cs+ce)/2;
		return fq(q(cur->l,cs,m,s,e),q(cur->r,m,ce,s,e));
	}

	void upd(Node* cur, int cs, int ce, int s, int e, U val){
		propa(cur, cs, ce);
		if (s>=ce||e<=cs)
			return;
		if (s<=cs&&ce<=e){
			addlazy(cur, val);
			propa(cur, cs, ce);
			return;
		}
		int m=(cs+ce)/2;
		upd(cur->l,cs,m,s,e,val);
		upd(cur->r,m,ce,s,e,val);
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
	
	Node* root=new Node();
};

template<typename T, typename U, int n>
struct SegLazyDynSumAdd:public SegLazyDyn<T,U,n>{
	T fq(const T& a, const T& b)override{return a+b;}
	T fupd(const T& a, const U& b, signed c)override{return a+b*c;}
	U fpropa(const U& a, const U& b)override{return a+b;}
};
template<typename T, typename U, int n>
struct SegLazyDynMaxAdd:public SegLazyDyn<T,U,n,-inf<T>()>{
	T fq(const T& a, const T& b)override{return max(a,b);}
	T fupd(const T& a, const U& b, signed c)override{return a+b;}
	U fpropa(const U& a, const U& b)override{return a+b;}
};
template<typename T, typename U, int n>
struct SegLazyDynMinAss:public SegLazyDyn<T,U,n,inf<T>()>{
	T fq(const T& a, const T& b)override{return min(a,b);}
	T fupd(const T& a, const U& b, signed c)override{return b;}
	U fpropa(const U& a, const U& b)override{return b;}
};