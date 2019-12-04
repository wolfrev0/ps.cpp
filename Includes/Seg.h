#pragma once
#include "Core.h"

//Upd=Assignment
template<typename T, typename F>
struct Seg{
	static_assert(F::q(F::id(),F::id())==F::id());
	Seg(int n=0, T init=F::id()):n(n), tr(4*n, init){}
	T q(int p){return q(p,p+1);}
	T q(int s, int e){return q(1,0,n,s,e);}
	void upd(int p, T val){upd(1,0,n,p,val);}
protected:
	int n;
	Arr<T> tr;

	T q(int cur, int cs, int ce, int s, int e){
		if (s>=ce||e<=cs)
			return F::id();
		if (s<=cs&&ce<=e)
			return tr[cur];
		int m=(cs+ce)/2;
		return F::q(q(cur*2,cs,m,s,e),q(cur*2+1,m,ce,s,e));
	}

	void upd(int cur, int cs, int ce, int p, T val){
		if (p>=ce||p+1<=cs)
			return;
		if (p<=cs&&ce<=p+1){
			tr[cur]=val;
			return;
		}
		int m=(cs+ce)/2;
		upd(cur*2,cs,m,p,val);
		upd(cur*2+1,m,ce,p,val);
		tr[cur]=F::q(tr[cur*2],tr[cur*2+1]);
	}
};

//For c++2a
// //Upd=Assignment
// template<typename T, T id=T(), auto qf=[](T a, T b){return a+b;}>
// struct Seg{
// 	Seg(int n=0):n(n), tr(4*n, id){}
// 	T q(int p){return q(p,p+1);}
// 	T q(int s, int e){return q(1,0,n,s,e);}
// 	void upd(int p, T val){upd(1,0,n,p,val);}
// protected:
// 	int n;
// 	Arr<T> tr;

// 	T q(int cur, int cs, int ce, int s, int e){
// 		if (s>=ce||e<=cs)
// 			return id;
// 		if (s<=cs&&ce<=e)
// 			return tr[cur];
// 		int m=(cs+ce)/2;
// 		return qf(q(cur*2,cs,m,s,e),q(cur*2+1,m,ce,s,e));
// 	}

// 	void upd(int cur, int cs, int ce, int p, T val){
// 		if (p>=ce||p+1<=cs)
// 			return;
// 		if (p<=cs&&ce<=p+1){
// 			tr[cur]=val;
// 			return;
// 		}
// 		int m=(cs+ce)/2;
// 		upd(cur*2,cs,m,p,val);
// 		upd(cur*2+1,m,ce,p,val);
// 		tr[cur]=qf(tr[cur*2],tr[cur*2+1]);
// 	}
// };