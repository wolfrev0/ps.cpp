#pragma once
#include "Core.h"

template<typename T, typename U=T>
struct SegfSumAss{
	static T id(){return T();}
	static T q(const T& a, const T& b){return a+b;}
	static T upd(const T& a, const U& b, int c){return b*c;}
	static U propa(const U& a, const U& b){return b;}
};

template<typename T, typename U=T>
struct SegfMinAss{
	static T id(){return inf<T>();}
	static T q(const T& a, const T& b){return min(a,b);}
	static T upd(const T& a, const U& b, int c){return b;}
	static U propa(const U& a, const U& b){return b;}
};

template<typename T, typename U=T>
struct SegfMaxAss{
	static T id(){return -inf<T>();}
	static T q(const T& a, const T& b){return max(a,b);}
	static T upd(const T& a, const U& b, int c){return b;}
	static U propa(const U& a, const U& b){return b;}
};

template<typename T, typename U=T>
struct SegfSumAdd{
	static T id(){return T();}
	static T q(const T& a, const T& b){return a+b;}
	static T upd(const T& a, const U& b, int c){return a+b*c;}
	static U propa(const U& a, const U& b){return a+b;}
};

template<typename T, typename U=T>
struct SegfMinAdd{
	static T id(){return T();}
	static T q(const T& a, const T& b){return min(a,b);}
	static T upd(const T& a, const U& b, int c){return a+b;}
	static U propa(const U& a, const U& b){return a+b;}
};

template<typename T, typename U=T>
struct SegfMaxAdd{
	static T id(){return T();}
	static T q(const T& a, const T& b){return max(a,b);}
	static T upd(const T& a, const U& b, int c){return a+b;}
	static U propa(const U& a, const U& b){return a+b;}
};