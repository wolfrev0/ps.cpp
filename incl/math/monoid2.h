#pragma once
#include "core/base.h"

// template<class T, class U=T> struct PlusPlus{
// 	static cxp Monoid<T> mq;
// 	static cxp Monoid<U> mu;
// 	cxp static T updn(T a, U b, int c, auto*x){return a+b*c;}
// 	cxp static U propa(U a, U b){return a+b;}
// };
// template<class T, class U=T> struct PlusAss{
// 	static cxp Monoid<T> mq;
// 	static cxp Monoid<U,[](T x,U y){return y;},inf<U>()> mu;
// 	cxp static T updn(T a, U b, int c, auto*x){return b*c;}
// 	cxp static U propa(U a, U b){return b;}
// };

template<class T, class U=T> struct PlusPlus{
	cxp static T idT(){return T(0);}
	cxp static T idU(){return U(0);}
	cxp static T f(T a, T b){return a+b;}
	cxp static T upd(T a, U b){return a+b;}
	//For Lazy
	cxp static T updn(T a, U b, int c, auto*x){return a+b*c;}
	cxp static U propa(U a, U b){return a+b;}
};
template<class T, class U=T> struct PlusAss{
	cxp static T idT(){return T(0);}
	cxp static T idU(){return inf<U>();}
	cxp static T f(T a, T b){return a+b;}
	cxp static T upd(T a, U b){return b;}
	cxp static T updn(T a, U b, int c, auto*x){return b*c;}
	cxp static U propa(U a, U b){return b;}
};
template<class T, class U=T> struct MinPlus{
	cxp static T idT(){return inf<T>();}
	cxp static T idU(){return U(0);}
	cxp static T f(T a, T b){return min(a,b);}
	cxp static T upd(T a, U b){return a+b;}
	cxp static T updn(T a, U b, int c, auto*x){return a+b;}
	cxp static U propa(U a, U b){return a+b;}
};
template<class T, class U=T> struct MinAss{
	cxp static T idT(){return inf<T>();}
	cxp static T idU(){return inf<U>();}
	cxp static T f(T a, T b){return min(a,b);}
	cxp static T upd(T a, U b){return b;}
	cxp static T updn(T a, U b, int c, auto*x){return b;}
	cxp static U propa(U a, U b){return b;}
};
template<class T, class U=T> struct MaxPlus{
	cxp static T idT(){return -inf<T>();}
	cxp static T idU(){return U(0);}
	cxp static T f(T a, T b){return max(a,b);}
	cxp static T upd(T a, U b){return a+b;}
	cxp static T updn(T a, U b, int c, auto*x){return a+b;}
	cxp static U propa(U a, U b){return a+b;}
};
template<class T, class U=T> struct MaxAss{
	cxp static T idT(){return -inf<T>();}
	cxp static T idU(){return -inf<U>();}
	cxp static T f(T a, T b){return max(a,b);}
	cxp static T upd(T a, U b){return b;}
	cxp static T updn(T a, U b, int c, auto*x){return b;}
	cxp static U propa(U a, U b){return b;}
};

template<class T, class U=T> struct XorAss{
	cxp static T idT(){return T(0);}
	cxp static T idU(){return inf<U>();}
	cxp static T f(T a, T b){return a^b;}
	cxp static T upd(T a, U b){return b;}
	cxp static T updn(T a, U b, int c, auto*x){return c%2?b:U(0);}
	cxp static U propa(U a, U b){return b;}
};
template<class T, class U=T> struct XorXor{
	cxp static T idT(){return T(0);}
	cxp static T idU(){return U(0);}
	cxp static T f(T a, T b){return a^b;}
	cxp static T upd(T a, U b){return a^b;}
	cxp static T updn(T a, U b, int c, auto*x){return a^(c%2?b:U(0));}
	cxp static U propa(U a, U b){return a^b;}
};

//Splay Only
template<class T, class U=T> struct PlusFlip{
	cxp static T idT(){return T(0);}
	cxp static T idU(){return U(0);}
	cxp static T f(T a, T b){return a+b;}
	cxp static T upd(T a, U b){return a;}
	cxp static T updn(T a, U b, int c, auto*x){ if(b)swap(x->l,x->r);return a;}
	cxp static U propa(U a, U b){return a^b;}
};