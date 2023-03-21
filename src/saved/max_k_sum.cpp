#include "tree/seg/seg.h"
#include "tree/seg/segdyn.h"
//min k: https://atcoder.jp/contests/abc281/submissions/37162839
void solve(){
	// int n=10;
	// Seg<MAdd<int>> st0(n),st1(n);
	// func(void,add,int x){
	// 	st0.upd(x,st0.q(x)+1);
	// 	st1.upd(x,st1.q(x)+x);
	// };
	// func(void,del,int x){
	// 	st0.upd(x,st0.q(x)-1);
	// 	st1.upd(x,st1.q(x)-x);
	// };
	// func(int,qry,int k){
	// 	int m=st0.liftRL(lam(acc>=k,int acc,int i));
	// 	return st1.q(m,n)-(st0.q(m,n)-k)*m;
	// };
	SegDyn<MAdd<int>,lamp(x+y,int x,int y)> st0,st1;
	func(void,add,int x){
		st0.upd(x,1);
		st1.upd(x,x);
	};
	func(void,del,int x){
		st0.upd(x,-1);
		st1.upd(x,-x);
	};
	func(int,qry,int k){
		int m=st0.liftRL(lam(acc>=k,int acc,int i));
		return st1.q(m,inf<int>())-(st0.q(m,inf<int>())-k)*m;
	};
	add(3);
	add(4);
	add(5);
	println(qry(2));
	del(4);
	println(qry(2));
	add(5);
	println(qry(2));
}
