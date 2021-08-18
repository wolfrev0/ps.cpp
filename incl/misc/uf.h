#pragma once
#include "core/base.h"

//NOTE: 그룹union시 부가적인 연산 필요하면 걍 복붙해서 고쳐쓰는게 편하다(9938,3830등)
struct UF{
	Arr<int> p,s;
	UF(int n=0):p(n),s(n,1){for(int i=0;i<n;i++)p[i]=i;}
	//return false when already unioned
	bool uni(int a,int b){
		a=r(a),b=r(b);
		if(a==b)return false;
		// union by size
		if(s[a]<s[b])swap(a,b);
		p[b]=a,s[a]+=s[b],s[b]=0;
		return true;
	}
	int r(int a){return p[a]==a?a:p[a]=r(p[a]);}//root of a
	bool eq(int a,int b){return r(a)==r(b);}
	int size(int a){return s[r(a)];}
};

//Not tested yet
struct undoUF{
	struct undoinfo{int b=-1,pb=-1,sb=-1;};
	Arr<int> p,s;
	stack<undoinfo> uis;
	undoUF(int n=0):p(n),s(n,1){for(int i=0;i<n;i++)p[i]=i;}
	//return false when already unioned
	bool uni(int a,int b){
		a=find(a),b=find(b);
		undoinfo ui;
		if(a!=b){
			// union by size
			if(s[a]<s[b])swap(a,b);
			ui.b=b, ui.pb=p[b], ui.sb=s[b];
			p[b]=a, s[a]+=s[b], s[b]=0;
			uis.empl(ui);
			return true;
		}
		uis.empl(ui);
		return a!=b;
	}
	void undo(){
		auto ui=uis.top();uis.pop();
		if(ui.b==-1)return;
		int a=find(ui.b),b=ui.b;
		s[b]=ui.sb, s[a]-=s[b], p[b]=ui.pb;
	}
	int find(int a){return p[a]==a?a:find(p[a]);}
	bool eq(int a,int b){return find(a)==find(b);}
	int size(int a){return s[find(a)];}
};
