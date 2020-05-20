#pragma once
#include "Core.h"

template<typename T>
struct SegfSumAss{
	static T id(){return T();}
	static T q(T a, T b){return a+b;}
	static void upd(T& tv, T uv, int cs, int ce){tv=uv*(ce-cs);}
	static T propa(T a, T b){return b;}
};

template<typename T>
struct SegfMinAss{
	static T id(){return inf<T>();}
	static T q(T a, T b){return min(a,b);}
	static void upd(T& tv, T uv, int cs, int ce){tv=uv;}
	static T propa(T a, T b){return b;}
};

template<typename T>
struct SegfMaxAss{
	static T id(){return -inf<T>();}
	static T q(T a, T b){return max(a,b);}
	static void upd(T& tv, T uv, int cs, int ce){tv=uv;}
	static T propa(T a, T b){return b;}
};

template<typename T>
struct SegfSumAdd{
	static T id(){return T();}
	static T q(T a, T b){return a+b;}
	static void upd(T& tv, T uv, int cs, int ce){tv=tv+uv*(ce-cs);}
	static T propa(T a, T b){return a+b;}
};

template<typename T>
struct SegfMinAdd{
	static T id(){return inf<T>();}
	static T q(T a, T b){return min(a,b);}
	static void upd(T& tv, T uv, int cs, int ce){tv=tv+uv;}
	static T propa(T a, T b){return a+b;}
};

template<typename T>
struct SegfMaxAdd{
	static T id(){return -inf<T>();}
	static T q(T a, T b){return max(a,b);}
	static void upd(T& tv, T uv, int cs, int ce){tv=tv+uv;}
	static T propa(T a, T b){return a+b;}
};
