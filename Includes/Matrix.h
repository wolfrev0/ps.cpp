#pragma once
#include "Core.h"

template<typename T, int n>
struct Mat{
	array<array<T,n>,n> a{0,};
	Mat(bool is_one=0){
		if(is_one){
			hfor(i,0,n)
				a[i][i]=1;
		}
	}
	Mat(const array<array<T,n>,n>& a):a(a){}

	Mat operator*(const Mat& r)const{
		Mat<T, n> ret;
		hfor(i,0,n)
			hfor(j,0,n)
				hfor(k,0,n)
					ret.a[i][j]+=a[i][k]*r.a[k][j];
		return ret;
	}
	array<T, n> operator*(const array<T, n>& r)const{
		array<T, n> ret{0,};
		hfor(i,0,n)
			hfor(j,0,n)
				ret[i]+=a[i][j]*r[j];
		return ret;
	}

	void transpose(){}
	void gauss_elim(){}
};