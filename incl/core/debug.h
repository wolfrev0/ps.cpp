#pragma once
#include "core/func1.h"
#include "core/config.h"

#if DEBUG
	#undef dbgprint
	#undef dbgprintln
	#define dbgprint(...) osprint(cerr,"\033[0;33m",__VA_ARGS__,"\033[0m").flush()
	#define dbgprintln(...) osprint(cerr,"\033[0;33m",__VA_ARGS__,"\033[0m",'\n').flush()

	//declaration
	template<Printable T>void _dbgprint_(const T& a,int d=0);
	#if CPP20
	template<class T> requires Iterable<T>&&NotPrintable<T> void _dbgprint_(const T& a,int d=0);
	#endif
	template<class A,class B>void _dbgprint_(const pair<A,B>& a,int d);
	template<class TupType,size_t... I>void _dbgprint_(const TupType& _tup,index_sequence<I...>,int d=0);
	template<class... T> void _dbgprint_(const tuple<T...>& _tup,int d=0);

	//printable debug
	template<Printable T>
	void _dbgprint_(const T& a,int d){
		dbgprint(setw(DBG_SETW),a);
	}
	
	#if CPP20
	//iterable debug
	template<class T> requires Iterable<T>&&NotPrintable<T>
	void _dbgprint_(const T& a,int d){
		static string ob="[{(",cb="]})";
		dbgprint('\n',string(d,'-')+ob[d%sz(ob)]);
		for(const auto& i:a){
			_dbgprint_(i,d+1);
			dbgprint(',');
		}
		dbgprint(cb[d%sz(ob)]);
	}
	#endif
	
	//pair debug
	template<class A,class B>void _dbgprint_(const pair<A,B>& a,int d){
		dbgprint('\n',string(d,'-')+'<');
		_dbgprint_(a.fi,d+1);
		dbgprint(',',_dbgprint_(a.se,d+1),'>');
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
	
	#undef dbg
	#undef dbgif
	#undef dbg1
	#undef dbg1if
	#define dbg(...) (cerr<<(#__VA_ARGS__)<<";=",_dbgprint_(mkt(__VA_ARGS__)),dbgprintln(""))
	#define dbgif(bex,...) ((bex)&&dbg(__VA_ARGS__))
	static set<const char*> __z;
	#define dbg1(...) (!__z.count(#__VA_ARGS__)&&(__z.insert(#__VA_ARGS__),dbg(__VA_ARGS__)))
	#define dbg1if(bex,...) (!__z.count(#bex#__VA_ARGS__)&&(bex)&&(__z.insert(#bex#__VA_ARGS__),dbg(__VA_ARGS__)))
#endif
