#pragma once
#include <bits/stdc++.h>
#define _EXT_CODECVT_SPECIALIZATIONS_H 1
#define _EXT_ENC_FILEBUF_H 1
using namespace std;
#pragma GCC diagnostic ignored "-Wparentheses"
#define SYSCALL_ALLOWED 1
#if SYSCALL_ALLOWED
	#include <bits/extc++.h>
	#include <ext/rope>
#endif


// Const
using i32=signed;
using u32=unsigned;
using i64=long long;
using u64=unsigned long long;
#define int i64
using fp=double; //long double,__float128
const fp pi=acos(-1)/*numbers::pi_v<fp>*/,eps=1e-11;
const int dir4[4][2]={{0,1},{-1,0},{0,-1},{1,0}};
const int dir8[8][2]={{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1}};


// Utility
#define fi first
#define se second
#define mkp make_pair
#define mkt make_tuple
#define lb lower_bound
#define ub upper_bound
#define itos to_string
#define sz ssize
#define head(x) (x.begin())
#define tail(x) prev(x.end())
#define ARG(...) __VA_ARGS__
#define func(RetT,fname,...) function<RetT(__VA_ARGS__)> fname=[&](__VA_ARGS__)->RetT
#define lam(expr,...) [&](__VA_ARGS__){return expr;}
#define lamp(expr,...) [](__VA_ARGS__){return expr;}
using pint=pair<int,int>;using tint=tuple<int,int,int>;
template<class T>concept PrintPrimitive=requires(T x){cout<<x;};
template<class T>concept NotPrintPrimitive=not PrintPrimitive<T>;
template<class T>concept InputPrimitive=requires(T x){cin>>x;};
template<class T>concept NotInputPrimitive=not InputPrimitive<T>;
template<class T>concept Iterable=requires(T x){x.begin();x.end();begin(x);end(x);};
template<class T>using Str=basic_string<T>;
template<class T,class CMP=less<>>using PQ=std::priority_queue<T,vector<T>,CMP>;
template<class T, class P=vector<T>> struct Arr:public P{
	Arr(){P::shrink_to_fit();}
	explicit Arr(i32 n):P(n,T()){}
	explicit Arr(i32 n,T init):P(n,init){}
	Arr(initializer_list<T>il):P(il){}
	Arr(auto its, auto ite):P(its,ite){}
	inline T& operator[](i32 i){return P::operator[](i<0?i+sz(*this):i);}
	const T& operator[](i32 i)const{return P::operator[](i<0?i+sz(*this):i);}
	T& at(i32 i){return *this[i];}
	const T& at(i32 i)const{return *this[i];}
};
template<class... A> auto ARR(auto n,A&&... a)
{if constexpr(!sizeof...(a)) return n; else return Arr(n,ARR(a...));}
template<Iterable T> map<typename T::value_type,Arr<int>> classify(const T& a){
	map<typename T::value_type,Arr<int>> r;
	int idx=0;
	for(auto x:a)
		r[x].push_back(idx++);
	return r;
}
auto key2cmp(auto key){return [key](auto x, auto y){return mkp(key(x),x)<mkp(key(y),y);};}
auto fmap(auto a, auto f)->remove_reference_t<decltype(a)>{
	auto b=a;
	for(auto&i:b)
		i=f(i);
	return b;
}


// Math
int fdiv(int a,int b){return a/b-((a^b)<0&&a%b);}
int cdiv(int a,int b){return (a^b>0)?(a+b-1)/b:a/b;}
i64 flg2(u64 x){return 63-countl_zero(x);}
i64 clg2(u64 x){return x-1==0?0:64-countl_zero(x-1);}
int fsqrt(i64 n) {i64 i=sqrtl(n);while(i*i>n)i--;while(i*i<=n)i++;return i-1;}
int csqrt(i64 n) {i64 i=sqrtl(n);while(i*i>=n)i--;while(i*i<n)i++;return i;}
template<class T>T sq(T x){return x*x;}
template<class T>constexpr T inf(){return numeric_limits<T>::max()/2;}
template<class T>constexpr T nan(){return numeric_limits<T>::max();}
template<typename T> concept MemberInf=requires(T t){t.inf();};
template<typename T> concept MemberNan=requires(T t){t.nan();};
template<MemberInf T>T inf(){return T().inf();}
template<class T>int argmin(const Arr<T>& a){return min_element(a.begin(),a.end())-a.begin();}
template<class T>int argmax(const Arr<T>& a){return max_element(a.begin(),a.end())-a.begin();}
template<class T,class U>bool assmin(T& a,U&& b){return a>b?a=b,true:false;}
template<class T,class U>bool assmax(T& a,U&& b){return a<b?a=b,true:false;}


