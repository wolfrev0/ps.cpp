#pragma once
#include "Core.h"

template<typename T, int n>
struct Mat{
	array<array<int,n>,n> a{0,};
	Mat(){
		forh(i,0,n)
			a[i][i]=1;
	}
	Mat(const array<array<int,n>,n>& a):a(a){}

	Mat operator*(const Mat& r)const{
		array<array<int,n>,n> ret{0,};
		forh(i,0,n)
			forh(j,0,n)
				forh(k,0,n)
					ret[i][j]+=a[i][k]*r.a[k][j];
		return ret;
	}
	array<int, n> operator*(const array<int, n>& r)const{
		array<int, n> ret{0,};
		forh(i,0,n)
			forh(j,0,n)
				ret[i]+=a[i][j]*r[j];
		return ret;
	}

	void transpose(){}
	void gauss_elim(){}
};