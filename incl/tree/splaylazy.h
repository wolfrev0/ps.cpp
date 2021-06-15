#pragma once
#include "core/base.h"
#include "math/monoid2.h"

template<class T, class F>
struct SplayLazy{
	struct N;
	SplayLazy(): root(new N(F::idT())){}
	~SplayLazy(){delete root;}

	int size()const{return root->s-1;}//remove one mock node
	N* ins(int i, T v){
		splay(nth(root,i));
		N* node=new N(v);
		node->setL(root->l);
		root->setL(node);
		
		node->renew();
		root->renew();
		return node;
	}
	void del(int i){
		N* x=interval(i,i+1);
		x->p->l=0;
		x->p->renew();
		if(x->p->p)x->p->p->renew();
		delete x;
	}
	T q(int s, int e){ return interval(s,e)->a; }
	void upd(int s, int e, T val){
		N* x=interval(s,e);
		x->addlz(val);
		x->propa();
		//x->renew();
		x->p->renew();
		if(x->p->p) x->p->p->renew();
	}

// private:
	N* nth(N* x, int n){
		if(!x)return x;
		x->propa();
		int ls=(x->l?x->l->s:0);
		if(n<ls) return nth(x->l,n);
		else if(n>ls) return nth(x->r,n-ls-1);
		else return x;
	}
	N* splay(N *x){
		while(x->p)
			x->step_splay();
		return root=x;
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

	struct N{
		N *l=0,*r=0,*p=0;
		int s=1;
		T v=F::idT(),a=F::idT(),lz=F::idU();
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
			p->propa();
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
			if(lz==F::idU()) return;
			v=F::upd(v,lz);
			a=F::updn(a,lz,s,this);
			if(l)l->addlz(lz);
			if(r)r->addlz(lz);
			lz=F::idU();
		}
		void addlz(T val){
			lz = lz==F::idU() ? val : F::propa(lz,val);
		}
		void renew(){
			a=v,s=1;
			if(l)l->propa(),a=F::f(l->a,a),s+=l->s;
			if(r)r->propa(),a=F::f(a,r->a),s+=r->s;
		}
	} *root;
};

