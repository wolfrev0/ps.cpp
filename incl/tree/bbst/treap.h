#pragma once
#include "core/base.h"
#include "math/struct/monoid.h"
#include "misc/random.h"

// //NOTE: height = logN
// template<Monoid Q, Monoid U>
// struct Treap{
// 	using T=decltype(Q::id());
// 	//CRTP is better?
// 	//https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
// 	struct Node{
// 		Node* l()=0;
// 		Node* r()=0;
// 		Node* s()=0;
// 	};
// 	struct NodeImpl{
// 		N *l=0,*r=0;
// 		int s=1, w=rd();
// 		T v=Q::id(),a=Q::id();
// 		N(T v):v(v),a(v){}
// 		~N(){
// 			if(l) delete l;
// 			if(r) delete r;
// 		}
// 		void setL(N* x){l=x; if(x)x->p=this;}
// 		void setR(N* x){r=x; if(x)x->p=this;}
// 		void renew(){
// 			a=Q::f(Q::f(l?l->a:Q::id(),v),r?r->a:Q::id());
// 			s=(l?l->s:0)+(r?r->s:0)+1;
// 		}
// 	} *root=0;
// 	struct NodeNull{
// 	};
// 	Splay(){}
// 	~Splay(){if(root)delete root;}
// 	int size()const{return root->s;}

// };
