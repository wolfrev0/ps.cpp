#pragma once
#include "core/base.h"

//https://codeforces.com/contest/1555/submission/124802305
//MLE시 좌표압축하면 메모리 많이 줆 https://www.acmicpc.net/source/31803947
struct Node{
	int v=0,w=0;
	Node *l=0,*r=0;

	void upd(int cs, int ce, int s, int e, int x){
		if(ce<=s or e<=cs)return;
		if(s<=cs and ce<=e){
			w+=x;
			v=w?ce-cs:(l?l->v:0)+(r?r->v:0);
			return;
		}
		int cm=(cs+ce)/2;
		if(!l)l=new Node;
		if(!r)r=new Node;
		l->upd(cs,cm,s,e,x), r->upd(cm,ce,s,e,x);
		v=w?ce-cs:l->v+r->v;
	}
	//Not tested
	int q(int cs, int ce, int s,int e){
		if(ce<=s or e<=cs)return 0;
		if(s<=cs and ce<=e) return v;
		if(w) return min(e,ce)-max(s,cs);
		int cm=(cs+ce)/2;
		if(!l)l=new Node;
		if(!r)r=new Node;
		return l->q(cs,cm,s,e)+r->q(cm,ce,s,e);
	}
}st;