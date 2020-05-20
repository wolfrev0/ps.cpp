#include "Core.h"

template<typename T>
struct Zip{
	Zip(Arr<T> a):a(a){sort(all(this->a));}
	int zip(T x){return lower_bound(all(a),x)-a.begin();}
	T unzip(int x){return a[x];}
	Arr<T> a;
};