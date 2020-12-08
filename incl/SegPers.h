#include "Core.h"
//#include "FastIO.h"
#include "PrettyIO.h"
//#include "PrettyDebug.h"
#include "XArr.h"

struct A{
	static A* id;
	int i=-2,c=0;
	A *l=id,*r=id;
	int upd(int cs, int ce, A*& y, int i, int v, int idx){
		int cm=(cs+ce)>>1;
		if(y==id) y=new A{idx};
		if(i<=cs and ce<=i+1) return y->c=c+v;
		if(ce<=i or i+1<=cs) return y=this,y->c;
		return y->c=l->upd(cs,cm,y->l,i,v,idx)+r->upd(cm,ce,y->r,i,v,idx);
	}
	int q1(int cs, int ce, int k, int idx, int bit){
		int cm=(cs+ce)>>1;
		if(!~bit) return cs;
		if(k>>bit&1) return l->i>=idx?l->q1(cs,cm,k,idx,bit-1):r->q1(cm,ce,k,idx,bit-1);
		return r->i>=idx?r->q1(cm,ce,k,idx,bit-1):l->q1(cs,cm,k,idx,bit-1);
	}
	int q2(int cs, int ce, int k){
		int cm=(cs+ce)>>1;
		if(ce-cs==1) return c;
		return k<cm?l->q2(cs,cm,k):l->c+r->q2(cm,ce,k);
	}
	int q3(int cs, int ce, A* y, int k){
		int cm=(cs+ce)>>1;
		if(ce-cs==1) return cs;
		return y->l->c-l->c>=k?l->q3(cs,cm,y->l,k):r->q3(cm,ce,y->r,k-y->l->c+l->c);
	}
	A* upd(int i, int v, int idx){ A* y=id; upd(0,1<<19,y,i,v,idx); return y; }
	int q1(int k, int idx){ return q1(0,1<<19,k,idx,18); }
	int q2(int k){ return q2(0,1<<19,k); }
	int q3(A* y, int k){ return q3(0,1<<19,y,k); }
};
A* A::id=new A{};
auto id=A::id->l=A::id->r=A::id;

signed main(){
	XArr<A*> a={new A{-1}};
	CIN(int,m);
	rep(_,m){
		CIN(int,t);
		if(t==1){ CIN(int,x); a.emplb(a.back()->upd(x,1,sz(a)-1)); }
		if(t==2){ CIN(int,l,r,x); l--,r--; cout<<a[r]->q1(x,l)<<endl; }
		if(t==3){ CIN(int,k); a.erase(a.end()-k,a.end()); }
		if(t==4){ CIN(int,l,r,x); l--,r--; cout<<a[r]->q2(x)-a[l-1]->q2(x)<<endl; }
		if(t==5){ CIN(int,l,r,k); l--,r--; cout<<a[l-1]->q3(a[r],k)<<endl; }
	}
}

//https://www.acmicpc.net/problem/13538

//https://aruz.tistory.com/82 여기 코드처럼 update가 새로운 노드를 반환하게 짜는게 깔끔한듯. 수정하자.