#include "Core.h"
#include "FastIO.h"
#include "PrettyIO.h"
//#include "PrettyDebug.h"
#include "XArr.h"

struct A{
	static A* id;
	int i=-2,c=0;
	A *l=id,*r=id;
};
A* A::id=new A{};
auto id=A::id->l=A::id->r=A::id;

int _upd(int s, int e, A* x, A*& y, int i, int v, int idx){
	int m=(s+e)>>1;
	if(y==id) y=new A{idx};
	if(i<=s and e<=i+1) return y->c=x->c+v;
	if(e<=i or i+1<=s) return y=x,y->c;
	return y->c=_upd(s,m,x->l,y->l,i,v,idx)+_upd(m,e,x->r,y->r,i,v,idx);
}
int _q1(int s, int e, A* x, int k, int idx, int bit){
	int m=(s+e)>>1;
	if(!~bit) return s;
	if(k>>bit&1) return x->l->i>=idx?_q1(s,m,x->l,k,idx,bit-1):_q1(m,e,x->r,k,idx,bit-1);
	return x->r->i>=idx?_q1(m,e,x->r,k,idx,bit-1):_q1(s,m,x->l,k,idx,bit-1);
}
int _q2(int s, int e, A* x, int k){
	int m=(s+e)>>1;
	if(e-s==1) return x->c;
	return k<m?_q2(s,m,x->l,k):x->l->c+_q2(m,e,x->r,k);
}
int _q3(int s, int e, A* x, A* y, int k){
	int m=(s+e)>>1;
	if(e-s==1) return s;
	return y->l->c-x->l->c>=k?_q3(s,m,x->l,y->l,k):_q3(m,e,x->r,y->r,k-y->l->c+x->l->c);
}
A* upd(A* x, int i, int v, int idx){ A* y=id; _upd(0,1<<19,x,y,i,v,idx); return y; }
int q1(A* x, int k, int idx){ return _q1(0,1<<19,x,k,idx,18); }
int q2(A* x, int k){ return _q2(0,1<<19,x,k); }
int q3(A* x, A* y, int k){ return _q3(0,1<<19,x,y,k); }

signed main(){
	XArr<A*> a={new A{-1}};
	CIN(int,m);
	rep(_,m){
		CIN(int,t);
		if(t==1){ CIN(int,x); a.emplb(upd(a.back(),x,1,sz(a)-1)); }
		if(t==2){ CIN(int,l,r,x); l--,r--; cout<<q1(a[r],x,l)<<endl; }
		if(t==3){ CIN(int,k); a.erase(a.end()-k,a.end()); }
		if(t==4){ CIN(int,l,r,x); l--,r--; cout<<q2(a[r],x)-q2(a[l-1],x)<<endl; }
		if(t==5){ CIN(int,l,r,k); l--,r--; cout<<q3(a[l-1],a[r],k)<<endl; }
	}
}
//https://www.acmicpc.net/problem/13538