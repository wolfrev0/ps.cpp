#pragma once
#include "Core.h"

template<typename T, int n>
struct Mat{
	array<array<T,n>,n> a{0,};
	Mat(bool is_one=0){
		if(is_one){
			forh(i,0,n)
				a[i][i]=1;
		}
	}
	Mat(const array<array<T,n>,n>& a):a(a){}

	Mat operator*(const Mat& r)const{
		Mat<T, n> ret;
		forh(i,0,n)
			forh(j,0,n)
				forh(k,0,n)
					ret.a[i][j]+=a[i][k]*r.a[k][j];
		return ret;
	}
	array<T, n> operator*(const array<T, n>& r)const{
		array<T, n> ret{0,};
		forh(i,0,n)
			forh(j,0,n)
				ret[i]+=a[i][j]*r[j];
		return ret;
	}

	void transpose(){}
	void gauss_elim(){}
};