// IO & misc
#define print(...) osprint(cout,__VA_ARGS__)
#define println(...) osprint(cout,__VA_ARGS__,'\n')
template<class T=int,class... Ts> requires InputPrimitive<T>
tuple<T,Ts...> input(istream& is=cin){
	T x; is>>x;
	if constexpr (sizeof...(Ts)==0) return mkt(x);
	else return tuple_cat(mkt(x),input<Ts...>());
}
template<class T> requires InputPrimitive<T>
T input(T&& a, istream& is=cin){ is>>a; return a;}
template<class T> requires NotInputPrimitive<T>&&Iterable<T>
T input(T&& a){ for(auto&i:a)input(i); return a; }
template<class T=int> T input1(istream& is=cin){return get<0>(input<T>());}
template<class...A>ostream& osprint(ostream& os, A...a){return ((os<<a),...);}
template<typename... Args, size_t... Is>
void read_tuple(istream& is, tuple<Args...>& tuple, index_sequence<Is...>) { (..., (is >> std::get<Is>(tuple)));}
template<class T, class U> istream& operator>>(istream& is, pair<T,U>& a){ return is>>a.fi>>a.se; }
template<typename... Args> istream& operator>>(istream& is, tuple<Args...>& tuple){
	read_tuple(is, tuple, index_sequence_for<Args...>{});
	return is;
}


// Debug
#if !DEBUG
	#define dbgprint(...) void(0)
	#define dbgprintln(...) void(0)
	#define dbg(...) void(0)
	#define dbgif(...) void(0)
	#define dbg1(...) void(0)
	#define dbg1if(...) void(0)
#else
	#define dbgprint(...) osprint(cerr,"\033[0;33m",__VA_ARGS__,"\033[0m").flush()
	#define dbgprintln(...) osprint(cerr,"\033[0;33m",__VA_ARGS__,"\033[0m",'\n').flush()

	//declaration
	template<PrintPrimitive T>void _dbgprint_(const T& a,int d=0);
	template<class T> requires Iterable<T>&&NotPrintPrimitive<T> void _dbgprint_(const T& a,int d=0);
	template<class A,class B>void _dbgprint_(const pair<A,B>& a,int d);
	template<class TupType,size_t... I>void _dbgprint_(const TupType& _tup,index_sequence<I...>,int d=0);
	template<class... T> void _dbgprint_(const tuple<T...>& _tup,int d=0);

	//printable debug
	template<PrintPrimitive T>
	void _dbgprint_(const T& a,int d){
		dbgprint(setw(3),a);
	}
	
	//iterable debug
	template<class T> requires Iterable<T>&&NotPrintPrimitive<T>
	void _dbgprint_(const T& a,int d){
		static string ob="[{(",cb="]})";
		dbgprint('\n',string(d,'-')+ob[d%sz(ob)]);
		for(const auto& i:a){
			_dbgprint_(i,d+1);
			dbgprint(',');
		}
		dbgprint(cb[d%sz(ob)]);
	}
	
	//pair debug
	template<class A,class B>void _dbgprint_(const pair<A,B>& a,int d){
		dbgprint('\n',string(d,'-')+'<');
		_dbgprint_(a.fi,d+1);
		dbgprint(','),_dbgprint_(a.se,d+1),dbgprint('>');
	}
	
	//tuple debug
	template<class TupType,size_t... I>
	void _dbgprint_(const TupType& _tup,index_sequence<I...>,int d){
		dbgprint('\n',string(d,'-')+'<');
		( ..., (_dbgprint_(get<I>(_tup),d+1),dbgprint(',')) );
		dbgprint('>');
	}
	template<class... T> void _dbgprint_(const tuple<T...>& _tup,int d){
		_dbgprint_(_tup,make_index_sequence<sizeof...(T)>(),d);
	}
	
	#define dbg(...) (dbgprint((#__VA_ARGS__),";="),_dbgprint_(mkt(__VA_ARGS__)),dbgprintln(""))
	#define dbgif(bex,...) ((bex)&&dbg(__VA_ARGS__))
	static set<const char*> __z;
	#define dbg1(...) (!__z.count(#__VA_ARGS__)&&(__z.insert(#__VA_ARGS__),dbg(__VA_ARGS__)))
	#define dbg1if(bex,...) (!__z.count(#bex#__VA_ARGS__)&&(bex)&&(__z.insert(#bex#__VA_ARGS__),dbg(__VA_ARGS__)))
#endif


// Pre-run
auto __PR=(cout<<fixed<<setprecision(10),0);
#if !(DEBUG)
auto __PR_NDB=(ios::sync_with_stdio(0),cin.tie(0),cout.tie(0));
#endif


