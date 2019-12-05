#pragma once
#include "Core.h"

template<typename T>
struct Fenwick{
	Fenwick(int n=0):n(n), tr(n+1){}

	T q(int i){return q(i, i+1);}
	T q(int s, int e){
		if(s>=e)
			return T();
		s++, e++;//ft idx base = 1
		return sum(e-1)-sum(s-1);
	}

	void upd(int i, T delta){
		i++;
		while(i<=n){
			tr[i]+=delta;
			i+=(i&-i);
		}
	}

	void RUPQu(int s, int e, T d){
		upd(s,d);
		upd(e,-d);
	}
	T RUPQq(int i){return sum(i+1);}
	
private:
	int n;
	Arr<T> tr;
	
	T sum(int i){
		T ans=T();
		while(i>0){
			ans+=tr[i];
			i-=(i&-i);
		}
		return ans;
	}
};