#pragma once
#include "core/base.h"

#pragma GCC optimize ("Ofast")
//NOTE: n*m행렬이다. m*n행렬이 아님(코드상으로는 <m> (n)형태라 헷갈리니 조심)
template<int m> struct MatGF2{
	const int n;
	Arr<bitset<m>> a;
	MatGF2(int n):n(n),a(n){}
	Arr<int> operator*(const bitset<m>& v)const{
		//NOTE: M*v 말고 v*M이 필요한 경우 전치시키면 됨
		Arr<int> ret(n);
		for(int i=0;i<n;i++)
			ret[i]=(a[i]&v).count()%2;
		return ret;
	}
	MatGF2 inv(){
		if(n>m)
			throw "No MatInv";
		MatGF2<m*2> tmp(n);
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				tmp.a[i][j]=a[i][j];
		for(int i=0;i<n;i++)
			tmp.a[i][n+i]=1;
		if(tmp.RREF(n)!=n)
			throw "No MatInv";
		MatGF2 ret(n);
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				ret.a[i][j]=tmp.a[i][n+j];
		return ret;
	}

	int REF(bool pv_fix){
		int pi=0,i=0;
		for(;i<n;i++){
			while(pi<m&&a[i][pi]==0){
				if(!pv_fix){
					int j=i+1;
					for(;j<n;j++)
						if(a[j][pi])break;
					if(j<n){swap(a[i],a[j]);break;}
				}
				pi++;
			}
			if(pi==m)break;
			if(a[i][pi])for(int j=i+1;j<n;j++)if(a[j][pi])a[j]^=a[i];
			pi++;
		}
		return rank=i;
	}
	int RREF(int rm){REF(false),flipX(rank),flipY(rm),REF(true),flipY(rm),flipX(rank);return rank;}
	void flipX(int rn){for(int i=0;i<rn/2;i++)swap(a[i],a[rn-1-i]);}
	void flipY(int rm){
		for(int i=0;i<n;i++){
			for(int j=0;j<rm/2;j++){
				bool z=a[i][j];
				a[i][j]=a[i][rm-1-j],a[i][rm-1-j]=z;
			}
		}
	}
private:
	int rank=-1;
};

template<int m> ostream& operator<<(ostream& s, const MatGF2<m>& mat){
	for(int i=0;i<mat.n;i++){
		for(int j=0;j<m;j++) s << mat.a[i][j] << ' ';
		s << endl;
	}
	return s;
}

// https://codeforces.com/blog/entry/68953
// can use greedy maximize
//((staircase basis, basis coefficient),selected basis indices)
// staircase basis: has some good property
// basis coefficient and selected basis indices: for reconstruct
pair<Arr<pint>, Arr<int>> xor_basis(const Arr<int>& a){
	Arr<pint> r(64,{-1, -1}); // descending
	Arr<int> bi;
	for(int i=0;i<sz(a);i++){
		int x=a[i], xc=0;
		for(auto [b, bc] : r)
			if(~b and x > (x ^ b)) x^=b, xc^=bc;
		if(x) r[63-lg2f(x)]={x, xc ^ (1ll << sz(bi))}, bi.pushb(i);
	}
	return{move(r), move(bi)};
}