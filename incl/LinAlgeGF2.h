#pragma once
#include "Core.h"

template<int m>
struct MatGF2{
	const int n;
	Arr<bitset<m>> a;
	
	MatGF2(int n, bool one=false):n(n),a(n){
		if(!one)
			return;
		for(int i=0;i<min(n,m);i++)
			for(int j=0;j<min(n,m);j++)
				a[i][j]=1;
	}
	
	template<int rm>
	MatGF2 operator*(const MatGF2<rm>& r)const{
		assert(m==r.n);
		MatGF2 ret(n,rm);
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(a[i][j])
					ret.a[i]^=r.a[j];
		return ret;
	}

	void transpose(){}
	
	MatGF2 sub(int r, int c, int rn, int rm)const{
		MatGF2 ret(rn,rm);
		for(int i=0;i<rn;i++)
			for(int j=0;j<rm;j++)
				ret.a[i][j]=a[r+i][c+j];
		return ret;
	}
	
	void REF(bool pv_fix){
		int pi=0;
		int i=0;
		for(;i<n;i++){
			while(pi<m && a[i][pi]==0){
				if(!pv_fix){
					int j=i+1;
					for(;j<n;j++)
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
				for(int j=i+1;j<n;j++)
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
		for(int i=0;i<rn/2;i++)
			swap(a[i],a[rn-1-i]);
	}
	
	void flipY(int rm){
		for(int i=0;i<n;i++){
			for(int j=0;j<rm/2;j++){
				bool z=a[i][j];
				a[i][j]=a[i][rm-1-j];
				a[i][rm-1-j]=z;
			}
		}
	}
};

template<int m>
ostream& operator<<(ostream& s, const MatGF2<m>& mat){
	for(int i=0;i<mat.n;i++){
		for(int j=0;j<m;j++)
			s<<mat.a[i][j]<<' ';
		s<<endl;
	}
	return s;
}

//https://codeforces.com/blog/entry/68953
//can use greedy maximize
//((staircase basis, basis coefficient),selected basis indices)
//staircase basis: has some good property
//basis coefficient and selected basis indices: for reconstruct
pair<Arr<pint>,Arr<int>> xor_basis(const Arr<int>& a){
	Arr<pint> r(64,{-1,-1});//descending
	Arr<int> bi;
	for(int i=0;i<sz(a);i++){
		int x=a[i], xc=0;
		for(auto [b,bc]:r)
			if(~b and x>(x^b))
				x^=b, xc^=bc;
		if(x)
			r[63-lg2f(x)]={x,xc^(1ll<<sz(bi))}, bi.pushb(i);
	}
	return {move(r),move(bi)};
}
