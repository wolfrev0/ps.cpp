#pragma once
#include "Core.h"

template<int m>
struct MatGF2{
	const int n;
	Arr<bitset<m>> a;
	
	MatGF2(int n, bool one=false):n(n),a(n){
		if(!one)
			return;
		rep(i,min(n,m))
			rep(j,min(n,m))
				a[i][j]=1;
	}
	
	template<int rm>
	MatGF2 operator*(const MatGF2<rm>& r)const{
		assert(m==r.n);
		MatGF2 ret(n,rm);
		rep(i,n)
			rep(j,m)
				if(a[i][j])
					ret.a[i]^=r.a[j];
		return ret;
	}

	void transpose(){}
	
	MatGF2 sub(int r, int c, int rn, int rm)const{
		MatGF2 ret(rn,rm);
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
						swap(a[i],a[j]);
						break;
					}
				}
				pi++;
			}
			if(pi==m)
				break;
			if(a[i][pi])
				hfor(j,i+1,n)
					if(a[j][pi])
						a[j]^=a[i];
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
			swap(a[i],a[rn-1-i]);
	}
	
	void flipY(int rm){
		rep(i,n){
			rep(j,rm/2){
				bool z=a[i][j];
				a[i][j]=a[i][rm-1-j];
				a[i][rm-1-j]=z;
			}
		}
	}
};

template<int m>
ostream& operator<<(ostream& s, const MatGF2<m>& mat){
	rep(i,mat.n){
		rep(j,m)
			s<<mat.a[i][j]<<' ';
		s<<endl;
	}
	return s;
}