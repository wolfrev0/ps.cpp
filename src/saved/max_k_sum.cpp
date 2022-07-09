#include "tree/seg/seg.h"
#include "tree/seg/segdyn.h"

signed main(){
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
	// 	return st1.q(m,n);
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
		return st1.q(m,inf<int>());
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
