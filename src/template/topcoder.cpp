#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;

#define int i64
#define FP_EPS 1e-11
#define COUT_FP 11
using f64=double;
// #define CPP20 1
// #define ARGAUTO 1
#define DBG_SETW 3

#define pushb(...) push_back({__VA_ARGS__})
#define pushf(...) push_front({__VA_ARGS__})
#define push_(...) push({__VA_ARGS__})
#define popb pop_back
#define popf pop_front
#define fi first
#define se second
#define mkp make_pair
#define mkt make_tuple
#define cxp constexpr
#define lb lower_bound
#define ub upper_bound
#define reduce accumulate
#define itos to_string
using i64=long long;using u64=unsigned long long;
using pint=pair<int,int>;using tint=tuple<int,int,int>;
template<class T>using Str=basic_string<T>;

//Handy Funcs
template<class T>int sz(const T& x){return x.size();}
template<class T>cxp T inf(){return numeric_limits<T>::max()/2;}
int divc(int a,int b){if(b<0)a=-a,b=-b;return (a>0)?(a+b-1)/b:a/b;}
int divf(int a,int b){if(b<0)a=-a,b=-b;return (a>0)?a/b:(a-b+1)/b;}
cxp int lg2f(int x){return 63-__builtin_clzll(x);}
cxp int lg2c(int x){return 64-__builtin_clzll(x-1);}
template<class T>inline T sq(T x){return x*x;}

void WARN(bool cond,const char* str){
	#if DEBUG
	static set<const char*> z;
	if(cond&&!z.count(str))z.insert(str),cerr<<"[WARN] "<<str<<endl;
	#endif
}

template<class T, class P=
#if CPP20
conditional_t<is_same<bool,T>::value,deque<T>,vector<T>>>
#else
vector<T>>
#endif
struct Arr:public P{
	Arr(){P::shrink_to_fit();}
	explicit Arr(signed n,T init=T()):P(n,init){}
	Arr(initializer_list<T>il):P(il){}
#ifdef ARGAUTO
	Arr(auto its, auto ite):P(its,ite){}
#endif
	T& operator[](signed i){
		WARN(i<0,"Negative Index Found");
		return P::operator[](i>=0?i:i+this->size());
	}
	const T& operator[](signed i)const{return P::operator[](i>=0?i:i+this->size());}
	T& at(signed i){return *this[i];}
	const T& at(signed i)const{return *this[i];}
};
#if ARGAUTO
template<class... A> auto ARR(auto n,A&&... a)
{if constexpr(!sizeof...(a)) return n; else return Arr(n,ARR(a...));}
#endif

//Monoid
#ifdef CPP20
template<class T, auto _f=[](T x,T y){return x+y;}, T _id=0>
struct Monoid{static cxp auto f=_f,id=_id;};
template<class T, class M=Monoid<T>>
Arr<T> cumf(const Arr<T>& a){
	Arr<T> b(sz(a)+1,M::id);
	for(int i=0;i<sz(a);i++)
		b[i]=M::f(b[i-1],a[i]);
	return b;
}
#endif

//Func Exts
#define ARG(...) __VA_ARGS__
#define func(RetT,fname,...) function<RetT(__VA_ARGS__)> fname=[&](__VA_ARGS__)->RetT
#define lam(expr,...) [&](__VA_ARGS__){return expr;}

template<class T,class U>bool assmin(T& a,U&& b){return a>b?a=b,true:false;}
template<class T,class U>bool assmax(T& a,U&& b){return a<b?a=b,true:false;}
template<class T>int argmin(const Arr<T>& a){return min_element(a.begin(),a.end())-a.begin();}
template<class T>int argmax(const Arr<T>& a){return max_element(a.begin(),a.end())-a.begin();}
Arr<int> range(int n){Arr<int> r;while(n--)r.pushb(sz(r));return r;}
template<class T>Arr<pair<int,T>> enumer(const Arr<T>& a){
	Arr<pair<int,T>> r;
	for(auto&i:a)r.pushb(sz(r),i);
	return r;
}


#define PQ std::priority_queue
template<class T>using PQMax=PQ<T>;
template<class T>using PQMin=PQ<T,vector<T>,greater<T>>;

//Consts
const f64 pi=acosl(-1),eps=FP_EPS;
const int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};

struct CLASSNAME{
};
#undef int
#pragma GCC diagnostic pop