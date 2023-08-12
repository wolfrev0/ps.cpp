#include "tree/seg/seg.h"
#include "tree/seg/segdyn.h"

#define endl '\n' // Remove it when interactive
#define CHECK_INPUT 0
#define TC 1
#define TC_OUT_PREFIX ""//"Case #",ti,": "
signed main(){
	void solve();
	for(int ti=1,t=TC;ti<=t;ti++)
		print(TC_OUT_PREFIX),
		solve();
#if CHECK_INPUT
	assert(cin.get()=='\n');
	assert(cin.get()==EOF);
#endif
}

//min k: https://atcoder.jp/contests/abc281/submissions/37162839
//another method: incl/misc/topk.h
void solve(){
	SegDyn<MAdd<int>> st0, st1;
	func(void,add,int x){
		st0.upd(x,st0.q(x,x+1)+1);
		st1.upd(x,st1.q(x,x+1)+x);
	};
	func(void,del,int x){
		st0.upd(x,st0.q(x,x+1)-1);
		st1.upd(x,st1.q(x,x+1)-x);
	};
	func(int,qry,int k){
		int m=st0.suffix_search(lam(acc>=k,int acc,int i));
		return st1.q(m,inf<int>())-(st0.q(m,inf<int>())-k)*m;
	};
	//return k that (max k sum) >= sum
	//https://atcoder.jp/contests/abc314/submissions/44531493
	func(int,qry_by_sum,int sum){
		int m=st1.suffix_search(lam(acc>=sum,int acc,int i));
		int sum_cur=st1.q(0,m,inf<int>());
		int x=(sum_cur-sum)/m;
		return st0.q(0,m,inf<int>())-x;
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
