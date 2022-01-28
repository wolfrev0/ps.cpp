#pragma once
#include "core/func1.h"
#include "core/config.h"

#undef watch
#if DEBUG
	template<class T>concept Printable=requires(T x){cout<<x<<endl;};
	template<class T>concept NotPrintable=not Printable<T>;
	template<class T>concept Iterable=requires(T x){{x}->NotPrintable;x.begin();x.end();begin(x);end(x);};

	//declaration
	template<Printable T>void _dbgprint_(const T& a,int d=0);
	template<Iterable T>void _dbgprint_(const T& a,int d=0);
	template<class A,class B>void _dbgprint_(const pair<A,B>& a,int d);
	template<class TupType,size_t... I>void _dbgprint_(const TupType& _tup,index_sequence<I...>,int d=0);
	template<class... T> void _dbgprint_(const tuple<T...>& _tup,int d=0);

	//printable debug
	template<Printable T>
	void _dbgprint_(const T& a,int d){cerr<<setw(DBG_SETW)<<a<<',';}
	
	//iterable debug
	template<Iterable T>
	void _dbgprint_(const T& a,int d){
		static string ob="[{(",cb="]})";
		cerr<<endl<<string(d,'-')+ob[d%sz(ob)];
		for(const auto& i:a)_dbgprint_(i,d+1);
		cerr<<cb[d%sz(ob)];}
	
	//pair debug
	template<class A,class B>void _dbgprint_(const pair<A,B>& a,int d){
		cerr<<endl<<string(d,'-')+'<';
		_dbgprint_(a.fi,d+1),_dbgprint_(a.se,d+1);
		cerr<<'>';}
	
	//tuple debug
	template<class TupType,size_t... I>
	void _dbgprint_(const TupType& _tup,index_sequence<I...>,int d){
		cerr<<endl<<string(d,'-')+'<';
		(...,_dbgprint_(get<I>(_tup),d+1));
		cerr<<'>';}
	template<class... T> void _dbgprint_(const tuple<T...>& _tup,int d){
		_dbgprint_(_tup,make_index_sequence<sizeof...(T)>(),d);}
	
	#define watch(...)(cerr<<(#__VA_ARGS__)<<";=",_dbgprint_(mkt(__VA_ARGS__)),cerr<<endl)
#else
	#define watch(...)
#endif