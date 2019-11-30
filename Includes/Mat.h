#pragma once
#include "Core.h"

template<typename T>
struct Mat{
	const int n,m;
	Arr<Arr<T>> a;
	
	Mat(int n, int m, bool one=false):n(n),m(m),a(n,Arr<T>(m)){
		if(!one)
			return;
		rep(i,min(n,m))
			rep(j,min(n,m))
				a[i][j]=1;
	}
	
	Mat<T> operator*(const Mat<T>& r)const{
		assert(m==r.n);
		Mat<T> ret(n,r.m);
		rep(i,n)
			rep(j,r.m)
				rep(k,m)
					ret.a[i][j]+=a[i][k]*r.a[k][j];
		return ret;
	}

	void transpose(){}
	
	Mat<T> sub(int r, int c, int rn, int rm)const{
		Mat<T> ret(rn,rm);
		rep(i,rn)
			rep(j,rm)
				ret.a[i][j]=a[r+i][c+j];
		return ret;
	}
	
	void REF(bool pv_fix){
		int pi=0;
		repo(i,n){
			while(pi<m && a[i][pi]==0){
				if(!pv_fix){
					hforo(j,i+1,n)
						if(a[j][pi])
							break;
					if(j<n){
						hfor(k,pi,m)
							swap(a[i][k],a[j][k]);
						break;
					}
				}
				pi++;
			}
			if(pi==m)
				break;
			if(a[i][pi]){
				hfori(j,pi,m)
					a[i][j]/=a[i][pi];
				hfor(j,i+1,n){
					auto z=a[j][pi];
					if(z==0)
						continue;
					hfor(k,pi,m)
						a[i][k]*=z;
					hfor(k,pi,m)
						a[j][k]-=a[i][k];
					hfor(k,pi,m)
						a[i][k]/=z;
				}
			}
			pi++;
		}
		rank=i;
	}
	int rank=-1;
	
	void RREF(int rm){
		REF(false);
		flipX(rank);
		flipY(rm);
		REF(true);
		flipY(rm);
		flipX(rank);
	}
	
	void flipX(int rn){
		rep(i,rn/2)
			rep(j,m)
				swap(a[i][j],a[rn-1-i][j]);
	}
	
	void flipY(int rm){
		rep(i,n)
			rep(j,rm/2)
				swap(a[i][j],a[i][rm-1-j]);
	}
};

template<typename T>
ostream& operator<<(ostream& s, const Mat<T>& mat){
	rep(i,mat.n){
		rep(j,mat.m)
			s<<mat.a[i][j]<<' ';
		s<<endl;
	}
	return s;
}