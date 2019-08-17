#pragma once
#include "Core.h"

template<typename T, typename F>
struct SegPers{
	struct Node{
		Node *l=0, *r=0;
		T val=F::id();
	};

	SegPers(int n):n(n){}
	void build(Node* cur){ vector<T> tmp(n); build(cur, tmp); }
	void build(Node* cur, const vector<T>& a){ build(cur, 0, n, a); }
	T q(Node* tr, int s, int e){ return q(tr, 0, n, s, e); }
	Node *upd(Node* tr, int idx, T val){
		auto ret=new Node();
		upd(ret, tr, 0, n, idx, val);
		return ret;
	}
private:
	int n;

	void build(Node* cur, int s, int e, const vector<T>& a){
		if(e-s==1){
			cur->val=a[s];
			return;
		}

		int m=(s+e)/2;
		cur->l=new Node();
		cur->r=new Node();
		build(cur->l,s,m,a);
		build(cur->r,m,e,a);
		cur->val=F::q(cur->l->val, cur->r->val);
	}

	void upd(Node* cur, Node* bs, int s, int e, int idx, T v){
		if(e<=idx or idx<s)
			return;
		if(e-s==1){
			cur->val=v;
			return;
		}

		int m=(s+e)/2;
		cur->l= idx<m?new Node():bs->l;
		cur->r= idx<m?bs->r:new Node();
		upd(cur->l, bs->l, s, m, idx, v);
		upd(cur->r, bs->r, m, e, idx, v);
		cur->val=F::q(cur->l->val, cur->r->val);
	}

	T q(Node* cur, int cs, int ce, int s, int e){
		if(ce<=s or e<=cs or e<=s)
			return F::id();
		if(s<=cs and ce<=e)
			return cur->val;
		int m=(cs+ce)/2;
		return F::q(q(cur->l, cs, m, s, e), q(cur->r, m, ce, s, e));
	}
};