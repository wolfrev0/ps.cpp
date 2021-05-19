#include "Core.h"

template<class T> struct Zip{
	Zip(Arr<T> arr):a(arr){sort(a.begin(),a.end());}
	int zip(T x){return lb(a.begin(),a.end(),x)-a.begin();}
	T unzip(int x){return a[x];}
	Arr<T> a;
};