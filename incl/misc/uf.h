#pragma once
#include "core/base.h"

//NOTE: 그룹union시 부가적인 연산 필요하면 걍 복붙해서 고쳐쓰는게 편하다(9938,3830등)
struct UFgroup{
	Arr<int> p;
	Arr<Arr<int>> g;
	UFgroup(int n=0):p(n),g(n){
		for(int i=0;i<n;i++)
			p[i]=i,g[i]={i};
	}
	//return false when already unioned
	bool uni(int a,int b){
		a=r(a),b=r(b);
		if(a==b)
			return false;
		// union by size
		if(sz(g[a])<sz(g[b]))
			swap(a,b);
		p[b]=a;
		g[a].insert(g[a].end(),g[b].begin(),g[b].end());
		g[b].clear();
		return true;
	}
	int r(int a){return p[a]==a?a:p[a]=r(p[a]);}//root of a
	bool eq(int a,int b){return r(a)==r(b);}
	int gsz(int a){return sz(g[r(a)]);}
};
struct UFtree{
	int gc;
	Arr<int> p,s;
	Arr<Arr<int>> ch;
	UFtree(int n=0):gc(n),p(n),s(n,1),ch(n){
		iota(p.begin(),p.end(),0);
	}
	//return false when already unioned
	bool uni(int a,int b){
		a=r(a),b=r(b);
		if(a==b)
			return false;
		// union by size
		if(s[a]<s[b])
			swap(a,b);
		p[b]=a;
		s[a]+=s[b];
		ch[a].push_back(b);
		gc--;
		return true;
	}
	//no path compression
	int r(int a){
		return p[a]==a?a:r(p[a]);
	}
	bool eq(int a,int b){return r(a)==r(b);}
	int gsz(int a){return s[r(a)];}
};

// struct UFundo{
// 	struct A{int b=-1,sb=-1;};
// 	int gc;
// 	Arr<int> p,s;
// 	stack<A> uis;
// 	UFundo(int n=0):gc(n),p(n),s(n,1){for(int i=0;i<n;i++)p[i]=i;}
// 	//return false when already unioned
// 	bool uni(int a,int b){
// 		a=r(a),b=r(b);
// 		if(a!=b){
// 			// union by size
// 			if(s[a]<s[b])swap(a,b);
// 			uis.emplace(b,s[b]);
// 			p[b]=a,s[a]+=s[b],s[b]=0,gc--;
// 			return true;}
// 		uis.emplace();
// 		return a!=b;}
// 	void undo(){
// 		auto ui=uis.top();uis.pop();
// 		if(ui.b==-1)return;
// 		int a=r(ui.b),b=ui.b;
// 		gc++,s[b]=ui.sb,s[a]-=s[b],p[b]=b;}
// 	int r(int a){return p[a]==a?a:r(p[a]);}
// 	bool eq(int a,int b){return r(a)==r(b);}
// 	int gsz(int a){return s[r(a)];}
// };
