#pragma once
#include "core/base.h"

struct Node{
	int v=0;
	Node *l=0,*r=0;

	int upd(int cs, int ce, int s, int e, int x){
		if(ce<=s or e<=cs)return 0;
		if(s<=cs and ce<=e)return v+=x*(ce-cs);
		int cm=(cs+ce)/2;
		if(!l)l=new Node;
		if(!r)r=new Node;
		return v=l->upd(cs,cm,s,e,x)+r->upd(cm,ce,s,e,x);
	}
	int q(int cs, int ce, int s,int e){
		if(ce<=s or e<=cs)return 0;
		if(s<=cs and ce<=e) return v;
		int cm=(cs+ce)/2;
		if(!l)l=new Node;
		if(!r)r=new Node;
		return l->q(cs,cm,s,e)+r->q(cm,ce,s,e);
	}
};
