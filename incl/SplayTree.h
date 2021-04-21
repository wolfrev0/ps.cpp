#pragma once
#include "Core.h"
#include "Monoid.h"

//NOTE: root->s = n+1임. 맨뒤에 모조노드1개 사용하기때문.
template<class T, class Q, class U>
struct SplayTree{
	struct N{
		N *l=0,*r=0,*p=0;
		int s=1;
		T v=Q::id(),a=Q::id();//,lz=U::id();
		N(T v):v(v){}
		~N(){
			if(l) delete l;
			if(r) delete r;
		}
		void setL(N* x){l=x; if(x)x->p=this;}
		void setR(N* x){r=x; if(x)x->p=this;}
		void step_splay(){
			N *p=this->p,*pp=p->p;
			if(!p) return;
			if(pp) (this==p->l ^ p==pp->l ? this : p)->rot();
			this->rot();
		}
		void rot(){
			if(!this->p) return;
			N *p=this->p,*pp=p->p;
			propa();
			if(pp){
				if(p==pp->l) pp->setL(this);
				else pp->setR(this);
			}else this->p=0;
			if(this==p->l) p->setL(r),this->setR(p);
			else p->setR(l),this->setL(p);
			if(pp)pp->renew();
			p->renew();
			this->renew();
		}
		void propa(){
			// if(lz==U::id()) return;
			// v=U::f(v,lz);
			// a=U::fn(a,s);
			// if(l)l->lz=U::f(l->lz,lz);
			// if(r)r->lz=U::f(r->lz,lz);
			// lz=U::id();
		}
		void renew(){
			a=Q::f(Q::f(l?l->a:Q::id(),v),r?r->a:Q::id());
			s=(l?l->s:0)+(r?r->s:0)+1;
		}
	} *root;

	SplayTree(): root(new N(Q::id())){}
	~SplayTree(){delete root;}

	void ins(int i, T v){
		splay(nth(root,i));
		N* node=new N(v);
		node->setL(root->l);
		root->setL(node);
		
		node->renew();
		root->renew();
	}
	void del(int i){
		N* x=interval(i,i+1);
		x->p->l=0;
		x->p->renew();
		if(x->p->p)x->p->p->renew();
		delete x;
	}
	T q(int s, int e){ return interval(s,e)->a; }

	N* nth(N* x, int n){
		if(!x)return x;
		x->propa();
		int ls=(x->l?x->l->s:0);
		if(n<ls) return nth(x->l,n);
		else if(n>ls) return nth(x->r,n-ls-1);
		else return x;
	}
	void splay(N *x){
		while(x->p)
			x->step_splay();
		root=x;
	}

	N* interval(int s, int e){
		if(!s){
			splay(nth(root,e));
			return root->l;
		}
		splay(nth(root,s-1));
		N* root_save=root;
		root->r->p=0;
		root=root->r;
		splay(nth(root,e-s));
		root->p=root_save;
		root_save->r=root;
		root=root_save;
		return root->r->l;
	}
};

